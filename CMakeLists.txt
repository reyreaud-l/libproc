cmake_minimum_required(VERSION 3.1)

set(LIB proc)

project(${PROJECT} CXX)

add_compile_options(-Wall -Wextra -pedantic -std=c++17 -g3)

# Lib
add_subdirectory(src/)

# Example
add_subdirectory(example/src)

# Tests
enable_testing()
add_subdirectory(tests)
