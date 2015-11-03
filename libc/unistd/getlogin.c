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

char *getlogin(void);

/***************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <pwd.h>

#include "set_errno.h"

char* getlogin(void) {
	char *n = NULL;
	int r, fd;
	struct stat stat;
	uid_t uid;
	struct passwd *p;

	/* XXX: Do not use getuid(), because that uid might be different than
	 * that of the controlling terminal, which might not even exist. */

	r = open("/dev/tty",O_RDONLY);
	if ( r == -1 )
		goto out;
	fd = r;

	r = fstat(fd,&stat);
	if ( r == -1 )
		goto closefd;

	uid = stat.st_uid;

	p = getpwuid(uid);
	if ( !p )
		goto closefd;

	n = p->pw_name;
	SET_ERRNO(0);

closefd:
	close(fd);

out:
	return n;
}
