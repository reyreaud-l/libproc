#include <condition_variable>
#include <sys/wait.h>
#include <unistd.h>

#include "gtest/gtest.h"
#include "plib.hh"

#include "script.hh"

#define SETUP_PERIODIC_WATCHER()                                               \
  auto proc = plib::get_process(pid_);                                         \
  plib::PeriodicWatcher watcher(proc)

class Watcher : public ::testing::Test
{
protected:
  Watcher()
  {
    // FIXME: Use socket unix to communicate with subprocess, and fetch
    // the signal sent.
    pid_ = fork();
    if (pid_ == 0)
    {
      execl(WHILE_TRUE_SCRIPT_PATH, WHILE_TRUE_SCRIPT_PATH);
      exit(0);
    }
  }

  pid_t pid_ = 0;
};

TEST_F(Watcher, periodic_single_watch)
{
  if (pid_ != 0)
  {
    SETUP_PERIODIC_WATCHER();
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

TEST_F(Watcher, periodic_multiple_watch)
{
  if (pid_ != 0)
  {
    SETUP_PERIODIC_WATCHER();
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

TEST_F(Watcher, periodic_delay_check)
{
  if (pid_ != 0)
  {
    SETUP_PERIODIC_WATCHER();
    auto start = std::chrono::steady_clock::now();

    watcher.delay_set(5);
    watcher.on_update([&start, &watcher](plib::Process) {
      auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start);
      // the delay is set to 5 milliseconds. More than 10 milliseconds would
      // be an error. Still it sucks.
      EXPECT_LT(time, std::chrono::milliseconds(10));
      watcher.watch_stop();
    });
    watcher.watch();

    proc.kill(SIGINT);
    waitpid(-1, NULL, WNOHANG);
  }
}

TEST_F(Watcher, periodic_thread_check)
{
  if (pid_ != 0)
  {
    SETUP_PERIODIC_WATCHER();

    std::condition_variable cv;
    std::unique_lock<decltype(watcher.watch_mutex)> lk(watcher.watch_mutex);
    bool assert_check = false;

    watcher.delay_set(10);
    watcher.on_update([&watcher, &cv, &assert_check](plib::Process) {
      watcher.watch_stop();
      assert_check = true;
      cv.notify_all();
    });
    watcher.start();

    cv.wait(lk);

    watcher.join();

    EXPECT_TRUE(assert_check);

    proc.kill(SIGINT);
    waitpid(-1, NULL, WNOHANG);
  }
}
