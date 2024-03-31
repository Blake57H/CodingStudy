cmake_minimum_required(VERSION 3.8)
project(somemath)
add_library(somemath add.cpp)

# alternative way at the end of the video
include(GNUInstallDirs)
set_target_properties(somemath PROPERTIES PUBLIC_HEADER add.h)
install(TARGETS somemath LIBRARY PUBLIC_HEADER)