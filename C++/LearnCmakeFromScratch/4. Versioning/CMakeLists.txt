cmake_minimum_required(VERSION 3.13)
project(ExeUseLib VERSION 0.1)
configure_file(ExeUseLibConfig.h.in ExeUseLibConfig.h)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(add_lib)

# I don't think it will work in my case, as my repository itself isn't a git repo, but a part of a git repo.
# find_package(Git QUIET)
# if(NOT EXISTS "${PROJECT_SOURCE_DIR}/.git")
#     message(FATAL_ERROR "Not a git repository: ${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
# endif()
# if(GIT_FOUND)
#     option(GIT_SUBMODULE "Check submodule during build" ON)
#     if(GIT_SUBMODULE)
#         message(STATUS "Submodule update")
#         execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
#                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#                         RESULT_VARIABLE GIT_SUBMOD_RESULT)
#         if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#             message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
#         endif()
#     endif()
# endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "glfw submodule is not present: ${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
endif()
add_subdirectory(external/glfw)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC add_lib
    PUBLIC out/mingw-make-build
    PUBLIC external/glfw/include
)
target_link_directories(
    ${PROJECT_NAME} 
    PRIVATE add_lib
    PRIVATE external/glfw/src
)
target_link_libraries(${PROJECT_NAME} somemath glfw)
