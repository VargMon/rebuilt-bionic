#ifndef _BIONIC_UPSTREAM_MUSL_ATOMIC_H
#define _BIONIC_UPSTREAM_MUSL_ATOMIC_H

#include <stdint.h>

#if defined(__x86__)
static inline int a_ctz_64(uint64_t x)
{
	int r;
	__asm__( "bsf %1,%0 ; jnz 1f ; bsf %2,%0 ; addl $32,%0\n1:"
		: "=r"(r) : "r"((unsigned)x), "r"((unsigned)(x>>32)) );
	return r;
}

static inline int a_ctz_l(unsigned long x)
{
	long r;
	__asm__( "bsf %1,%0" : "=r"(r) : "r"(x) );
	return r;
}

static inline void a_and_64(volatile uint64_t *p, uint64_t v)
{
	__asm__( "lock ; andl %1, (%0) ; lock ; andl %2, 4(%0)"
		: : "r"((long *)p), "r"((unsigned)v), "r"((unsigned)(v>>32)) : "memory" );
}

static inline void a_or_64(volatile uint64_t *p, uint64_t v)
{
	__asm__( "lock ; orl %1, (%0) ; lock ; orl %2, 4(%0)"
		: : "r"((long *)p), "r"((unsigned)v), "r"((unsigned)(v>>32)) : "memory" );
}

static inline void a_or_l(volatile void *p, long v)
{
	__asm__( "lock ; orl %1, %0"
		: "=m"(*(long *)p) : "r"(v) : "memory" );
}

static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	__asm__( "lock ; cmpxchg %3, %1"
		: "=a"(t), "=m"(*(long *)p) : "a"(t), "r"(s) : "memory" );
	return t;
}

static inline int a_cas(volatile int *p, int t, int s)
{
	__asm__( "lock ; cmpxchg %3, %1"
		: "=a"(t), "=m"(*p) : "a"(t), "r"(s) : "memory" );
	return t;
}

static inline void a_or(volatile int *p, int v)
{
	__asm__( "lock ; orl %1, %0"
		: "=m"(*p) : "r"(v) : "memory" );
}

static inline void a_and(volatile int *p, int v)
{
	__asm__( "lock ; andl %1, %0"
		: "=m"(*p) : "r"(v) : "memory" );
}

static inline int a_swap(volatile int *x, int v)
{
	__asm__( "xchg %0, %1" : "=r"(v), "=m"(*x) : "0"(v) : "memory" );
	return v;
}

#define a_xchg a_swap

static inline int a_fetch_add(volatile int *x, int v)
{
	__asm__( "lock ; xadd %0, %1" : "=r"(v), "=m"(*x) : "0"(v) : "memory" );
	return v;
}

static inline void a_inc(volatile int *x)
{
	__asm__( "lock ; incl %0" : "=m"(*x) : "m"(*x) : "memory" );
}

static inline void a_dec(volatile int *x)
{
	__asm__( "lock ; decl %0" : "=m"(*x) : "m"(*x) : "memory" );
}

static inline void a_store(volatile int *p, int x)
{
	__asm__( "movl %1, %0 ; lock ; orl $0,(%%esp)" : "=m"(*p) : "r"(x) : "memory" );
}

static inline void a_spin()
{
	__asm__ __volatile__( "pause" : : : "memory" );
}

static inline void a_barrier()
{
	__asm__ __volatile__( "" : : : "memory" );
}

static inline void a_crash()
{
	__asm__ __volatile__( "hlt" : : : "memory" );
}
#elif defined(__x86_64_)
static inline int a_ctz_64(uint64_t x)
{
	__asm__( "bsf %1,%0" : "=r"(x) : "r"(x) );
	return x;
}

static inline int a_ctz_l(unsigned long x)
{
	__asm__( "bsf %1,%0" : "=r"(x) : "r"(x) );
	return x;
}

static inline void a_and_64(volatile uint64_t *p, uint64_t v)
{
	__asm__( "lock ; and %1, %0"
			 : "=m"(*p) : "r"(v) : "memory" );
}

static inline void a_or_64(volatile uint64_t *p, uint64_t v)
{
	__asm__( "lock ; or %1, %0"
			 : "=m"(*p) : "r"(v) : "memory" );
}

static inline void a_or_l(volatile void *p, long v)
{
	__asm__( "lock ; or %1, %0"
		: "=m"(*(long *)p) : "r"(v) : "memory" );
}

static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	__asm__( "lock ; cmpxchg %3, %1"
		: "=a"(t), "=m"(*(long *)p) : "a"(t), "r"(s) : "memory" );
	return t;
}

static inline int a_cas(volatile int *p, int t, int s)
{
	__asm__( "lock ; cmpxchg %3, %1"
		: "=a"(t), "=m"(*p) : "a"(t), "r"(s) : "memory" );
	return t;
}

static inline void a_or(volatile int *p, int v)
{
	__asm__( "lock ; or %1, %0"
		: "=m"(*p) : "r"(v) : "memory" );
}

static inline void a_and(volatile int *p, int v)
{
	__asm__( "lock ; and %1, %0"
		: "=m"(*p) : "r"(v) : "memory" );
}

static inline int a_swap(volatile int *x, int v)
{
	__asm__( "xchg %0, %1" : "=r"(v), "=m"(*x) : "0"(v) : "memory" );
	return v;
}

static inline int a_fetch_add(volatile int *x, int v)
{
	__asm__( "lock ; xadd %0, %1" : "=r"(v), "=m"(*x) : "0"(v) : "memory" );
	return v;
}

static inline void a_inc(volatile int *x)
{
	__asm__( "lock ; incl %0" : "=m"(*x) : "m"(*x) : "memory" );
}

static inline void a_dec(volatile int *x)
{
	__asm__( "lock ; decl %0" : "=m"(*x) : "m"(*x) : "memory" );
}

static inline void a_store(volatile int *p, int x)
{
	__asm__( "mov %1, %0 ; lock ; orl $0,(%%rsp)" : "=m"(*p) : "r"(x) : "memory" );
}

static inline void a_spin()
{
	__asm__ __volatile__( "pause" : : : "memory" );
}

static inline void a_barrier()
{
	__asm__ __volatile__( "" : : : "memory" );
}

static inline void a_crash()
{
	__asm__ __volatile__( "hlt" : : : "memory" );
}
#elif defined(__arm__)
static inline int a_ctz_l(unsigned long x)
{
	static const char debruijn32[32] = {
		0, 1, 23, 2, 29, 24, 19, 3, 30, 27, 25, 11, 20, 8, 4, 13,
		31, 22, 28, 18, 26, 10, 7, 12, 21, 17, 9, 6, 16, 5, 15, 14
	};
	return debruijn32[(x&-x)*0x076be629 >> 27];
}

static inline int a_ctz_64(uint64_t x)
{
	uint32_t y = x;
	if (!y) {
		y = x>>32;
		return 32 + a_ctz_l(y);
	}
	return a_ctz_l(y);
}

#if __ARM_ARCH_7A__ || __ARM_ARCH_7R__ ||  __ARM_ARCH >= 7

static inline void a_barrier()
{
	__asm__ __volatile__("dmb ish");
}

static inline int a_cas(volatile int *p, int t, int s)
{
	int old;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldrex %0,%3\n"
		"	cmp %0,%1\n"
		"	bne 1f\n"
		"	strex %0,%2,%3\n"
		"	cmp %0, #0\n"
		"	bne 1b\n"
		"	mov %0, %1\n"
		"1:	dmb ish\n"
		: "=&r"(old)
		: "r"(t), "r"(s), "Q"(*p)
		: "memory", "cc" );
	return old;
}

static inline int a_swap(volatile int *x, int v)
{
	int old, tmp;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldrex %0,%3\n"
		"	strex %1,%2,%3\n"
		"	cmp %1, #0\n"
		"	bne 1b\n"
		"	dmb ish\n"
		: "=&r"(old), "=&r"(tmp)
		: "r"(v), "Q"(*x)
		: "memory", "cc" );
	return old;
}

static inline int a_fetch_add(volatile int *x, int v)
{
	int old, tmp;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldrex %0,%3\n"
		"	add %0,%0,%2\n"
		"	strex %1,%0,%3\n"
		"	cmp %1, #0\n"
		"	bne 1b\n"
		"	dmb ish\n"
		: "=&r"(old), "=&r"(tmp)
		: "r"(v), "Q"(*x)
		: "memory", "cc" );
	return old-v;
}

static inline void a_inc(volatile int *x)
{
	int tmp, tmp2;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldrex %0,%2\n"
		"	add %0,%0,#1\n"
		"	strex %1,%0,%2\n"
		"	cmp %1, #0\n"
		"	bne 1b\n"
		"	dmb ish\n"
		: "=&r"(tmp), "=&r"(tmp2)
		: "Q"(*x)
		: "memory", "cc" );
}

static inline void a_dec(volatile int *x)
{
	int tmp, tmp2;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldrex %0,%2\n"
		"	sub %0,%0,#1\n"
		"	strex %1,%0,%2\n"
		"	cmp %1, #0\n"
		"	bne 1b\n"
		"	dmb ish\n"
		: "=&r"(tmp), "=&r"(tmp2)
		: "Q"(*x)
		: "memory", "cc" );
}

static inline void a_and(volatile int *x, int v)
{
	int tmp, tmp2;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldrex %0,%3\n"
		"	and %0,%0,%2\n"
		"	strex %1,%0,%3\n"
		"	cmp %1, #0\n"
		"	bne 1b\n"
		"	dmb ish\n"
		: "=&r"(tmp), "=&r"(tmp2)
		: "r"(v), "Q"(*x)
		: "memory", "cc" );
}

static inline void a_or(volatile int *x, int v)
{
	int tmp, tmp2;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldrex %0,%3\n"
		"	orr %0,%0,%2\n"
		"	strex %1,%0,%3\n"
		"	cmp %1, #0\n"
		"	bne 1b\n"
		"	dmb ish\n"
		: "=&r"(tmp), "=&r"(tmp2)
		: "r"(v), "Q"(*x)
		: "memory", "cc" );
}

static inline void a_store(volatile int *p, int x)
{
	__asm__ __volatile__(
		"	dmb ish\n"
		"	str %1,%0\n"
		"	dmb ish\n"
		: "=m"(*p)
		: "r"(x)
		: "memory", "cc" );
}

#else

int __a_cas(int, int, volatile int *) __attribute__((__visibility__("hidden")));
#define __k_cas __a_cas

static inline void a_barrier()
{
	__asm__ __volatile__("bl __a_barrier"
		: : : "memory", "cc", "ip", "lr" );
}

static inline int a_cas(volatile int *p, int t, int s)
{
	int old;
	for (;;) {
		if (!__k_cas(t, s, p))
			return t;
		if ((old=*p) != t)
			return old;
	}
}

static inline int a_swap(volatile int *x, int v)
{
	int old;
	do old = *x;
	while (__k_cas(old, v, x));
	return old;
}

static inline int a_fetch_add(volatile int *x, int v)
{
	int old;
	do old = *x;
	while (__k_cas(old, old+v, x));
	return old;
}

static inline void a_inc(volatile int *x)
{
	a_fetch_add(x, 1);
}

static inline void a_dec(volatile int *x)
{
	a_fetch_add(x, -1);
}

static inline void a_store(volatile int *p, int x)
{
	a_barrier();
	*p = x;
	a_barrier();
}

static inline void a_and(volatile int *p, int v)
{
	int old;
	do old = *p;
	while (__k_cas(old, old&v, p));
}

static inline void a_or(volatile int *p, int v)
{
	int old;
	do old = *p;
	while (__k_cas(old, old|v, p));
}

#endif

static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	return (void *)a_cas(p, (int)t, (int)s);
}

#define a_spin a_barrier

static inline void a_crash()
{
	*(volatile char *)0=0;
}

static inline void a_or_l(volatile void *p, long v)
{
	a_or(p, v);
}

static inline void a_and_64(volatile uint64_t *p, uint64_t v)
{
	union { uint64_t v; uint32_t r[2]; } u = { v };
	a_and((int *)p, u.r[0]);
	a_and((int *)p+1, u.r[1]);
}

static inline void a_or_64(volatile uint64_t *p, uint64_t v)
{
	union { uint64_t v; uint32_t r[2]; } u = { v };
	a_or((int *)p, u.r[0]);
	a_or((int *)p+1, u.r[1]);
}
#elif defined(__aarch64__)
static inline int a_ctz_64(uint64_t x)
{
	__asm__(
		"	rbit %0, %1\n"
		"	clz %0, %0\n"
		: "=r"(x) : "r"(x));
	return x;
}

static inline int a_ctz_l(unsigned long x)
{
	return a_ctz_64(x);
}

static inline void a_barrier()
{
	__asm__ __volatile__("dmb ish");
}

static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	void *old;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldxr %0,%3\n"
		"	cmp %0,%1\n"
		"	b.ne 1f\n"
		"	stxr %w0,%2,%3\n"
		"	cbnz %w0,1b\n"
		"	mov %0,%1\n"
		"1:	dmb ish\n"
		: "=&r"(old)
		: "r"(t), "r"(s), "Q"(*(long*)p)
		: "memory", "cc");
	return old;
}

static inline int a_cas(volatile int *p, int t, int s)
{
	int old;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldxr %w0,%3\n"
		"	cmp %w0,%w1\n"
		"	b.ne 1f\n"
		"	stxr %w0,%w2,%3\n"
		"	cbnz %w0,1b\n"
		"	mov %w0,%w1\n"
		"1:	dmb ish\n"
		: "=&r"(old)
		: "r"(t), "r"(s), "Q"(*p)
		: "memory", "cc");
	return old;
}

static inline int a_swap(volatile int *x, int v)
{
	int old, tmp;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldxr %w0,%3\n"
		"	stxr %w1,%w2,%3\n"
		"	cbnz %w1,1b\n"
		"	dmb ish\n"
		: "=&r"(old), "=&r"(tmp)
		: "r"(v), "Q"(*x)
		: "memory", "cc" );
	return old;
}

static inline int a_fetch_add(volatile int *x, int v)
{
	int old, tmp;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldxr %w0,%3\n"
		"	add %w0,%w0,%w2\n"
		"	stxr %w1,%w0,%3\n"
		"	cbnz %w1,1b\n"
		"	dmb ish\n"
		: "=&r"(old), "=&r"(tmp)
		: "r"(v), "Q"(*x)
		: "memory", "cc" );
	return old-v;
}

static inline void a_inc(volatile int *x)
{
	int tmp, tmp2;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldxr %w0,%2\n"
		"	add %w0,%w0,#1\n"
		"	stxr %w1,%w0,%2\n"
		"	cbnz %w1,1b\n"
		"	dmb ish\n"
		: "=&r"(tmp), "=&r"(tmp2)
		: "Q"(*x)
		: "memory", "cc" );
}

static inline void a_dec(volatile int *x)
{
	int tmp, tmp2;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldxr %w0,%2\n"
		"	sub %w0,%w0,#1\n"
		"	stxr %w1,%w0,%2\n"
		"	cbnz %w1,1b\n"
		"	dmb ish\n"
		: "=&r"(tmp), "=&r"(tmp2)
		: "Q"(*x)
		: "memory", "cc" );
}

static inline void a_and_64(volatile uint64_t *p, uint64_t v)
{
	int tmp, tmp2;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldxr %0,%3\n"
		"	and %0,%0,%2\n"
		"	stxr %w1,%0,%3\n"
		"	cbnz %w1,1b\n"
		"	dmb ish\n"
		: "=&r"(tmp), "=&r"(tmp2)
		: "r"(v), "Q"(*p)
		: "memory", "cc" );
}

static inline void a_and(volatile int *p, int v)
{
	int tmp, tmp2;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldxr %w0,%3\n"
		"	and %w0,%w0,%w2\n"
		"	stxr %w1,%w0,%3\n"
		"	cbnz %w1,1b\n"
		"	dmb ish\n"
		: "=&r"(tmp), "=&r"(tmp2)
		: "r"(v), "Q"(*p)
		: "memory", "cc" );
}

static inline void a_or_64(volatile uint64_t *p, uint64_t v)
{
	int tmp, tmp2;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldxr %0,%3\n"
		"	orr %0,%0,%2\n"
		"	stxr %w1,%0,%3\n"
		"	cbnz %w1,1b\n"
		"	dmb ish\n"
		: "=&r"(tmp), "=&r"(tmp2)
		: "r"(v), "Q"(*p)
		: "memory", "cc" );
}

static inline void a_or_l(volatile void *p, long v)
{
	return a_or_64(p, v);
}

static inline void a_or(volatile int *p, int v)
{
	int tmp, tmp2;
	__asm__ __volatile__(
		"	dmb ish\n"
		"1:	ldxr %w0,%3\n"
		"	orr %w0,%w0,%w2\n"
		"	stxr %w1,%w0,%3\n"
		"	cbnz %w1,1b\n"
		"	dmb ish\n"
		: "=&r"(tmp), "=&r"(tmp2)
		: "r"(v), "Q"(*p)
		: "memory", "cc" );
}

static inline void a_store(volatile int *p, int x)
{
	__asm__ __volatile__(
		"	dmb ish\n"
		"	str %w1,%0\n"
		"	dmb ish\n"
		: "=m"(*p)
		: "r"(x)
		: "memory", "cc" );
}

#define a_spin a_barrier

static inline void a_crash()
{
	*(volatile char *)0=0;
}
#elif defined(__mips__)
static inline int a_ctz_l(unsigned long x)
{
	static const char debruijn32[32] = {
		0, 1, 23, 2, 29, 24, 19, 3, 30, 27, 25, 11, 20, 8, 4, 13,
		31, 22, 28, 18, 26, 10, 7, 12, 21, 17, 9, 6, 16, 5, 15, 14
	};
	return debruijn32[(x&-x)*0x076be629 >> 27];
}

static inline int a_ctz_64(uint64_t x)
{
	uint32_t y = x;
	if (!y) {
		y = x>>32;
		return 32 + a_ctz_l(y);
	}
	return a_ctz_l(y);
}

static inline int a_cas(volatile int *p, int t, int s)
{
	int dummy;
	__asm__ __volatile__(
		".set push\n"
		".set mips2\n"
		".set noreorder\n"
		"	sync\n"
		"1:	ll %0, %2\n"
		"	bne %0, %3, 1f\n"
		"	addu %1, %4, $0\n"
		"	sc %1, %2\n"
		"	beq %1, $0, 1b\n"
		"	nop\n"
		"	sync\n"
		"1:	\n"
		".set pop\n"
		: "=&r"(t), "=&r"(dummy), "+m"(*p) : "r"(t), "r"(s) : "memory" );
        return t;
}

static inline void *a_cas_p(volatile void *p, void *t, void *s)
{
	return (void *)a_cas(p, (int)t, (int)s);
}

static inline int a_swap(volatile int *x, int v)
{
	int old, dummy;
	__asm__ __volatile__(
		".set push\n"
		".set mips2\n"
		".set noreorder\n"
		"	sync\n"
		"1:	ll %0, %2\n"
		"	addu %1, %3, $0\n"
		"	sc %1, %2\n"
		"	beq %1, $0, 1b\n"
		"	nop\n"
		"	sync\n"
		".set pop\n"
		: "=&r"(old), "=&r"(dummy), "+m"(*x) : "r"(v) : "memory" );
        return old;
}

static inline int a_fetch_add(volatile int *x, int v)
{
	int old, dummy;
	__asm__ __volatile__(
		".set push\n"
		".set mips2\n"
		".set noreorder\n"
		"	sync\n"
		"1:	ll %0, %2\n"
		"	addu %1, %0, %3\n"
		"	sc %1, %2\n"
		"	beq %1, $0, 1b\n"
		"	nop\n"
		"	sync\n"
		".set pop\n"
		: "=&r"(old), "=&r"(dummy), "+m"(*x) : "r"(v) : "memory" );
        return old;
}

static inline void a_inc(volatile int *x)
{
	int dummy;
	__asm__ __volatile__(
		".set push\n"
		".set mips2\n"
		".set noreorder\n"
		"	sync\n"
		"1:	ll %0, %1\n"
		"	addu %0, %0, 1\n"
		"	sc %0, %1\n"
		"	beq %0, $0, 1b\n"
		"	nop\n"
		"	sync\n"
		".set pop\n"
		: "=&r"(dummy), "+m"(*x) : : "memory" );
}

static inline void a_dec(volatile int *x)
{
	int dummy;
	__asm__ __volatile__(
		".set push\n"
		".set mips2\n"
		".set noreorder\n"
		"	sync\n"
		"1:	ll %0, %1\n"
		"	subu %0, %0, 1\n"
		"	sc %0, %1\n"
		"	beq %0, $0, 1b\n"
		"	nop\n"
		"	sync\n"
		".set pop\n"
		: "=&r"(dummy), "+m"(*x) : : "memory" );
}

static inline void a_store(volatile int *p, int x)
{
	__asm__ __volatile__(
		".set push\n"
		".set mips2\n"
		".set noreorder\n"
		"	sync\n"
		"	sw %1, %0\n"
		"	sync\n"
		".set pop\n"
		: "+m"(*p) : "r"(x) : "memory" );
}

#define a_spin a_barrier

static inline void a_barrier()
{
	a_cas(&(int){0}, 0, 0);
}

static inline void a_crash()
{
	*(volatile char *)0=0;
}

static inline void a_and(volatile int *p, int v)
{
	int dummy;
	__asm__ __volatile__(
		".set push\n"
		".set mips2\n"
		".set noreorder\n"
		"	sync\n"
		"1:	ll %0, %1\n"
		"	and %0, %0, %2\n"
		"	sc %0, %1\n"
		"	beq %0, $0, 1b\n"
		"	nop\n"
		"	sync\n"
		".set pop\n"
		: "=&r"(dummy), "+m"(*p) : "r"(v) : "memory" );
}

static inline void a_or(volatile int *p, int v)
{
	int dummy;
	__asm__ __volatile__(
		".set push\n"
		".set mips2\n"
		".set noreorder\n"
		"	sync\n"
		"1:	ll %0, %1\n"
		"	or %0, %0, %2\n"
		"	sc %0, %1\n"
		"	beq %0, $0, 1b\n"
		"	nop\n"
		"	sync\n"
		".set pop\n"
		: "=&r"(dummy), "+m"(*p) : "r"(v) : "memory" );
}

static inline void a_or_l(volatile void *p, long v)
{
	a_or(p, v);
}

static inline void a_and_64(volatile uint64_t *p, uint64_t v)
{
	union { uint64_t v; uint32_t r[2]; } u = { v };
	a_and((int *)p, u.r[0]);
	a_and((int *)p+1, u.r[1]);
}

static inline void a_or_64(volatile uint64_t *p, uint64_t v)
{
	union { uint64_t v; uint32_t r[2]; } u = { v };
	a_or((int *)p, u.r[0]);
	a_or((int *)p+1, u.r[1]);
}
#endif /* If defined ARCH. */

#endif /* _BIONIC_UPSTREAM_MUSL_ATOMIC_H */
