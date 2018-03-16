#pragma once

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define DIM(x) (sizeof(x) / sizeof(*(x)))

std::string calculate_size(uint64_t size);
