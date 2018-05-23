#include "periodic_watcher.hh"

namespace plib
{
PeriodicWatcher::PeriodicWatcher(Process process)
  : process_(process)
{
}
void PeriodicWatcher::wait_and_refresh()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(delay_));
  process_.refresh();
}

void PeriodicWatcher::watch()
{
  while (this->watch_)
  {
    {
      LOCK_GUARD(this->watch_mutex);
      wait_and_refresh();
    }
    notifee_(process_);
  }
}
} // namespace plib
