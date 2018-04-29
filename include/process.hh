#pragma once

#include <algorithm>
#include <csignal>
#include <cstring> // strerror
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <sys/types.h>
#include <vector>

#include "error.hh"
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
  Process(Process&) = default;
  Process(const Process&) = default;
  Process& operator=(Process&) = default;
  Process& operator=(const Process&) = default;

  void kill();
  void kill(int sig);

  void refresh();

  std::string dump();
  const std::string dump() const;
  friend std::ostream& operator<<(std::ostream&, const Process&);

  bool operator<(const Process& other);

  /*{ Getters & Setters
   * */
  std::string name_get();
  const std::string name_get() const;

  std::string error_msg_get();
  const std::string error_msg_get() const;

  template <plib::Error::kind K>
  bool is_status();
  template <plib::Error::kind K>
  bool is_status() const;

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
  /* }
   * */

private:
  void parse_stat_file(FILE*);
  void parse_mem_file(FILE*);

  void fill_stat_map();
  void fill_mem_map();

  void set_error(plib::Error::kind, const std::string&);
  void set_error_errno(plib::Error::kind, const std::string&);

  void copy_fields(const Process&);
  std::string dump_() const;

  fs::path path_;
  std::string name_;
  plib::Error error_;

  pstat stat_;
  memstat statm_;

  std::vector<Process> children_;
  std::shared_ptr<Process> father_;
};
} // namespace plib

#include "process.hxx"
