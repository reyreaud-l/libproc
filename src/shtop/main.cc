#include <algorithm>
#include <iostream>

#include "plib/plib.hh"
#include "tclap/CmdLine.h"

int main(int argc, char* argv[])
{
  TCLAP::CmdLine cmd("shtop is utility binary to inspect processes", ' ',
                     "0.1");

  TCLAP::ValueArg<std::string> nameArg(
    "n", "name", "Name of process to inspect", true, "shtop", "string");
  TCLAP::ValueArg<int> intArg("s", "signal", "Signal to send to process", false,
                              -1, "int");
  cmd.add(intArg);
  cmd.add(nameArg);

  cmd.parse(argc, argv);
  std::string name = nameArg.getValue();
  int signal = intArg.getValue();

  auto processes = plib::sort_by_mem(plib::get_all_processes());
  processes = plib::resolve_father_sons(processes);
  std::for_each(processes.begin(), processes.end(),
                [&](const plib::Process& n) {
                  if (name == n.name_get())
                  {
                    std::cout << n;
                    if (signal != -1)
                    {
                      n.kill(signal);
                    }
                  }
                });
}
