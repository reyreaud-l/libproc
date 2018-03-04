set(SRC main.cc)

add_executable(${PROJECT} ${SRC})
target_link_libraries(${PROJECT} PRIVATE ${LIB})

# Produce binary at root buildir
set_target_properties(${PROJECT}
  PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
