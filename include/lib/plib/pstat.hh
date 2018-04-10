#pragma once

#include <linux/limits.h>
#include <string>

namespace plib
{
struct pstat
{
  int pid;
  char comm[PATH_MAX];
  char state;
  int ppid;
  int pgrp;
  int session;
  int tty_nr;
  int tpgid;
  unsigned flags;
  size_t minflt;
  size_t cminflt;
  size_t majflt;
  size_t cmajflt;
  size_t utime;
  size_t stime;
  long int cutime;
  long int cstime;
  long priority;
  long nice;
  long num_threads;
  long itrealvalue;
  unsigned long long starttime;
  size_t vsize;
  long rss;
  size_t rsslim;
  size_t startcode;
  size_t endcode;
  size_t startstack;
  size_t kstkesp;
  size_t kstkeip;
  size_t signal;
  size_t blocked;
  size_t sigignore;
  size_t sigcatch;
  size_t wchan;
  size_t nswap;
  size_t cnswap;
  int exit_signal;
  int processor;
  unsigned rt_priority;
  unsigned policy;
  long long unsigned delayacct_blkio_ticks;
  size_t guest_time;
  long cguest_time;
  size_t start_data;
  size_t end_data;
  size_t start_brk;
  size_t arg_start;
  size_t arg_end;
  size_t env_start;
  size_t env_end;
  int exit_code;
};
}
