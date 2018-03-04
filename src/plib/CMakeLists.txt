find_library(FILESYSTEM stdc++fs)

set(SRC plib.cc process.cc)

add_library(${LIB} SHARED ${SRC})
target_include_directories(${LIB} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${LIB} PUBLIC ${FILESYSTEM})
