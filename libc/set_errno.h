/*
 * Copyright (c) Christopher Friedt. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef SHOULD_CLEAR_ERRNO_H_
#define SHOULD_CLEAR_ERRNO_H_

#include <errno.h>

/* Some functions call others that might set errno.
 * However, the functions themselves are not specified
 * to set errno on failure. Enabling this will make
 * those functions clear errno before returning,
 * regardless of the previous state of errno or any
 * failure on behalf of the function.
 */
#define BE_GOOD 1
#if BE_GOOD
#define SHOULD_SET_ERRNO(x) \
	{ errno = x; }
#define WOULD_SET_ERRNO(x) \
	do {} while(0)
#else
#define SHOULD_SET_ERRNO(x) \
	do {} while(0)
#define WOULD_SET_ERRNO(x) \
	{ errno = x; }
#endif
#undef BE_GOOD

#define SET_ERRNO(x) \
	{ \
		WOULD_SET_ERRNO(x); \
		SHOULD_SET_ERRNO(x); \
	}
#define SHOULD_CLEAR_ERRNO() SHOULD_SET_ERRNO(0)

#endif /* SHOULD_CLEAR_ERRNO_H_ */
