cmake_minimum_required(VERSION 3.15.0)
project (MinMaxQueueLib)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Bring the headers into the project.
include_directories(include)

# Now bring the sources.
file(GLOB SOURCES "src/*.cpp")

# Generate the static library from the sources.
add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

# Make a build directory and copy lib files after a successful build.
IF (WIN32)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/$<CONFIG>/")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PROJECT_BINARY_DIR}/$<CONFIG>/${PROJECT_NAME}.lib" "${CMAKE_BINARY_DIR}/$<CONFIG>/"
)
ELSE()
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_BINARY_DIR}/bin/")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.a" "${CMAKE_BINARY_DIR}/bin/"
)
ENDIF()

# Expose Lib's public includes to other subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)