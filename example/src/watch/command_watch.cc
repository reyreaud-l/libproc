#include "watch/command_watch.hh"

namespace shtop::watch
{
CommandWatch::CommandWatch()
  : cmdline("shtop watch command", ' ', "0.1")
  , name("name", "Name of process to inspect", true, "shtop", "PROCESS")
{
  cmdline.add(name);
}

void CommandWatch::parse(int argc, char* argv[])
{
  cmdline.parse(argc, argv);
}

void CommandWatch::execute()
{
  watch(name.getValue());
}
} // namespace shtop::watch
