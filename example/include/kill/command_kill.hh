#pragma once

#include <string>

#include "kill/kill.hh"
#include "tclap/CmdLine.h"

namespace shtop::kill
{
namespace tclap = TCLAP;
class CommandKill
{
public:
  CommandKill();
  void parse(int argc, char* argv[]);
  void execute();

  tclap::CmdLine cmdline;
  tclap::UnlabeledValueArg<std::string> name;
  tclap::ValueArg<int> signal;
};
} // namespace shtop::kill
