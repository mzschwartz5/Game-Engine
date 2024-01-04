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
                                                        ${CMAKE_SOURCE_DIR}/includes
                                                        # Glad builds its include folder to the build directory
                                                        ${CMAKE_BINARY_DIR}/gladsources/glad/include/glad)

# Add subdirectory for GLFW
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glad/cmake)

# Function defined in glad cmake file
glad_add_library(glad STATIC API gl:core=4.6)

# Link libraries
target_link_libraries(GameEngineExecutable glfw 
                                           glad ${CMAKE_DL_LIBS})