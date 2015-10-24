/*
 * Copyright (C) 2013 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#undef _FORTIFY_SOURCE
#include <errno.h>
#include <sys/poll.h>
#include <sys/select.h>

#include "private/bionic_time_conversions.h"
#include "private/kernel_sigset_t.h"

int __ppoll(struct pollfd*, unsigned int, struct timespec*, const union kernel_sigset_t*, size_t);
int __pselect6(int, fd_set*, fd_set*, fd_set*, struct timespec*, void*);

int poll(struct pollfd* fds, nfds_t fd_count, int ms) {
  struct timespec ts;
  struct timespec* ts_ptr = NULL;
  if (ms >= 0) {
    timespec_from_ms(&ts, ms);
    ts_ptr = &ts;
  }
  return __ppoll(fds, fd_count, ts_ptr, NULL, 0);
}

int ppoll(struct pollfd* fds, nfds_t fd_count, const struct timespec* ts, const sigset_t* ss) {
  struct timespec mutable_ts;
  struct timespec* mutable_ts_ptr = NULL;
  if (ts != NULL) {
    mutable_ts = *ts;
    mutable_ts_ptr = &mutable_ts;
  }

  union kernel_sigset_t kernel_ss;
  union kernel_sigset_t* kernel_ss_ptr = NULL;
  kernel_sigset_t_default_init(&kernel_ss);
  if (ss != NULL) {
    kernel_sigset_t_set(&kernel_ss, ss);
    kernel_ss_ptr = &kernel_ss;
  }

  return __ppoll(fds, fd_count, mutable_ts_ptr, kernel_ss_ptr, sizeof(kernel_ss));
}

int select(int fd_count, fd_set* read_fds, fd_set* write_fds, fd_set* error_fds, struct timeval* tv) {
  struct timespec ts;
  struct timespec* ts_ptr = NULL;
  if (tv != NULL) {
    if (!timespec_from_timeval(&ts, tv)) {
      errno = EINVAL;
      return -1;
    }
    ts_ptr = &ts;
  }
  int result = __pselect6(fd_count, read_fds, write_fds, error_fds, ts_ptr, NULL);
  if (tv != NULL) {
    timeval_from_timespec(tv, &ts);
  }
  return result;
}

int pselect(int fd_count, fd_set* read_fds, fd_set* write_fds, fd_set* error_fds,
            const struct timespec* ts, const sigset_t* ss) {
  struct timespec mutable_ts;
  struct timespec* mutable_ts_ptr = NULL;
  if (ts != NULL) {
    mutable_ts = *ts;
    mutable_ts_ptr = &mutable_ts;
  }

  union kernel_sigset_t kernel_ss;
  union kernel_sigset_t* kernel_ss_ptr = NULL;
  kernel_sigset_t_default_init(&kernel_ss);
  if (ss != NULL) {
    kernel_sigset_t_set(&kernel_ss, ss);
    kernel_ss_ptr = &kernel_ss;
  }

  // The Linux kernel only handles 6 arguments and this system call really needs 7,
  // so the last argument is a void* pointing to:
  struct pselect6_extra_data_t {
    uintptr_t ss_addr;
    size_t ss_len;
  };
  struct pselect6_extra_data_t extra_data;
  extra_data.ss_addr = (uintptr_t)(kernel_ss_ptr);
  extra_data.ss_len = sizeof(kernel_ss);

  return __pselect6(fd_count, read_fds, write_fds, error_fds, mutable_ts_ptr, &extra_data);
}
