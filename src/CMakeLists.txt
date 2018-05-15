find_package(Threads REQUIRED)

set(SRC
  plib.cc
  process.cc
  watcher.cc
  periodic_watcher.cc
  fs.cc
  sort.cc
  helper.cc
)

add_library(${LIB} SHARED ${SRC})
target_include_directories(${LIB} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(${LIB} PUBLIC "-lstdc++fs")
target_link_libraries(${LIB} PUBLIC "-lstdc++fs")
target_link_libraries(${LIB} PRIVATE Threads::Threads)

IF(BUILD_COVERAGE)
  target_compile_options(${LIB} PRIVATE "-fprofile-arcs" "-ftest-coverage")
  target_link_libraries(${LIB} PRIVATE "-coverage" "-lgcov")
ENDIF(BUILD_COVERAGE)
