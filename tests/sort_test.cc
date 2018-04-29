#include <experimental/filesystem>
#include <sys/wait.h>
#include <unistd.h>

#include "gtest/gtest.h"
#include "plib.hh"

#include "script.hh"

namespace fs = std::experimental::filesystem;

TEST(Sort, sort_by_mem)
{
  auto procs = plib::get_all_processes();
  procs = plib::sort_by_mem(procs);
  EXPECT_TRUE(
    std::is_sorted(procs.begin(), procs.end(),
                   [](const plib::Process& a, const plib::Process& b) {
                     return a.statm_get().size > b.statm_get().size;
                   }));
}

TEST(Sort, sort_by_utime)
{
  auto procs = plib::get_all_processes();
  procs = plib::sort_by_utime(procs);
  EXPECT_TRUE(
    std::is_sorted(procs.begin(), procs.end(),
                   [](const plib::Process& a, const plib::Process& b) {
                     return a.stat_get().utime > b.stat_get().utime;
                   }));
}
