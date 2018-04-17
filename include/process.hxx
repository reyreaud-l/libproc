#include "process.hh"

namespace plib
{
inline std::string Process::name_get()
{
  return name_;
}

inline const std::string Process::name_get() const
{
  return name_;
}

inline bool Process::is_valid()
{
  return valid_;
}

inline bool Process::is_valid() const
{
  return valid_;
}

inline std::string Process::error_get()
{
  return error_;
}

inline const std::string Process::error_get() const
{
  return error_;
}

inline pstat Process::stat_get()
{
  return stat_;
}

inline const pstat Process::stat_get() const
{
  return stat_;
}

inline memstat Process::statm_get()
{
  return statm_;
}

inline const memstat Process::statm_get() const
{
  return statm_;
}

inline std::vector<Process> Process::children_get()
{
  return children_;
}

inline std::vector<Process> Process::children_get() const
{
  return children_;
}

inline Process Process::father_get()
{
  return *(father_.get());
}

inline const Process Process::father_get() const
{
  return *(father_.get());
}

inline void Process::set_father(Process& father)
{
  father_ = std::make_unique<Process>(father);
}

inline void Process::set_father(std::nullptr_t)
{
  father_ = nullptr;
}

inline void Process::add_child(Process& child)
{
  children_.push_back(child);
}

inline bool Process::operator<(const Process& other)
{
  return this->stat_.pid < other.stat_.pid;
}

inline void Process::delay_set(std::size_t delay)
{
  this->delay_ = delay;
}

inline void Process::watch_stop()
{
  this->watch_ = false;
}
inline void Process::watch_start()
{
  this->watch_ = true;
}
inline void Process::watch_toggle()
{
  this->watch_ = !this->watch_;
}
} // namespace plib
