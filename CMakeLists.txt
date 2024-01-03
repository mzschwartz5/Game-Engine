# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.28.1)

# Define the project name
project(GameEngine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")

# Add the executable
add_executable(GameEngineExecutable ${SOURCES})

# Include directories for header files
target_include_directories(GameEngineExecutable PRIVATE ${CMAKE_SOURCE_DIR}/external/glm
                                                        ${CMAKE_SOURCE_DIR}/includes)

# Find frameworks needed by GLFW
find_library(OPENGL_LIBRARY OpenGL)
find_library(COCOA_LIBRARY Cocoa)
find_library(IOKIT_LIBRARY IOKit)
find_library(COREVIDEO_LIBRARY CoreVideo)

# Link libraries
target_link_directories(GameEngineExecutable PUBLIC ${CMAKE_SOURCE_DIR}/external/glfw-lib-arm64)
target_link_libraries(GameEngineExecutable glfw3 
                                           ${OPENGL_LIBRARY} 
                                           ${COCOA_LIBRARY} 
                                           ${IOKIT_LIBRARY} 
                                           ${COREVIDEO_LIBRARY})