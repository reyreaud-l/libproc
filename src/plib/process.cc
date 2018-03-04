#include "plib/process.hh"

namespace plib
{
Process::Process(fs::path p)
  : path_(p)
{
  fill_status_map();
}

void Process::refresh()
{
  fill_status_map();
}

void Process::fill_status_map()
{
  auto pfile = std::fopen(std::string(path_.string() + "/stat").c_str(), "r");
  if (pfile == NULL)
  {
    set_error_errno(
      std::string("Could not open file " + path_.string() + ": "));
    return;
  }
  parse_file(pfile);
  fclose(pfile);
}

void Process::parse_file(FILE* pfile)
{
  char sfile[MAX_PROC_FILE_LEN];
  char* s = NULL;
  char* t = NULL;
  if ((s = fgets(sfile, MAX_PROC_FILE_LEN, pfile)) == NULL)
  {
    set_error_errno(std::string(""));
    return;
  }

  if (sscanf(sfile, "%d", &(stat_.pid)) == EOF)
  {
    set_error_errno(std::string(""));
    return;
  }

  s = strchr(sfile, '(') + 1;
  t = strchr(sfile, ')');
  strncpy(stat_.comm, s, t - s);
  stat_.comm[t - s] = '\0';
  auto res = std::sscanf(
    sfile,
    "%c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld "
    "%ld %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d "
    "%d %u %u %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %d",
    &(stat_.state), &(stat_.ppid), &(stat_.pgrp), &(stat_.session),
    &(stat_.tty_nr), &(stat_.tpgid), &(stat_.flags), &(stat_.minflt),
    &(stat_.cminflt), &(stat_.majflt), &(stat_.cmajflt), &(stat_.utime),
    &(stat_.stime), &(stat_.cutime), &(stat_.cstime), &(stat_.priority),
    &(stat_.nice), &(stat_.num_threads), &(stat_.itrealvalue),
    &(stat_.starttime), &(stat_.vsize), &(stat_.rss), &(stat_.rsslim),
    &(stat_.startcode), &(stat_.endcode), &(stat_.startstack), &(stat_.kstkesp),
    &(stat_.kstkeip), &(stat_.signal), &(stat_.blocked), &(stat_.sigignore),
    &(stat_.sigcatch), &(stat_.wchan), &(stat_.nswap), &(stat_.cnswap),
    &(stat_.exit_signal), &(stat_.processor), &(stat_.rt_priority),
    &(stat_.policy), &(stat_.delayacct_blkio_ticks), &(stat_.guest_time),
    &(stat_.cguest_time), &(stat_.start_data), &(stat_.end_data),
    &(stat_.start_brk), &(stat_.arg_start), &(stat_.arg_end),
    &(stat_.env_start), &(stat_.env_end), &(stat_.exit_code));
  if (res == EOF)
  {
    set_error_errno(std::string("Error reading " + path_.string() + ": "));
    return;
  }
}

void Process::set_error(std::string err)
{
  valid_ = false;
  error_ = err;
}

void Process::set_error_errno(std::string err)
{
  set_error(std::string(err + strerror(errno)));
}

std::ostream& operator<<(std::ostream& ostr_, const Process& p)
{
  auto s = p.stat_get();
  return ostr_ << "pid: " << s.pid << " cmd: " << s.comm;
}
}
