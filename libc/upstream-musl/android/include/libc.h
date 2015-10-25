// Bionic-specific libc.h.
#ifndef MUSL_LIBC_H
#define MUSL_LIBC_H
#include <stddef.h>
#define weak_alias(name1,name2)  // nothing here.

#define ATTR_LIBC_VISIBILITY __attribute__((visibility("hidden")))

#endif  // MUSL_LIBC_H