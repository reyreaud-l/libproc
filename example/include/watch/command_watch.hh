#pragma once

#include <string>

#include "tclap/CmdLine.h"
#include "watch/watch.hh"

namespace shtop::watch
{
namespace tclap = TCLAP;
class CommandWatch
{
public:
  CommandWatch();
  void parse(int argc, char* argv[]);
  void execute();

  tclap::CmdLine cmdline;
  tclap::UnlabeledValueArg<std::string> name;
};
} // namespace shtop::watch
