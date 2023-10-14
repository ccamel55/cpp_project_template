cmake_minimum_required(VERSION 3.26)

# change to the project name, all build targets will be renamed accordingly
set(CPP_PROJECT_NAME cpp_project)
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
set(LIB_BACKEND_INPUT none)
set(LIB_BACKEND_RENDER none)
set(LIB_BACKEND_WINDOW_CREATION none)
set(LIB_COMMON_LOGGER 4)
set(LIB_COMMON_THREADING false)

CPMAddPackage("gh:ccamel55/custom_lib#54f69b0e365c39036287151cbf7650010afcbd36")

add_subdirectory(runnable)
add_subdirectory(src)
add_subdirectory(tests)