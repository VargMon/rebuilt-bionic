#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdatomic.h>
#include <sys/syscall.h> /* For syscall defines */
#include <unistd.h> /* For the actual syscall function */
#include <private/bionic_syscall.h> /* XXX: Super hackish musl libc like syscall macros.. etc.. */

/* This'is evil */
#undef weak_alias
#define weak_alias(old, new) \
	extern __typeof(old) new __attribute__((weak, alias(#old)))

#ifdef SHARED
__LIBC_HIDDEN__
#endif
long __cancel(), __cp_cancel(), __syscall_cp_asm(), __syscall_cp_c();

long __cancel()
{
	pthread_t self = __pthread_self();
	if (self->canceldisable == PTHREAD_CANCEL_ENABLE || self->cancelasync)
		pthread_exit(PTHREAD_CANCELED);
	self->canceldisable = PTHREAD_CANCEL_DISABLE;
	return -ECANCELED;
}

/* If __syscall_cp_asm has adjusted the stack pointer, it must provide a
 * definition of __cp_cancel to undo those adjustments and call __cancel.
 * Otherwise, __cancel provides a definition for __cp_cancel. */

weak_alias(__cancel, __cp_cancel);

long __syscall_cp_asm(volatile void *, syscall_arg_t,
                      syscall_arg_t, syscall_arg_t, syscall_arg_t,
                      syscall_arg_t, syscall_arg_t, syscall_arg_t);

long __syscall_cp_c(syscall_arg_t nr,
                    syscall_arg_t u, syscall_arg_t v, syscall_arg_t w,
                    syscall_arg_t x, syscall_arg_t y, syscall_arg_t z)
{
	pthread_t self;
	long r;
	int st;

	if ((st=(self=__pthread_self())->canceldisable)
	    && (st==PTHREAD_CANCEL_DISABLE || nr==SYS_close))
		return __syscall(nr, u, v, w, x, y, z);

	r = __syscall_cp_asm(&self->cancel, nr, u, v, w, x, y, z);
	if (r==-EINTR && nr!=SYS_close && self->cancel &&
	    self->canceldisable != PTHREAD_CANCEL_DISABLE)
		r = __cancel();
	return r;
}

static void _sigaddset(sigset_t *set, int sig)
{
	unsigned s = sig-1;
	set->__bits[s/8/sizeof *set->__bits] |= 1UL<<(s&8*sizeof *set->__bits-1);
}

#ifdef SHARED
__LIBC_HIDDEN__
#endif
extern const char __cp_begin[1], __cp_end[1];

static void cancel_handler(int sig, siginfo_t *si, void *ctx)
{
	pthread_t self = __pthread_self();
	ucontext_t *uc = ctx;
	const char *ip = ((char **)&uc->uc_mcontext)[CANCEL_REG_IP];

	a_barrier();
	if (!self->cancel || self->canceldisable == PTHREAD_CANCEL_DISABLE) return;

	_sigaddset(&uc->uc_sigmask, SIGCANCEL);

	if (self->cancelasync || ip >= __cp_begin && ip < __cp_end) {
		((char **)&uc->uc_mcontext)[CANCEL_REG_IP] = (char *)__cp_cancel;
		return;
	}

	__syscall(SYS_tkill, self->tid, SIGCANCEL);
}

void __testcancel()
{
	pthread_t self = __pthread_self();
	if (self->cancel && !self->canceldisable)
		__cancel();
}

static void init_cancellation()
{
	struct sigaction sa = {
		.sa_flags = SA_SIGINFO | SA_RESTART,
		.sa_sigaction = cancel_handler
	};
	memset(&sa.sa_mask, -1, _NSIG/8);
	__libc_sigaction(SIGCANCEL, &sa, 0);
}

int pthread_cancel(pthread_t t)
{
	static int init;
	if (!init) {
		init_cancellation();
		init = 1;
	}
	a_store(&t->cancel, 1);
	return pthread_kill(t, SIGCANCEL);
}

int pthread_setcanceltype(int new, int *old)
{
	struct pthread *self = __pthread_self();
	if (new > 1U) return EINVAL;
	if (old) *old = self->cancelasync;
	self->cancelasync = new;
	if (new) pthread_testcancel();
	return 0;
}

int __pthread_setcancelstate(int new, int *old)
{
	if (new > 2U) return EINVAL;
	struct pthread *self = __pthread_self();
	if (old) *old = self->canceldisable;
	self->canceldisable = new;
	return 0;
}

weak_alias(__pthread_setcancelstate, pthread_setcancelstate);

static void dummy()
{
}

weak_alias(dummy, __testcancel);

void __pthread_testcancel()
{
	__testcancel();
}

weak_alias(__pthread_testcancel, pthread_testcancel);


