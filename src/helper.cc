#include "helper.hh"

static const char* sizes[] = {"EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "B"};
static const uint64_t exbibytes =
  1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;

std::string calculate_size(uint64_t size)
{
  char result[20];
  size_t multiplier = exbibytes;

  for (size_t i = 0; i < DIM(sizes); i++, multiplier /= 1024)
  {
    if (size < multiplier)
    {
      continue;
    }
    if (size % multiplier == 0)
    {
      std::sprintf(result, "%" PRIu64 " %s", size / multiplier, sizes[i]);
    }
    else
    {
      std::sprintf(result, "%.1f %s", (float)size / multiplier, sizes[i]);
    }
    return result;
  }
  ::strcpy(result, "0 B");
  return std::string(result);
}

int page_size()
{
  return getpagesize();
}
