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

# Add subdirectory for GLFW
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw)

# Link libraries
target_link_libraries(GameEngineExecutable glfw 
                                           ${OPENGL_LIBRARY} 
                                           ${COCOA_LIBRARY} 
                                           ${IOKIT_LIBRARY} 
                                           ${COREVIDEO_LIBRARY})