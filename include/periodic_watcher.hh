#pragma once

#include "watcher.hh"

#include <chrono>

namespace plib
{
class PeriodicWatcher : public Watcher
{
public:
  PeriodicWatcher(Process);

  PeriodicWatcher(PeriodicWatcher&) = delete;
  PeriodicWatcher(const PeriodicWatcher&) = delete;
  PeriodicWatcher& operator=(PeriodicWatcher&) = delete;
  PeriodicWatcher& operator=(const PeriodicWatcher&) = delete;

  void wait_and_refresh();
  void watch();

  inline void delay_set(std::size_t millisecs)
  {
    delay_ = millisecs;
  }

protected:
  Process process_;
  std::size_t delay_ = 0;
};
} // namespace plib
