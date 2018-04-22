#include "process.hh"

namespace plib
{
Process::Process(fs::path p)
  : path_(p)
{
  refresh();
}

Process::Process(const Process& other)
{
  this->copy_fields(other);
}

Process& Process::operator=(Process& other)
{
  this->copy_fields(other);
  return *this;
}

Process& Process::operator=(const Process& other)
{
  this->copy_fields(other);
  return *this;
}

void Process::kill()
{
  this->kill(SIGTERM);
}

void Process::kill(int sig)
{
  ::kill(this->stat_.pid, sig);
  set_error(plib::Error::kind::killed, "killed");
}

void Process::wait_and_refresh()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(delay_));
  this->refresh();
}

void Process::watcher()
{
  while (this->watch_)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_));
    this->refresh();
  }
}

void Process::watch()
{
  // Launch process to regularly poll update from /proc files
  this->watch_start();
  std::thread t1(&Process::watcher, this);
}

void Process::on_update(std::function<void(Process)> notifee)
{
  this->notifee_ = notifee;
}

void Process::refresh()
{
  std::lock_guard<std::mutex> lock(this->watch_mutex_);
  fill_stat_map();
  fill_mem_map();
  notifee_(*this);
}

void Process::fill_stat_map()
{
  auto pfile = std::fopen(std::string(path_.string() + "/stat").c_str(), "r");
  if (pfile == NULL)
  {
    set_error_errno(
      plib::Error::kind::fatal,
      std::string("Could not open file " + path_.string() + ": "));
    return;
  }
  parse_stat_file(pfile);
  fclose(pfile);
}

void Process::fill_mem_map()
{
  auto pfile = std::fopen(std::string(path_.string() + "/statm").c_str(), "r");
  if (pfile == NULL)
  {
    set_error_errno(
      plib::Error::kind::fatal,
      std::string("Could not open file " + path_.string() + ": "));
    return;
  }
  parse_mem_file(pfile);
  this->name_ = stat_.comm;
  fclose(pfile);
}

void Process::parse_mem_file(FILE* pfile)
{
  char sfile[MAX_PROC_FILE_LEN];
  char* s = NULL;
  if ((s = fgets(sfile, MAX_PROC_FILE_LEN, pfile)) == NULL)
  {
    set_error_errno(plib::Error::kind::fatal, std::string(""));
    return;
  }
  if (std::sscanf(sfile, "%lu %lu %lu %lu %lu %lu %lu", &(statm_.size),
                  &(statm_.resident), &(statm_.shared), &(statm_.text),
                  &(statm_.lib), &(statm_.data), &(statm_.dt)))
  {
    set_error_errno(plib::Error::kind::fatal, std::string(""));
    return;
  }
}

void Process::parse_stat_file(FILE* pfile)
{
  char sfile[MAX_PROC_FILE_LEN];
  char* s = NULL;
  char* t = NULL;
  if ((s = fgets(sfile, MAX_PROC_FILE_LEN, pfile)) == NULL)
  {
    set_error_errno(plib::Error::kind::fatal, std::string(""));
    return;
  }

  if (std::sscanf(sfile, "%d", &(stat_.pid)) == EOF)
  {
    set_error_errno(plib::Error::kind::fatal, std::string(""));
    return;
  }

  s = strchr(sfile, '(') + 1;
  t = strchr(sfile, ')');
  strncpy(stat_.comm, s, t - s);
  stat_.comm[t - s] = '\0';
  auto res = std::sscanf(
    t + 2,
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
    set_error_errno(plib::Error::kind::fatal,
                    std::string("Error reading " + path_.string() + ": "));
    return;
  }
}

std::string Process::dump_() const
{
  std::lock_guard<std::mutex> lock(this->watch_mutex_);
  std::string res;
  res += std::string(stat_.comm) + '\n';
  res += "  pid: " + std::to_string(stat_.pid) + '\n';
  res += "  state: " + std::string(1, stat_.state) + '\n';
  res += "  size: " + calculate_size(statm_.size * page_size()) + '\n';
  res += "  resident: " + calculate_size(statm_.resident * page_size()) + '\n';
  res += "  shared: " + calculate_size(statm_.shared * page_size()) + '\n';
  res += "  text: " + calculate_size(statm_.text * page_size()) + '\n';
  res += "  data: " + calculate_size(statm_.data * page_size()) + '\n';
  res += "  threads: " + std::to_string(stat_.num_threads) + '\n';
  if (father_ != nullptr)
    res += "  ppid: " + std::to_string(father_->stat_get().pid) + '\n';
  else
    res += "  ppid: 0\n";
  res += "  childp: ";
  for (const auto& child : children_)
  {
    res += std::to_string(child.stat_get().pid);
    if (&child != &(children_.back()))
      res += ", ";
  }
  res += '\n';
  return res;
}

std::string Process::dump()
{
  return this->dump_();
}

const std::string Process::dump() const
{
  return this->dump_();
}

void Process::set_error(plib::Error::kind kind, std::string msg)
{
  this->watch_stop();
  this->error_.set_error(kind, msg);
}

void Process::set_error_errno(plib::Error::kind kind, std::string msg)
{
  this->watch_stop();
  this->error_.set_error_errno(kind, msg);
}

std::ostream& operator<<(std::ostream& ostr_, const Process& p)
{
  return ostr_ << p.dump();
}

void Process::copy_fields(const Process& other)
{
  // FIXME: Update with all fields
  this->path_ = other.path_;
  this->name_ = other.name_;
  this->stat_ = other.stat_;
  this->statm_ = other.statm_;
  this->children_ = other.children_;
  this->father_ = other.father_;
}
} // namespace plib
