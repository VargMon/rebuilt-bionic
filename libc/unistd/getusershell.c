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

#include <unistd.h>

char *getusershell(void);
void setusershell(void);
void endusershell(void);

/**********************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <regex.h>
#ifndef NDEBUG
#define NDEBUG
#endif
#include <assert.h>
#include <ctype.h>

#include "shell_priv.h"
#include "set_errno.h"
#include "branch_prediction.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#endif

// empty line or comment line
static bool eorc(const char *line, const size_t len) {
	char *o;
	for(o=(char *)line; (o-line) < len && isblank(*o); o++);
	return (o-line) == len || *o == '#';
}

#define LINE_ALLOCATED 256
static char line[LINE_ALLOCATED];

static FILE *__the_shell = NULL;

static int default_shells_idx = -1;
static const char *default_shells[] = { "/bin/sh", "/bin/csh" };

char *getusershell(void) {
	char *r = NULL, *linep;
	ssize_t line_len;
	size_t line_alloc;
	int r2;

	const char *pat = SHELLLINE;
	static bool expr_initialized = false;
	static regex_t expr;
	regmatch_t match[2];

	if ( default_shells_idx >= 0 ) {

		if ( default_shells_idx < ARRAY_SIZE(default_shells) ) {
			r = (char *) default_shells[default_shells_idx];
			default_shells_idx++;
		}
		goto out;

	}

	if ( !expr_initialized ) {
		r2 = regcomp(&expr,pat,REG_EXTENDED);
		assert(!r2);
		if ( unlikely(r2) ) {
			WOULD_SET_ERRNO(EINVAL);
			goto out;
		}
	}

	for(;;) {

		linep = line;
		line_alloc = LINE_ALLOCATED;

		line_len = getline(&linep,&line_alloc,__the_shell);
		if ( !(linep == line && line_alloc == LINE_ALLOCATED) ) {
			SET_ERRNO(ENOBUFS);
			free(linep);
			goto out;
		}
		if ( unlikely(line_len == -1) )
			goto out;

		if ( eorc(line,line_len) )
			continue;

		if ( line[line_len -1] == '\n' ) {
			line[line_len -1] = '\0';
			line_len--;
		}

		r2 = regexec(&expr,line,ARRAY_SIZE(match),match,0);
		if ( unlikely(r2) )
			continue;

		line[match[1].rm_eo] = '\0';
		r = &line[match[1].rm_so];
		break;
	}

out:
    return r;
}

void setusershell(void) {
	int e = errno;
	if ( default_shells_idx != -1 ) {
		default_shells_idx = 0;
	} else {
		if ( !__the_shell ) {
			__the_shell = fopen(_PATH_SHELLS,"r");
			if ( __the_shell ) {
				fseek(__the_shell,0,SEEK_SET);
			} else {
				default_shells_idx = 0;
			}
		} else {
			default_shells_idx = 0;
		}
	}
	errno = e;
}

void endusershell(void) {
	int e = errno;
	fclose(__the_shell);
	__the_shell = NULL;
	default_shells_idx = -1;
	errno = e;
}
