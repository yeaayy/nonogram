cmake_minimum_required(VERSION 3.15)
project(Nonogram)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options("$<BUILD_INTERFACE:-Wall;-ggdb>")

add_executable(nonogram src/main.cpp)

add_subdirectory(src)