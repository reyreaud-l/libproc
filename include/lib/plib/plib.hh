#pragma once

#include <algorithm>
#include <experimental/filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "process.hh"

namespace plib
{
namespace fs = std::experimental::filesystem;

/* Return a path object for /proc */
fs::path get_proc_root();

/* Return all dirs containing only numbers (ie. pid) in the root) */
std::vector<fs::path> get_proc_dirs(const fs::path&);

/* Return all object Process */
std::vector<Process> get_all_processes();

/* Return a copy of the vector given in parameter sorted by memory usage */
std::vector<Process> sort_by_mem(std::vector<Process>);

/* Return a copy of the vector given in parameter sorted by time spent in
 * userland */
std::vector<Process> sort_by_utime(std::vector<Process>);

/* Resolve links between childs and father process in the given vector */
std::vector<Process> resolve_father_sons(std::vector<Process>);
} // namespace plib
