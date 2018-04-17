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

  std::string name_get();
  const std::string name_get() const;

  std::string error_get();
  const std::string error_get() const;

  pstat stat_get();
  const pstat stat_get() const;

  memstat statm_get();
  const memstat statm_get() const;

  std::vector<Process> children_get();
  std::vector<Process> children_get() const;

  Process father_get();
  const Process father_get() const;

  bool is_valid();
  bool is_valid() const;

  void set_father(Process& father);
  void set_father(std::nullptr_t);

  void add_child(Process& child);

  std::string dump() const;
  friend std::ostream& operator<<(std::ostream&, const Process&);

  bool operator<(const Process& other);

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

#include "process.hxx"