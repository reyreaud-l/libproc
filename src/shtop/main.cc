#include <algorithm>
#include <iostream>

#include "plib/plib.hh"
#include "shtop/command_line.hh"

int main(int argc, char* argv[])
{
  shtop::CommandLine(argc, argv);
  auto processes = plib::sort_by_mem(plib::get_all_processes());
  processes = plib::resolve_father_sons(processes);
}
