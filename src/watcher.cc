#include "watcher.hh"

namespace plib
{
void Watcher::start()
{
  // Launch watch function in an async way to refresh the inner
  // Process in the background.
  this->watch_start();
  this->server = std::thread(&Watcher::watch, this);
}

void Watcher::on_update(callback_func notifee)
{
  LOCK_GUARD(this->watch_mutex);
  this->notifee_ = std::move(notifee);
}

void Watcher::watch_start()
{
  LOCK_GUARD(this->watch_mutex);
  watch_ = true;
}

void Watcher::watch_stop()
{
  LOCK_GUARD(this->watch_mutex);
  watch_ = false;
}

void Watcher::watch_toggle()
{
  LOCK_GUARD(this->watch_mutex);
  watch_ = !watch_;
}

void Watcher::join()
{
  LOCK_GUARD(this->watch_mutex);
  this->server.join();
}

void Watcher::join() const
{
  LOCK_GUARD(this->watch_mutex);
  this->server.join();
}
} // namespace plib
