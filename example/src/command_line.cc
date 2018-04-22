#include "command_line.hh"

namespace shtop
{
CommandLine::CommandLine(int argc, char* argv[])
  : CommandLine()
{
  auto cmd = argv[1];
  argc -= 1;
  argv += 1;
  if (!::strcmp(cmd, "kill"))
  {
    auto kill = kill::CommandKill();
    kill.parse(argc, argv);
    kill.execute();
  }
  else if (!::strcmp(cmd, "watch"))
  {
    auto watch = watch::CommandWatch();
    watch.parse(argc, argv);
    watch.execute();
  }
}
} // namespace shtop
