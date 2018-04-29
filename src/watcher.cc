#include "watcher.hh"

namespace plib
{
Watcher::Watcher(Process process)
  : process_(process)
{
}

void Watcher::wait_and_refresh()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(delay_));
  process_.refresh();
}

void Watcher::watch()
{
  while (this->watch_)
  {
    std::lock_guard<decltype(watch_mutex)> lock(watch_mutex);
    wait_and_refresh();
    notifee_(process_);
  }
}

void Watcher::launch_async_watch()
{
  // Launch watch function in an async way to refresh the inner
  // Process in the background.
  this->watch_start();
  std::thread t1(&Watcher::watch, this);
}

void Watcher::on_update(std::function<void(Process)> notifee)
{
  this->notifee_ = notifee;
}
} // namespace plib
