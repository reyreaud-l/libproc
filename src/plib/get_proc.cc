#include "plib/plib.hh"

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

Process get_process(std::string name)
{
  auto processes = get_all_processes();
  processes = resolve_father_sons(processes);
  auto proc =
    std::find_if(processes.begin(), processes.end(),
                 [&name](const Process& p) { return p.name_get() == name; });
  if (proc != processes.end())
    return *proc;
  throw std::invalid_argument("Could not find a process for name: " + name);
}

Process get_process(int uid)
{
  try
  {
    return get_proc_dir(get_proc_root(), uid);
  }
  catch (std::invalid_argument)
  {
    throw std::invalid_argument("Could not find a process for uid: " +
                                std::to_string(uid));
  }
}
} // namespace plib
