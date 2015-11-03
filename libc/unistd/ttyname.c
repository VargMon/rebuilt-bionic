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

char *ttyname(int fd);

/***************/

#include <linux/limits.h> // NAME_MAX

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <pwd.h>

#include <stdio.h>

#include "branch_prediction.h"
#include "set_errno.h"

// it's unlikely that we'll ever need to switch this to PATH_MAX
static char ttypathname[NAME_MAX];

#ifndef min
#define min(a,b) ((a)<=(b) ? (a) : (b))
#endif

char *ttyname(int fd) {
	char *n = NULL;
	int r;
	pid_t pid;
	int procfd;
	ssize_t len;

	if ( !isatty(fd) )
		goto out;

	pid = getpid();

	// XXX: very linux-specific
	r = snprintf(ttypathname,sizeof(ttypathname),"/proc/%u/fd/%u",pid,fd);
	if ( unlikely(r < 0) )
		goto out;

	procfd = open(ttypathname,O_RDONLY);
	if ( procfd == -1 )
		goto out;

	len = readlink(ttypathname,ttypathname,sizeof(ttypathname));
	if ( unlikely(r == -1) )
		goto closeprocfd;

	ttypathname[min(sizeof(ttypathname),len)] = '\0';

	n = ttypathname;
	SET_ERRNO(0);

closeprocfd:
	close(procfd);

out:
	return n;
}
