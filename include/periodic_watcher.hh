#pragma once

#include "watcher.hh"

#include <chrono>

namespace plib
{
class PeriodicWatcher : public Watcher
{
public:
  PeriodicWatcher(Process);

  DELETE_COPY_MOVE(PeriodicWatcher);

  void watch() override;

  void wait_and_refresh();

  inline void delay_set(std::size_t millisecs)
  {
    delay_ = millisecs;
  }

protected:
  Process process_;
  std::size_t delay_ = 0;
};
} // namespace plib
