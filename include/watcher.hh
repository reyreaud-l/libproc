#pragma once

#include "process.hh"

#include <functional>
#include <mutex>
#include <thread>

#define LOCK_GUARD(X) std::lock_guard<decltype(X)> l(X)

#define DELETE_COPY_MOVE(X)                                                    \
  X(X&) = delete;                                                              \
  X(const X&) = delete;                                                        \
  X& operator=(X&) = delete;                                                   \
  X& operator=(const X&) = delete

namespace plib
{
class Watcher
{
public:
  using callback_func = std::function<void(Process)>;

  Watcher() = default;

  DELETE_COPY_MOVE(Watcher);

  virtual void watch() = 0;

  virtual void on_update(callback_func);

  virtual void watch_start();
  virtual void watch_stop();
  virtual void watch_toggle();

  virtual void start();
  virtual void join();
  virtual void join() const;

protected:
  mutable std::thread server;
  mutable std::mutex watch_mutex;
  bool watch_ = true;
  callback_func notifee_ = [](const Process&) {};
};
} // namespace plib
