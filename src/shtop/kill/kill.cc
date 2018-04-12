#include "shtop/kill/kill.hh"

namespace shtop::kill
{
void kill(std::string name, int signal)
{
  auto proc = plib::get_process(name);
  proc.kill(signal);
  std::cout << name << std::endl;
  std::cout << signal << std::endl;
}
} // namespace shtop::kill
