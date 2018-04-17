#include "kill/command_kill.hh"

namespace shtop::kill
{
CommandKill::CommandKill()
  : cmdline("shtop kill command", ' ', "0.1")
  , name("name", "Name of process to inspect", true, "shtop", "PROCESS")
  , signal("s", "signal", "Signal to send to process", false, SIGTERM, "int")
{
  cmdline.add(name);
  cmdline.add(signal);
}

void CommandKill::parse(int argc, char* argv[])
{
  cmdline.parse(argc, argv);
}

void CommandKill::execute()
{
  // Call kill module entry point, and forward options
  kill(name.getValue(), signal.getValue());
}
} // namespace shtop::kill
