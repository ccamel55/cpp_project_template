cmake_minimum_required(VERSION 3.26)

# change to the project name, all build targets will be renamed accordingly
set(CPP_PROJECT_NAME test_environment)
message(STATUS "Project name: ${CPP_PROJECT_NAME}")

project(${CPP_PROJECT_NAME})

# would use 23 however most features not supported yet by gcc/clang on machines i use :(
# todo: update in the future: https://en.cppreference.com/w/cpp/compiler_support

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# i include CPM by default because it means i dont need to clone the repo or directly include the source files
# for catch2 each time i want to use the boilerplate.
include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)

# including my custom library coz at this point everything I do gets mashing into there
set(LIB_COMMAND_PARSER on)
set(LIB_GUI on)
set(LIB_HASHING on)
set(LIB_INPUT on)
set(LIB_JSON_CONFIG on)
set(LIB_RENDERING vulkan)
set(LIB_THREADING on)
set(LIB_UTILS on)
set(LIB_WINDOW_CREATION on)
set(LIB_LOGGER 4)


add_subdirectory(deps/custom_lib)
add_subdirectory(runnable)
add_subdirectory(src)