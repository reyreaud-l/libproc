#include "shtop/kill/kill.hh"

namespace shtop::kill
{
void kill(std::string name, int signal)
{
  try
  {
    auto proc = plib::get_process(name);
    std::for_each(proc.begin(), proc.end(),
                  [signal](plib::Process& a) { a.kill(signal); });
  }
  catch (std::invalid_argument) // get_process throw if no process could be
                                // found
  {
    std::exit(1);
  }
}
} // namespace shtop::kill
