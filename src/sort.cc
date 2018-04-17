#include "plib.hh"

namespace plib
{
std::vector<Process> sort_by_mem(std::vector<Process> src)
{
  std::sort(src.begin(), src.end(), [](const Process& a, const Process& b) {
    return a.statm_get().size > b.statm_get().size;
  });
  return src;
}

std::vector<Process> sort_by_utime(std::vector<Process> src)
{
  std::sort(src.begin(), src.end(), [](const Process& a, const Process& b) {
    return a.stat_get().utime > b.stat_get().utime;
  });
  return src;
}
} // namespace plib
