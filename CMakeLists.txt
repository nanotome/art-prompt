cmake_minimum_required(VERSION 3.8.2)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

project(art-prompt VERSION 0.1.0)

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Set enable output of compile commands during generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require OpenGL package
find_package(OpenGL REQUIRED)

# Includes
include_directories(Includes)
include_directories(Libraries)
include_directories(Libraries/SFML/include)
include_directories(Libraries/stb)

# Compile options
include(CMake/CompileOptions.cmake)

# Build type - Release by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Overrides
set(CMAKE_MACOSX_RPATH ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

# Set resources
get_filename_component(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources ABSOLUTE)
set(RESOURCES_OBJS
    ${RESOURCES_DIR}/font.png)

# Project modules
add_subdirectory(Libraries/SFML)
add_subdirectory(Sources/ArtPrompt)
