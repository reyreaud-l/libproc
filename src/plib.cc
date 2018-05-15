#include "plib.hh"

namespace plib
{
std::vector<Process> get_all_processes()
{
  auto proc_dirs = get_proc_dirs(get_proc_root());
  std::vector<Process> res;
  res.reserve(proc_dirs.size());
  for (auto p : proc_dirs)
  {
    res.emplace_back(p);
  }
  return res;
}

std::vector<Process> get_process(const std::string& name)
{
  auto processes = get_all_processes();
  auto res = std::vector<Process>();
  for (auto& proc : processes)
  {
    if (proc.name_get() == name)
    {
      res.push_back(proc);
    }
  }
  return res;
}

Process get_process(int uid)
{
  return Process(get_proc_dir(get_proc_root(), uid));
}

std::vector<Process> resolve_father_sons(std::vector<Process> src)
{
  std::map<size_t, Process&> proc_map;
  for (Process& proc : src)
  {
    proc_map.emplace(proc.stat_get().pid, proc);
  }
  for (Process& proc : src)
  {
    try
    {
      auto& father = proc_map.at(proc.stat_get().ppid);
      proc.set_father(father);
      father.add_child(proc);
    }
    catch (std::out_of_range&) // Catch exception from .at call
    {
      proc.set_father(nullptr);
    }
  }
  return src;
}
} // namespace plib
