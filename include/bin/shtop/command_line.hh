#pragma once

#include <cstring>
#include <string>

#include "shtop/kill/command_kill.hh"
#include "tclap/CmdLine.h"

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
