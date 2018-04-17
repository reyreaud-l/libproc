#include "plib.hh"

namespace plib
{
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
    catch (std::out_of_range) // Catch exception from .at call
    {
      proc.set_father(nullptr);
    }
  }
  return src;
}
} // namespace plib
