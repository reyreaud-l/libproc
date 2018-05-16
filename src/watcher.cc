#include "watcher.hh"

namespace plib
{
Watcher::Watcher()
{
}

void Watcher::start()
{
  // Launch watch function in an async way to refresh the inner
  // Process in the background.
  this->watch_start();
  this->server = std::thread(&Watcher::watch, this);
}

void Watcher::on_update(callback_func notifee)
{
  this->notifee_ = std::move(notifee);
}

void Watcher::watch_start()
{
  watch_ = true;
}

void Watcher::watch_stop()
{
  watch_ = false;
}

void Watcher::watch_toggle()
{
  watch_ = !watch_;
}

void Watcher::join()
{
  this->server.join();
}

void Watcher::join() const
{
  this->server.join();
}
} // namespace plib
