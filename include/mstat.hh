#pragma once

#include <linux/limits.h>
#include <string>

namespace plib {
struct memstat {
  size_t size;
  size_t resident;
  size_t shared;
  size_t text;
  size_t lib;
  size_t data;
  size_t dt;
};
}  // namespace plib
