#pragma once

#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string.h> // strerror
#include <string>
#include <vector>

#include "plib/helper.hh"
#include "plib/mstat.hh"
#include "plib/pstat.hh"

#define MAX_PROC_FILE_LEN (2048)
namespace plib
{
namespace fs = std::experimental::filesystem;

class Process
{
public:
  Process(fs::path);
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

private:
  void parse_stat_file(FILE*);
  void fill_stat_map();
  void parse_mem_file(FILE*);
  void fill_mem_map();
  void set_error_errno(std::string);
  void set_error(std::string);

  fs::path path_;
  std::string name_;
  bool valid_ = true;
  std::string error_;
  pstat stat_;
  memstat statm_;
};
}