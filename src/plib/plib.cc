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

fs::path get_proc_dir(const fs::path& root, int uid)
{
  if (!fs::is_directory(root))
  {
    throw std::invalid_argument("Expected directory");
  }
  fs::path res;
  for (const auto& entry : fs::directory_iterator(root))
  {
    auto p = entry.path();
    if (!p.has_filename())
      continue;
    const auto& str_p = p.filename().string();
    if (!std::all_of(str_p.begin(), str_p.end(), ::isdigit))
      continue;
    if (str_p != std::to_string(uid))
      continue;
    res = p;
  }
  return res;
}

std::vector<Process> resolve_father_sons(std::vector<Process> src)
{
  std::map<size_t, Process&> proc_map;
  for (Process& proc : src)
    proc_map.emplace(proc.stat_get().pid, proc);
  for (Process& proc : src)
  {
    try
    {
      auto& father = proc_map.at(proc.stat_get().ppid);
      proc.set_father(father);
      father.add_child(proc);
    }
    catch (std::out_of_range e)
    {
      proc.set_father(nullptr);
    }
  }
  return src;
}
} // namespace plib
