cmake_minimum_required (VERSION 2.8)
project (LTI_Example)

#version number
set (LTI_Example_VERSION_MAJOR 1)
set (LTI_Example_VERSION_MINOR 0)

#include the subdirectory containing our libs
add_subdirectory (Library)
include_directories(Library)
#indicate the entry point for the executable
add_executable (LTI_Example Library Example.cpp)

# Indicate which libraries to include during the link process.
target_link_libraries (LTI_Example Library)

install (TARGETS LTI_Example DESTINATION bin)
