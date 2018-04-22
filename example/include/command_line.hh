#pragma once

#include <cstring>
#include <string>

#include "kill/command_kill.hh"
#include "tclap/CmdLine.h"
#include "watch/command_watch.hh"

namespace shtop
{
namespace tclap = TCLAP;
class CommandLine
{
public:
  CommandLine() = default;
  CommandLine(int argc, char* argv[]);
};
} // namespace shtop
