add_library(${PROJECT}_kill STATIC
  command_kill.cc
  kill.cc
)
target_include_directories(${PROJECT}_kill PRIVATE ${PROJECT_INCLUDE})
