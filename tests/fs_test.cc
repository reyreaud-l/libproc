#include <experimental/filesystem>
#include <sys/wait.h>
#include <unistd.h>

#include "gtest/gtest.h"
#include "plib.hh"

#include "script.hh"

namespace fs = std::experimental::filesystem;

TEST(Fs, get_proc_root)
{
  EXPECT_EQ(plib::get_proc_root(), "/proc");
}

TEST(Fs, get_proc_dir_no_dir)
{
  ASSERT_THROW(plib::get_proc_dir(fs::path("/nowhere"), 0),
               std::invalid_argument);
}

TEST(Fs, get_proc_dir_no_uid)
{
  // This UID really is random. But hey.
  ASSERT_THROW(plib::get_proc_dir(plib::get_proc_root(), 9999999),
               std::invalid_argument);
}

TEST(Fs, get_proc_dirs_no_dir)
{
  ASSERT_THROW(plib::get_proc_dirs(fs::path("/nowhere")),
               std::invalid_argument);
}

TEST(Fs, get_all_proc_not_zero)
{
  ASSERT_NE(plib::get_all_processes().size(), 0);
}

TEST(Fs, get_proc_name)
{
  ASSERT_EQ(plib::get_process(std::string("fs-test")).size(), 1);
}

TEST(Fs, get_proc_name_fail)
{
  ASSERT_EQ(plib::get_process(std::string("not_running_now")).size(), 0);
}

TEST(Fs, resolve_father)
{
  auto procs = plib::get_all_processes();
  procs = plib::resolve_father_sons(procs);
  auto init =
    std::find_if(procs.begin(), procs.end(),
                 [](const plib::Process& p) { return p.stat_get().pid == 1; });
  ASSERT_NE(init, procs.end());
  ASSERT_NE(init->children_get().size(), 0);
}
