cmake_minimum_required(VERSION 3.15.0)
project (MinMaxQueueLib)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Bring the headers into the project.
include_directories(include)

# Now bring the sources.

# Generate the static library from the sources.
add_library(${PROJECT_NAME} INTERFACE)


# Expose Lib's public includes to other subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)