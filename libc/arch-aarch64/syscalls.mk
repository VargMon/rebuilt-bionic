# Generated by gensyscalls.py. Do not edit.
syscall_src :=
syscall_src += arch-aarch64/syscalls/__brk.S
syscall_src += arch-aarch64/syscalls/__clone.S
syscall_src += arch-aarch64/syscalls/__epoll_pwait.S
syscall_src += arch-aarch64/syscalls/__exit.S
syscall_src += arch-aarch64/syscalls/__getcpu.S
syscall_src += arch-aarch64/syscalls/__getcwd.S
syscall_src += arch-aarch64/syscalls/__getpriority.S
syscall_src += arch-aarch64/syscalls/__ioctl.S
syscall_src += arch-aarch64/syscalls/__openat.S
syscall_src += arch-aarch64/syscalls/__ppoll.S
syscall_src += arch-aarch64/syscalls/__pselect6.S
syscall_src += arch-aarch64/syscalls/__ptrace.S
syscall_src += arch-aarch64/syscalls/__reboot.S
syscall_src += arch-aarch64/syscalls/__rt_sigaction.S
syscall_src += arch-aarch64/syscalls/__rt_sigpending.S
syscall_src += arch-aarch64/syscalls/__rt_sigprocmask.S
syscall_src += arch-aarch64/syscalls/__rt_sigsuspend.S
syscall_src += arch-aarch64/syscalls/__rt_sigtimedwait.S
syscall_src += arch-aarch64/syscalls/__sched_getaffinity.S
syscall_src += arch-aarch64/syscalls/__set_tid_address.S
syscall_src += arch-aarch64/syscalls/__syslog.S
syscall_src += arch-aarch64/syscalls/__timer_create.S
syscall_src += arch-aarch64/syscalls/__timer_delete.S
syscall_src += arch-aarch64/syscalls/__timer_getoverrun.S
syscall_src += arch-aarch64/syscalls/__timer_gettime.S
syscall_src += arch-aarch64/syscalls/__timer_settime.S
syscall_src += arch-aarch64/syscalls/__waitid.S
syscall_src += arch-aarch64/syscalls/_exit.S
syscall_src += arch-aarch64/syscalls/accept.S
syscall_src += arch-aarch64/syscalls/accept4.S
syscall_src += arch-aarch64/syscalls/acct.S
syscall_src += arch-aarch64/syscalls/adjtimex.S
syscall_src += arch-aarch64/syscalls/bdflush.S
syscall_src += arch-aarch64/syscalls/bind.S
syscall_src += arch-aarch64/syscalls/capget.S
syscall_src += arch-aarch64/syscalls/capset.S
syscall_src += arch-aarch64/syscalls/chdir.S
syscall_src += arch-aarch64/syscalls/chroot.S
syscall_src += arch-aarch64/syscalls/clock_adjtime.S
syscall_src += arch-aarch64/syscalls/clock_getres.S
syscall_src += arch-aarch64/syscalls/clock_gettime.S
syscall_src += arch-aarch64/syscalls/clock_nanosleep.S
syscall_src += arch-aarch64/syscalls/clock_settime.S
syscall_src += arch-aarch64/syscalls/close.S
syscall_src += arch-aarch64/syscalls/connect.S
syscall_src += arch-aarch64/syscalls/delete_module.S
syscall_src += arch-aarch64/syscalls/dup.S
syscall_src += arch-aarch64/syscalls/dup3.S
syscall_src += arch-aarch64/syscalls/epoll_create1.S
syscall_src += arch-aarch64/syscalls/epoll_ctl.S
syscall_src += arch-aarch64/syscalls/eventfd.S
syscall_src += arch-aarch64/syscalls/execve.S
syscall_src += arch-aarch64/syscalls/faccessat.S
syscall_src += arch-aarch64/syscalls/fallocate.S
syscall_src += arch-aarch64/syscalls/fchdir.S
syscall_src += arch-aarch64/syscalls/fchmod.S
syscall_src += arch-aarch64/syscalls/fchmodat.S
syscall_src += arch-aarch64/syscalls/fchown.S
syscall_src += arch-aarch64/syscalls/fchownat.S
syscall_src += arch-aarch64/syscalls/fcntl.S
syscall_src += arch-aarch64/syscalls/fdatasync.S
syscall_src += arch-aarch64/syscalls/fgetxattr.S
syscall_src += arch-aarch64/syscalls/flistxattr.S
syscall_src += arch-aarch64/syscalls/flock.S
syscall_src += arch-aarch64/syscalls/fremovexattr.S
syscall_src += arch-aarch64/syscalls/fsetxattr.S
syscall_src += arch-aarch64/syscalls/fstat.S
syscall_src += arch-aarch64/syscalls/fstatat.S
syscall_src += arch-aarch64/syscalls/fstatfs.S
syscall_src += arch-aarch64/syscalls/fsync.S
syscall_src += arch-aarch64/syscalls/ftruncate.S
syscall_src += arch-aarch64/syscalls/futex.S
syscall_src += arch-aarch64/syscalls/futimesat.S
syscall_src += arch-aarch64/syscalls/getdents.S
syscall_src += arch-aarch64/syscalls/getegid.S
syscall_src += arch-aarch64/syscalls/geteuid.S
syscall_src += arch-aarch64/syscalls/getgid.S
syscall_src += arch-aarch64/syscalls/getgroups.S
syscall_src += arch-aarch64/syscalls/getitimer.S
syscall_src += arch-aarch64/syscalls/getpeername.S
syscall_src += arch-aarch64/syscalls/getpgid.S
syscall_src += arch-aarch64/syscalls/getpid.S
syscall_src += arch-aarch64/syscalls/getppid.S
syscall_src += arch-aarch64/syscalls/getresgid.S
syscall_src += arch-aarch64/syscalls/getresuid.S
syscall_src += arch-aarch64/syscalls/getrlimit.S
syscall_src += arch-aarch64/syscalls/getrusage.S
syscall_src += arch-aarch64/syscalls/getsid.S
syscall_src += arch-aarch64/syscalls/getsockname.S
syscall_src += arch-aarch64/syscalls/getsockopt.S
syscall_src += arch-aarch64/syscalls/gettid.S
syscall_src += arch-aarch64/syscalls/gettimeofday.S
syscall_src += arch-aarch64/syscalls/getuid.S
syscall_src += arch-aarch64/syscalls/getxattr.S
syscall_src += arch-aarch64/syscalls/init_module.S
syscall_src += arch-aarch64/syscalls/inotify_add_watch.S
syscall_src += arch-aarch64/syscalls/inotify_init1.S
syscall_src += arch-aarch64/syscalls/inotify_rm_watch.S
syscall_src += arch-aarch64/syscalls/ioprio_get.S
syscall_src += arch-aarch64/syscalls/ioprio_set.S
syscall_src += arch-aarch64/syscalls/kill.S
syscall_src += arch-aarch64/syscalls/klogctl.S
syscall_src += arch-aarch64/syscalls/lgetxattr.S
syscall_src += arch-aarch64/syscalls/linkat.S
syscall_src += arch-aarch64/syscalls/listen.S
syscall_src += arch-aarch64/syscalls/listxattr.S
syscall_src += arch-aarch64/syscalls/llistxattr.S
syscall_src += arch-aarch64/syscalls/lremovexattr.S
syscall_src += arch-aarch64/syscalls/lseek.S
syscall_src += arch-aarch64/syscalls/lsetxattr.S
syscall_src += arch-aarch64/syscalls/madvise.S
syscall_src += arch-aarch64/syscalls/mincore.S
syscall_src += arch-aarch64/syscalls/mkdirat.S
syscall_src += arch-aarch64/syscalls/mknodat.S
syscall_src += arch-aarch64/syscalls/mlock.S
syscall_src += arch-aarch64/syscalls/mlockall.S
syscall_src += arch-aarch64/syscalls/mmap.S
syscall_src += arch-aarch64/syscalls/mount.S
syscall_src += arch-aarch64/syscalls/mprotect.S
syscall_src += arch-aarch64/syscalls/mremap.S
syscall_src += arch-aarch64/syscalls/msync.S
syscall_src += arch-aarch64/syscalls/munlock.S
syscall_src += arch-aarch64/syscalls/munlockall.S
syscall_src += arch-aarch64/syscalls/munmap.S
syscall_src += arch-aarch64/syscalls/name_to_handle_at.S
syscall_src += arch-aarch64/syscalls/nanosleep.S
syscall_src += arch-aarch64/syscalls/open_by_handle_at.S
syscall_src += arch-aarch64/syscalls/perf_event_open.S
syscall_src += arch-aarch64/syscalls/personality.S
syscall_src += arch-aarch64/syscalls/pipe2.S
syscall_src += arch-aarch64/syscalls/pivot_root.S
syscall_src += arch-aarch64/syscalls/prctl.S
syscall_src += arch-aarch64/syscalls/pread64.S
syscall_src += arch-aarch64/syscalls/preadv.S
syscall_src += arch-aarch64/syscalls/pwrite64.S
syscall_src += arch-aarch64/syscalls/pwritev.S
syscall_src += arch-aarch64/syscalls/quotactl.S
syscall_src += arch-aarch64/syscalls/read.S
syscall_src += arch-aarch64/syscalls/readahead.S
syscall_src += arch-aarch64/syscalls/readlinkat.S
syscall_src += arch-aarch64/syscalls/readv.S
syscall_src += arch-aarch64/syscalls/recvfrom.S
syscall_src += arch-aarch64/syscalls/recvmmsg.S
syscall_src += arch-aarch64/syscalls/recvmsg.S
syscall_src += arch-aarch64/syscalls/remap_file_pages.S
syscall_src += arch-aarch64/syscalls/removexattr.S
syscall_src += arch-aarch64/syscalls/renameat.S
syscall_src += arch-aarch64/syscalls/sched_get_priority_max.S
syscall_src += arch-aarch64/syscalls/sched_get_priority_min.S
syscall_src += arch-aarch64/syscalls/sched_getparam.S
syscall_src += arch-aarch64/syscalls/sched_getscheduler.S
syscall_src += arch-aarch64/syscalls/sched_rr_get_interval.S
syscall_src += arch-aarch64/syscalls/sched_setaffinity.S
syscall_src += arch-aarch64/syscalls/sched_setparam.S
syscall_src += arch-aarch64/syscalls/sched_setscheduler.S
syscall_src += arch-aarch64/syscalls/sched_yield.S
syscall_src += arch-aarch64/syscalls/sendfile.S
syscall_src += arch-aarch64/syscalls/sendmmsg.S
syscall_src += arch-aarch64/syscalls/sendmsg.S
syscall_src += arch-aarch64/syscalls/sendto.S
syscall_src += arch-aarch64/syscalls/setfsgid.S
syscall_src += arch-aarch64/syscalls/setfsuid.S
syscall_src += arch-aarch64/syscalls/setgid.S
syscall_src += arch-aarch64/syscalls/setgroups.S
syscall_src += arch-aarch64/syscalls/sethostname.S
syscall_src += arch-aarch64/syscalls/setitimer.S
syscall_src += arch-aarch64/syscalls/setns.S
syscall_src += arch-aarch64/syscalls/setpgid.S
syscall_src += arch-aarch64/syscalls/setpriority.S
syscall_src += arch-aarch64/syscalls/setregid.S
syscall_src += arch-aarch64/syscalls/setresgid.S
syscall_src += arch-aarch64/syscalls/setresuid.S
syscall_src += arch-aarch64/syscalls/setreuid.S
syscall_src += arch-aarch64/syscalls/setrlimit.S
syscall_src += arch-aarch64/syscalls/setsid.S
syscall_src += arch-aarch64/syscalls/setsockopt.S
syscall_src += arch-aarch64/syscalls/settimeofday.S
syscall_src += arch-aarch64/syscalls/setuid.S
syscall_src += arch-aarch64/syscalls/setxattr.S
syscall_src += arch-aarch64/syscalls/shutdown.S
syscall_src += arch-aarch64/syscalls/sigaltstack.S
syscall_src += arch-aarch64/syscalls/signalfd4.S
syscall_src += arch-aarch64/syscalls/socket.S
syscall_src += arch-aarch64/syscalls/socketpair.S
syscall_src += arch-aarch64/syscalls/splice.S
syscall_src += arch-aarch64/syscalls/statfs.S
syscall_src += arch-aarch64/syscalls/swapoff.S
syscall_src += arch-aarch64/syscalls/swapon.S
syscall_src += arch-aarch64/syscalls/symlinkat.S
syscall_src += arch-aarch64/syscalls/sync.S
syscall_src += arch-aarch64/syscalls/syncfs.S
syscall_src += arch-aarch64/syscalls/sysinfo.S
syscall_src += arch-aarch64/syscalls/tee.S
syscall_src += arch-aarch64/syscalls/tgkill.S
syscall_src += arch-aarch64/syscalls/timerfd_create.S
syscall_src += arch-aarch64/syscalls/timerfd_gettime.S
syscall_src += arch-aarch64/syscalls/timerfd_settime.S
syscall_src += arch-aarch64/syscalls/times.S
syscall_src += arch-aarch64/syscalls/tkill.S
syscall_src += arch-aarch64/syscalls/truncate.S
syscall_src += arch-aarch64/syscalls/umask.S
syscall_src += arch-aarch64/syscalls/umount2.S
syscall_src += arch-aarch64/syscalls/uname.S
syscall_src += arch-aarch64/syscalls/unlinkat.S
syscall_src += arch-aarch64/syscalls/unshare.S
syscall_src += arch-aarch64/syscalls/ustat.S
syscall_src += arch-aarch64/syscalls/utimensat.S
syscall_src += arch-aarch64/syscalls/vhangup.S
syscall_src += arch-aarch64/syscalls/vmsplice.S
syscall_src += arch-aarch64/syscalls/wait4.S
syscall_src += arch-aarch64/syscalls/write.S
syscall_src += arch-aarch64/syscalls/writev.S
