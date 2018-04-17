cmake_minimum_required(VERSION 3.1)

set(LIB proclib)

project(${PROJECT} CXX)

add_compile_options(-Wall -Wextra -pedantic -std=c++17 -g3)

add_subdirectory(src/)
add_subdirectory(example/src)
