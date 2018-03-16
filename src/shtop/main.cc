#include <algorithm>
#include <iostream>

#include "plib/plib.hh"

int main()
{
  auto processes = plib::get_all_processes();
  processes = plib::resolve_father_sons(processes);
  std::for_each(processes.begin(), processes.end(),
                [](const plib::Process& n) { std::cout << n << std::endl; });
}
