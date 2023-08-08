# Specify minimum required version of CMake.
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

### PROJECT - TETRIS ###

# Specify project and identify languages used.
project(tetris LANGUAGES CXX C)

# Include options for compiling with Sanitizer info at runtime.
include(Sanitizers.cmake)

# Provide an option for users to enable code coverage when compiling.
option(ALL_WARNINGS "Show all compiler warnings" false)

# Print the ID of the compiler that is in use.
message("Currently using compiler: ${CMAKE_CXX_COMPILER_ID}")

# Print the current compile flags before we add additional ones.
message("Existing compile flags: \"${CMAKE_CXX_FLAGS}\"")

# Enable verbose makefiles & Export commands.
set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Set the standard to C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Find the packages that are required for compilation
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Show all compiler warnings if enabled by user.
if (ALL_WARNINGS)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    message("NOTE: Enabled all compiler warnings.")
endif()

# Add program source code files.
add_executable(tetris
    lib/TetrisGraphics.cpp
    src/Tetromino.cpp
    src/Playfield.cpp
    src/Tetris.cpp
)

# Add include directories to a target
target_include_directories(tetris PRIVATE include)
#target_include_directories(tetris PUBLIC /usr/include/)
target_link_libraries(tetris PRIVATE ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})


# Print the current compile flags.
message("New compile flags: \"${CMAKE_CXX_FLAGS}\"")

# TODO: Add install support, not just building the executable.
