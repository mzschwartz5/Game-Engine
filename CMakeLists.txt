# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.28.1)

# Define the project name
project(GameEngine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")

# Add the executable
add_executable(GameEngineExecutable ${SOURCES})

# Download all Git submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# Check that all the submodules downloaded
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The GLFW submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glad/cmake/CMakeLists.txt")
    message(FATAL_ERROR "The Glad submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glm/glm/CMakeLists.txt")
    message(FATAL_ERROR "The GLM submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/stb/stb_image.h")
    message(FATAL_ERROR "The STB submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# Include directories for header files
target_include_directories(GameEngineExecutable PRIVATE ${CMAKE_SOURCE_DIR}/src
                                                        ${CMAKE_SOURCE_DIR}/external/glm
                                                        ${CMAKE_SOURCE_DIR}/external/stb
                                                        ${CMAKE_SOURCE_DIR}/includes
                                                        # Glad builds its include folder to the build directory
                                                        ${CMAKE_BINARY_DIR}/gladsources/glad/include/glad)

# Add subdirectories for GLFW and Glad
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glad/cmake)

# Function defined in glad cmake file
glad_add_library(glad STATIC API gl:core=4.1)

# Link libraries
target_link_libraries(GameEngineExecutable glfw 
                                           glad ${CMAKE_DL_LIBS})