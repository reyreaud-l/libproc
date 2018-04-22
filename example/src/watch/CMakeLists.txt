add_library(${PROJECT}_watch STATIC
  command_watch.cc
  watch.cc
)
target_include_directories(${PROJECT}_watch PRIVATE ${PROJECT_INCLUDE})
