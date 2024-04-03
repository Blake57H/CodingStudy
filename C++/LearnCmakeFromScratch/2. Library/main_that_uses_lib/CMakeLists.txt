cmake_minimum_required(VERSION 3.13)
project(exe_use_lib)
add_executable(exe_use_lib main.cpp)

# include(GNUInstallDirs)
# target_link_directories(exe_use_lib PRIVATE LIBRARY)
target_link_directories(exe_use_lib PRIVATE ${CMAKE_SOURCE_DIR}/../add_lib/mingw-make-build/)
target_link_libraries(exe_use_lib somemath)