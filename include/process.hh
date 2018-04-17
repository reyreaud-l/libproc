#pragma once

#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <signal.h>
#include <string.h> // strerror
#include <string>
#include <sys/types.h>
#include <vector>

#include "helper.hh"
#include "mstat.hh"
#include "pstat.hh"

#define MAX_PROC_FILE_LEN (2048)
namespace plib
{
namespace fs = std::experimental::filesystem;

class Process
{
public:
  Process(fs::path);
  Process(const Process&);
  Process& operator=(Process&);
  Process& operator=(const Process&);

  void kill();
  void kill(int sig);
  void kill() const;
  void kill(int sig) const;
  void refresh();
  std::string dump() const;
  friend std::ostream& operator<<(std::ostream&, const Process&);

  inline const std::string name_get()
  {
    return name_;
  }

  inline const std::string name_get() const
  {
    return name_;
  }

  inline bool is_valid()
  {
    return valid_;
  }

  inline bool is_valid() const
  {
    return valid_;
  }

  inline const std::string error_get()
  {
    return error_;
  }

  inline const std::string error_get() const
  {
    return error_;
  }

  inline const pstat stat_get()
  {
    return stat_;
  }

  inline const pstat stat_get() const
  {
    return stat_;
  }

  inline const memstat statm_get()
  {
    return statm_;
  }

  inline const memstat statm_get() const
  {
    return statm_;
  }

  inline std::vector<Process> children_get()
  {
    return children_;
  }

  inline std::vector<Process> children_get() const
  {
    return children_;
  }

  inline Process father_get()
  {
    return *(father_.get());
  }

  inline const Process father_get() const
  {
    return *(father_.get());
  }

  inline void set_father(Process& father)
  {
    father_ = std::make_unique<Process>(father);
  }

  inline void set_father(std::nullptr_t)
  {
    father_ = nullptr;
  }

  inline void add_child(Process& child)
  {
    children_.push_back(child);
  }

  inline bool operator<(const Process& other)
  {
    return this->stat_.pid < other.stat_.pid;
  }

private:
  void parse_stat_file(FILE*);
  void fill_stat_map();
  void parse_mem_file(FILE*);
  void fill_mem_map();
  void set_error_errno(std::string);
  void set_error(std::string);
  void copy_fields(const Process&);

  fs::path path_;
  std::string name_;
  bool valid_ = true;
  std::string error_;
  pstat stat_;
  memstat statm_;
  std::vector<Process> children_;
  std::shared_ptr<Process> father_;
};
} // namespace plib
