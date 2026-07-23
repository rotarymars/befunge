cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(befunge LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

option(DEBUGER "A befunge debugger" ON)
option(INTERPRETER "A befunge interpreter" ON)
option(COMPILER "A befunge compiler" ON)

add_library(code STATIC lib/code.cpp)
target_include_directories(code PUBLIC lib)

# tests

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(test)