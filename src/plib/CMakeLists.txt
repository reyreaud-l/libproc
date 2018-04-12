find_library(FILESYSTEM stdc++fs)

set(SRC
  plib.cc
  process.cc
  get_proc.cc
  sort.cc
  helper.cc
)

add_library(${LIB} SHARED ${SRC})
target_include_directories(${LIB} PUBLIC ${CMAKE_SOURCE_DIR}/include/lib)
target_link_libraries(${LIB} PUBLIC ${FILESYSTEM})
