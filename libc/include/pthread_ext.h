/*
 * Public domain.
 */

#ifndef _PTHREAD_EXT_H
#define _PTHREAD_EXT_H

#include <sys/cdefs.h>

#define PTHREAD_CANCEL_ENABLE 0
#define PTHREAD_CANCEL_DISABLE 1
#define PTHREAD_CANCEL_MASKED 2

#define PTHREAD_CANCEL_DEFERRED 0
#define PTHREAD_CANCEL_ASYNCHRONOUS 1

#define PTHREAD_CANCELED ((void *)-1)

__BEGIN_DECLS

int pthread_setcancelstate(int, int *);
int pthread_setcanceltype(int, int *);
void pthread_testcancel(void);
int pthread_cancel(pthread_t);

__END_DECLS

#endif /* _PTHREAD_EXT_H */