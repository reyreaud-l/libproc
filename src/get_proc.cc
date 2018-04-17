#include "plib.hh"

namespace plib
{
std::vector<Process> get_all_processes()
{
  auto proc_dirs = get_proc_dirs(get_proc_root());
  std::vector<Process> res;
  for (auto p : proc_dirs)
  {
    res.emplace_back(p);
  }
  return res;
}

std::vector<Process> get_process(std::string name)
{
  auto processes = get_all_processes();
  auto res = std::vector<Process>();
  for (auto& proc : processes)
    if (proc.name_get() == name)
      res.push_back(proc);
  return res;
}

Process get_process(int uid)
{
  return Process(get_proc_dir(get_proc_root(), uid));
}
} // namespace plib
