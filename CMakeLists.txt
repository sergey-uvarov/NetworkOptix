cmake_minimum_required(VERSION 3.15.0)
project (MinMaxQueue)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

add_subdirectory(MinMaxQueueLib) # static lib with necessary functionality
add_subdirectory(MinMaxQueueUT)  # executable to test the lib using Google Test framework