#ifndef _STDARG_H
#define _STDARG_H

#include <sys/cdefs.h>

__BEGIN_DECLS

#define __NEED_va_list

#include <types.h>

#if __GNUC__ >= 3
#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v,l)     __builtin_va_arg(v,l)
#define va_copy(d,s)    __builtin_va_copy(d,s)
#else
#include <machine/stdarg.h>
#endif

__END_DECLS

#endif
