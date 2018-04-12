set(PROJECT_INCLUDE
  ${CMAKE_SOURCE_DIR}/include/bin
  ${CMAKE_SOURCE_DIR}/include/lib
)

set(SRC
  main.cc
  command_line.cc
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/kill)

add_executable(${PROJECT} ${SRC})
target_include_directories(${PROJECT} PRIVATE ${PROJECT_INCLUDE})

# Link to all sub libraries
target_link_libraries(${PROJECT} PRIVATE ${PROJECT}_kill)

# Link to plib
target_link_libraries(${PROJECT} PRIVATE ${LIB})

# Produce binary at root buildir
set_target_properties(${PROJECT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
