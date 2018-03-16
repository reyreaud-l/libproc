#pragma once

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define DIM(x) (sizeof(x) / sizeof(*(x)))

static const char* sizes[] = {"EiB", "PiB", "TiB", "GiB", "MiB", "KiB", "B"};
static const uint64_t exbibytes =
  1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;

std::string calculate_size(uint64_t size);
