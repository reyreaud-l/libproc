#include "plib/helper.hh"

std::string calculate_size(uint64_t size)
{
  char* result = (char*)malloc(sizeof(char) * 20);
  uint64_t multiplier = exbibytes;

  for (size_t i = 0; i < DIM(sizes); i++, multiplier /= 1024)
  {
    if (size < multiplier)
      continue;
    if (size % multiplier == 0)
      sprintf(result, "%" PRIu64 " %s", size / multiplier, sizes[i]);
    else
      sprintf(result, "%.1f %s", (float)size / multiplier, sizes[i]);
    return result;
  }
  strcpy(result, "0");
  return std::string(result);
}
