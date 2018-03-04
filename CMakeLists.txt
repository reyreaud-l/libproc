cmake_minimum_required(VERSION 3.1)

set(PROJECT shtop)
set(LIB proclib)

project(${PROJECT} CXX)

add_compile_options(-Wall -Wextra -pedantic -std=c++17 -g3)

add_subdirectory(src/plib)
add_subdirectory(src/shtop)
