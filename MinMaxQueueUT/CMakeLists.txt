cmake_minimum_required(VERSION 3.15.0)
project (MinMaxQueueUT)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

enable_testing()
add_subdirectory(googletest)

# Bring the headers into the project.
include_directories(include googletest/include)
include_directories(${MinMaxQueueLib_INCLUDE_DIRS})

# Now bring the sources.
file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# Link to the main lib and gtest.
target_link_libraries(${PROJECT_NAME} MinMaxQueueLib gtest_main gtest)

# Copy exe files after a successful build.
IF (WIN32)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PROJECT_BINARY_DIR}/$<CONFIG>/${PROJECT_NAME}.exe" "${CMAKE_BINARY_DIR}/$<CONFIG>/")
ELSE()
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${PROJECT_BINARY_DIR}/${PROJECT_NAME}" "${CMAKE_BINARY_DIR}/bin/")
ENDIF()
