#include "watch/watch.hh"

namespace shtop::watch
{
void watch(std::string name)
{
  try
  {
    auto proc = plib::get_process(name);
  }
  catch (std::invalid_argument) // get_process throw if no process could be
                                // found
  {
    std::exit(1);
  }
}
} // namespace shtop::watch
