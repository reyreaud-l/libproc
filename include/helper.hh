#pragma once

#include <unistd.h>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#define DIM(x) (sizeof(x) / sizeof(*(x)))

std::string calculate_size(uint64_t size);
int page_size();
