#pragma once

#include <string>

namespace plib
{
class Error
{
public:
  enum kind
  {
    valid,
    fatal,
    killed
  };

  Error() = default;

  inline void set_error(kind k, std::string msg)
  {
    kind_ = k;
    msg_ = std::move(msg);
  }

  inline void set_error_errno(kind k, const std::string& msg)
  {
    set_error(k, std::string(msg + strerror(errno)));
  }

  inline std::string msg_get()
  {
    return msg_;
  }

  inline std::string msg_get() const
  {
    return msg_;
  }

  inline kind kind_get()
  {
    return kind_;
  }

  inline kind kind_get() const
  {
    return kind_;
  }

private:
  kind kind_ = kind::valid;
  std::string msg_;
};
} // namespace plib
