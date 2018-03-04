#include "plib/plib.hh"

namespace plib
{
fs::path get_proc_root()
{
  return fs::path("/proc");
}

std::vector<fs::path> get_proc_dirs(const fs::path& root)
{
  if (!fs::is_directory(root))
  {
    throw std::invalid_argument("Expected directory");
  }
  std::vector<fs::path> res;
  for (const auto& entry : fs::directory_iterator(root))
  {
    auto p = entry.path();
    if (!p.has_filename())
      continue;
    const auto& str_p = p.filename().string();
    if (!std::all_of(str_p.begin(), str_p.end(), ::isdigit))
      continue;
    res.push_back(p);
  }
  return res;
}

std::vector<Process> get_all_processes()
{
  auto proc_dirs = get_proc_dirs(get_proc_root());
  std::vector<Process> res;
  for (auto p : proc_dirs)
  {
    res.push_back(Process(p));
  }
  return res;
}
}
