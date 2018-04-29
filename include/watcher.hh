#pragma once

#include "process.hh"

#include <chrono>
#include <functional>
#include <mutex>
#include <thread>

namespace plib
{
class Watcher
{
public:
  using callback_func = std::function<void(Process)>;

  Watcher(Process);

  Watcher(Watcher&) = delete;
  Watcher(const Watcher&) = delete;
  Watcher& operator=(Watcher&) = delete;
  Watcher& operator=(const Watcher&) = delete;

  void wait_and_refresh();
  void watch();
  void on_update(callback_func);
  void launch_async_watch();

  inline void watch_start()
  {
    watch_ = true;
  }

  inline void watch_stop()
  {
    watch_ = false;
  }

  inline void watch_toggle()
  {
    watch_ = !watch_;
  }

  inline void delay_set(std::size_t millisecs)
  {
    delay_ = millisecs;
  }

  mutable std::mutex watch_mutex;

private:
  Process process_;

  bool watch_ = true;
  std::size_t delay_ = 0;
  callback_func notifee_ = [](const Process&) {};
};
} // namespace plib
