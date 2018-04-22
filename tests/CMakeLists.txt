find_package(Threads REQUIRED)
# Download and unpack googletest at configure time
file(MAKE_DIRECTORY googletest-download)
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND cmake .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
  ${CMAKE_BINARY_DIR}/googletest-build
  EXCLUDE_FROM_ALL)

set(TEST ${PROJECT}_test)
set(TEST_COMMAND ctest -V)
set(TEST_CLEAN_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/check-clean.sh)

set(WHILE_TRUE_SCRIPT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/while_true.sh)

configure_file(script.hh.in script.hh)

add_custom_target(check COMMAND ${TEST_COMMAND} COMMENT "Running tests")
add_custom_target(check-clean COMMAND ${TEST_CLEAN_SCRIPT} COMMENT "Cleanup after tests...")

# Always run clean after running check
add_custom_command(TARGET check POST_BUILD COMMAND ${TEST_CLEAN_SCRIPT} COMMENT "Cleanup after tests...")

file(GLOB FILES "*_test.cc")
foreach(file ${FILES})
  get_filename_component(file_basename ${file} NAME_WE)
  string(REGEX REPLACE "([^$]+)_test" "\\1-test" testcase ${file_basename})

  add_executable(${testcase} EXCLUDE_FROM_ALL ${file})
  target_include_directories(${testcase} PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_include_directories(${testcase} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
  target_link_libraries(${testcase} PRIVATE ${LIB})
  target_link_libraries(${testcase} PRIVATE Threads::Threads)
  target_link_libraries(${testcase} PRIVATE gtest_main)
  target_compile_options(${testcase} PRIVATE -std=c++17 -Wall -Wextra -Werror -pedantic) 
  add_test(NAME "${testcase}_default" COMMAND ${testcase})
  add_dependencies(check "${testcase}")
endforeach()
