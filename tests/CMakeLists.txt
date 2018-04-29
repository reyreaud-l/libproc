include(GTest)

IF(BUILD_COVERAGE)
  include(CodeCoverage)
  set(COVERAGE_EXCLUDES "*/googletest-src/*" "*gtest/*" "*7.3.1/*")
  APPEND_COVERAGE_COMPILER_FLAGS()
ENDIF(BUILD_COVERAGE)

set(TEST_COMMAND ctest -V)
set(TEST_CLEAN_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/scripts/check-clean.sh)
set(WHILE_TRUE_SCRIPT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/scripts/while_true.sh)

configure_file(script.hh.in script.hh)

add_custom_target(check COMMAND ${TEST_COMMAND} -E env GTEST_COLOR=1 COMMENT "Running tests")
add_custom_target(check-clean COMMAND ${TEST_CLEAN_SCRIPT} COMMENT "Cleanup after tests...")
add_custom_command(TARGET check POST_BUILD COMMAND ${TEST_CLEAN_SCRIPT} COMMENT "Cleanup after tests...")

IF(BUILD_COVERAGE)
  setup_target_for_coverage(NAME check-coverage EXECUTABLE ${TEST_COMMAND})
ENDIF(BUILD_COVERAGE)

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
  add_dependencies(check ${testcase})

  IF(BUILD_COVERAGE)
    target_compile_options(${testcase} PRIVATE "-fprofile-arcs" "-ftest-coverage")
    target_link_libraries(${testcase} PRIVATE "-coverage" "-lgcov")
    add_dependencies(check-coverage ${testcase})
  ENDIF(BUILD_COVERAGE)
endforeach()
