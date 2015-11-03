#ifndef _PTHREAD_H
#define _PTHREAD_H

#include_next <pthread.h>

/* XXX: ripped from musl libc
#define PTHREAD_CANCEL_ENABLE 0
#define PTHREAD_CANCEL_DISABLE 1
#define PTHREAD_CANCEL_MASKED 2

#define PTHREAD_CANCEL_DEFERRED 0
#define PTHREAD_CANCEL_ASYNCHRONOUS 1

#define PTHREAD_CANCELED ((void *)-1)

#ifdef __cplusplus
extern "C" {
#endif

int pthread_setcancelstate(int, int *);
int pthread_setcanceltype(int, int *);
void pthread_testcancel(void);
int pthread_cancel(pthread_t);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _PTHREAD_H */