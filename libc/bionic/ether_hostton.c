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
#include <netinet/ether.h>

#include "set_errno.h"

int ether_hostton(const char *hostname, struct ether_addr *addr);

/**************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ether_private.h"
#include "stub.h"

static inline size_t min( size_t a, size_t b ) {
	return a <= b ? a : b;
}

static inline void reset_hostname(char *hn) {
	int i;
	for(i=0; i<POSIX_HOST_NAME_MAX; i++) {
		hn[i] = ' ';
	}
	hn[POSIX_HOST_NAME_MAX] = '\0';
}

int ether_hostton(const char *hostname, struct ether_addr *addr) {

	int r = -1, invalid_ether_line;
	char *hnt;
	char *line = NULL;
	size_t buflen = 0;
	ssize_t linelen;
	struct ether_addr taddr = {};

	FILE *ethers = NULL;

	BIONICSTUB();
	fprintf(stderr,"this is still waiting for ether_line.c\n");

	if ( !( hostname && addr ) )
		goto out;

	ethers = fopen(ETHERS_FILENAME,"r");
	if ( !ethers ) {
		errno = 0;
		goto out;
	}

	hnt = malloc(POSIX_HOST_NAME_MAX + 1);
	if ( !hnt ) {
		goto close_ethers;
	}

	for(;;) {
		reset_hostname(hnt);
		if ( line ) {
			free(line);
			line = NULL;
		}

		linelen = getline(&line,&buflen,ethers);

		// end of file reached
		if ( linelen == -1 )
			break;

		invalid_ether_line =
			ether_line(line,&taddr,hnt);

		if ( invalid_ether_line )
			continue;

		if ( strncmp(hostname,hnt,
				min(strlen(hnt),strlen(hostname))) == 0 ) {
			memcpy(addr,&taddr,sizeof(struct ether_addr));
			r = 0;
			break;
		}
	}

	if ( line ) {
		free(line);
		line = NULL;
	}

	if ( hnt ) {
		free(hnt);
		hnt = NULL;
	}

close_ethers:
	if ( ethers ) {
		fclose(ethers);
		ethers = NULL;
	}

out:

	SHOULD_CLEAR_ERRNO();

    return r;
}
