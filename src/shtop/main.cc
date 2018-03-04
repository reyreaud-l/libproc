#include <algorithm>
#include <iostream>

#include "plib/plib.hh"

int main()
{
  auto processes = plib::get_all_processes();
  std::for_each(processes.begin(), processes.end(),
                [](const plib::Process& n) { std::cout << n << std::endl; });
}
