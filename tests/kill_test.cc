#include <sys/wait.h>
#include <unistd.h>

#include "gtest/gtest.h"
#include "plib.hh"

#include "script.hh"

// FIXME: We should find a way to check that the subprocess
// receive the right signal, instead of checking if it's killed.
class WhileTrueProcess : public ::testing::Test {
 protected:
  WhileTrueProcess() {
    pid_ = fork();
    if (pid_ == 0) {
      execl(WHILE_TRUE_SCRIPT_PATH, WHILE_TRUE_SCRIPT_PATH);
      exit(0);
    }
  }

  pid_t pid_ = 0;
};

// This test will hang if it fails to kill the subprocess.
TEST_F(WhileTrueProcess, sigint) {
  if (pid_ != 0) {
    auto proc = plib::get_process(pid_);
    proc.kill(SIGINT);
    EXPECT_TRUE(proc.is_status<plib::Error::kind::killed>());
    waitpid(-1, nullptr, WNOHANG);
  }
}

// This test will hang if it fails to kill the subprocess.
TEST_F(WhileTrueProcess, sigterm) {
  if (pid_ != 0) {
    auto proc = plib::get_process(pid_);
    proc.kill();
    EXPECT_TRUE(proc.is_status<plib::Error::kind::killed>());
    waitpid(-1, nullptr, WNOHANG);
  }
}
