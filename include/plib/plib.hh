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

std::vector<Process> resolve_father_sons(std::vector<Process>);
}
