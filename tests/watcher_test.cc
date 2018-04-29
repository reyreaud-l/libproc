#include <sys/wait.h>
#include <unistd.h>

#include "gtest/gtest.h"
#include "plib.hh"

#include "script.hh"

class WhileTrueProcess : public ::testing::Test
{
protected:
  WhileTrueProcess()
  {
    pid_ = fork();
    if (pid_ == 0)
    {
      execl(WHILE_TRUE_SCRIPT_PATH, WHILE_TRUE_SCRIPT_PATH);
      exit(0);
    }
  }

  pid_t pid_ = 0;
};

TEST_F(WhileTrueProcess, single_watch)
{
  if (pid_ != 0)
  {
    auto proc = plib::get_process(pid_);
    auto watcher = plib::Watcher(proc);
    bool notifee_called = false;
    watcher.on_update([&notifee_called, &watcher](plib::Process) {
      notifee_called = true;
      watcher.watch_stop();
    });
    watcher.watch();
    EXPECT_TRUE(notifee_called);
    proc.kill(SIGINT);
    waitpid(-1, NULL, WNOHANG);
  }
}

TEST_F(WhileTrueProcess, multiple_watch)
{
  if (pid_ != 0)
  {
    auto proc = plib::get_process(pid_);
    auto watcher = plib::Watcher(proc);
    std::size_t count = 0;
    watcher.on_update([&count, &watcher](plib::Process) {
      if (count < 5)
        count++;
      else
        watcher.watch_stop();
    });
    watcher.watch();

    EXPECT_EQ(count, 5);

    proc.kill(SIGINT);
    waitpid(-1, NULL, WNOHANG);
  }
}

TEST_F(WhileTrueProcess, delay_check)
{
  if (pid_ != 0)
  {
    auto proc = plib::get_process(pid_);
    auto watcher = plib::Watcher(proc);
    auto start = std::chrono::steady_clock::now();

    watcher.delay_set(5);
    watcher.on_update([&start, &watcher](plib::Process) {
      auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
      // the delay is set to 5 milliseconds. More than 7 milliseconds would
      // be an error.
      EXPECT_LT(time, std::chrono::milliseconds(7));
      watcher.watch_stop();
    });
    watcher.watch();

    proc.kill(SIGINT);
    waitpid(-1, NULL, WNOHANG);
  }
}
