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

/* Return a single fs::path object to a precise uid. */
fs::path get_proc_dir(const fs::path&, int uid);

/* Return all object Process */
std::vector<Process> get_all_processes();

/* Return a list of Process with a name matching a given name. This function
 * will read the entire proc tree. It is similar to get_all_processes and then
 * looking for a precise name. */
std::vector<Process> get_process(std::string);

/* Return a precise Process for a given uid */
Process get_process(int);

/* Return a copy of the vector given in parameter sorted by memory usage */
std::vector<Process> sort_by_mem(std::vector<Process>);

/* Return a copy of the vector given in parameter sorted by time spent in
 * userland */
std::vector<Process> sort_by_utime(std::vector<Process>);

/* Resolve links between childs and father process in the given vector */
std::vector<Process> resolve_father_sons(std::vector<Process>);
} // namespace plib
