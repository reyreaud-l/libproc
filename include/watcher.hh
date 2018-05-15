#pragma once

#include "process.hh"

#include <functional>
#include <mutex>
#include <thread>

namespace plib
{
class Watcher
{
public:
  using callback_func = std::function<void(Process)>;

  Watcher();

  Watcher(Watcher&) = delete;
  Watcher(const Watcher&) = delete;
  Watcher& operator=(Watcher&) = delete;
  Watcher& operator=(const Watcher&) = delete;

  virtual void watch() = 0;

  virtual void start();
  virtual void on_update(callback_func);

  virtual inline void watch_start()
  {
    watch_ = true;
  }

  virtual inline void watch_stop()
  {
    watch_ = false;
  }

  virtual inline void watch_toggle()
  {
    watch_ = !watch_;
  }

  virtual inline void join()
  {
    this->server.join();
  }

  virtual inline void join() const
  {
    this->server.join();
  }

  mutable std::mutex watch_mutex;

protected:
  mutable std::thread server;
  bool watch_ = true;
  callback_func notifee_ = [](const Process&) {};
};
} // namespace plib
