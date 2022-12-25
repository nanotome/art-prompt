cmake_minimum_required(VERSION 3.17)
project(artprompt)
set(CMAKE_CXX_STANDARD 17)

set(ARTPROMPT_VERSION 1.1)

add_compile_definitions(ARTPROMPT_VERSION="${ARTPROMPT_VERSION}")

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE is not set, defaulting to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(NOT CMAKE_C_COMPILER)
    message(STATUS "CMAKE_C_COMPILER is not set, defaulting to gcc")
    set(CMAKE_C_COMPILER gcc)
endif()

if(NOT CMAKE_CXX_COMPILER)
    message(STATUS "CMAKE_CXX_COMPILER is not set, defaulting to g++")
    set(CMAKE_CXX_COMPILER g++)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    src/artprompt.cpp
)

set(INCLUDES
    include/artprompt.hpp
)

# Add Icon to windows builds
if(WIN32)
    enable_language("RC")

    add_executable(artprompt WIN32 main.cpp ${SOURCES} ${INCLUDES} images/artprompt.rc)
else()
    add_executable(artprompt main.cpp ${SOURCES} ${INCLUDES})
endif()

if(WIN32)
    if(NOT DEFINED ENV{SDL_PATH})
        message(STATUS "Environment variable SDL_PATH is not set, defaulting to C:/SDL2/")
        set(ENV{SDL_PATH} "C:/SDL2/")
    endif()

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(SDL_LIB_DIRECTORY $ENV{SDL_PATH}/lib/x64)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(SDL_LIB_DIRECTORY $ENV{SDL_PATH}/lib/x86)
    endif()

    target_include_directories(artprompt PRIVATE $ENV{SDL_PATH}/include)
    target_link_directories(artprompt PRIVATE ${SDL_LIB_DIRECTORY})
    target_link_libraries(artprompt PRIVATE SDL2main SDL2 SDL2_image)

    file(COPY ${SDL_LIB_DIRECTORY}/SDL2.dll SDL2_image.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    add_definitions(-DSDL_MAIN_HANDLED)
    add_definitions(-DYAML_CPP_STATIC_DEFINE)

    # TODO try to fix this 'hack'
    # Add IFileDialog for mingw64
    add_compile_definitions(NTDDI_VERSION=0x0A000006)
    add_compile_definitions(_WIN32_WINNT=0x0A00)

    add_compile_definitions(UNICODE)
    add_compile_definitions(_UNICODE)

    # Commented at the moment because printing to terminal doesn't work on windows while this is enabled
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-subsystem,windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
elseif(UNIX AND NOT APPLE)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_library(SDL2_LIBRARY SDL2)
    find_library(SDL2_image_LIBRARY SDL2_image)
    include_directories("${SDL2_INCLUDE_DIRS}")
    include_directories("${SDL2_image_INCLUDE_DIRS}")
    target_link_libraries(artprompt PRIVATE -lSDL2 -lSDL2_image)
elseif(APPLE)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_library(SDL2_LIBRARY SDL2)
    find_library(SDL2_image_LIBRARY SDL2_image)
    include_directories(artprompt SYSTEM PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS})
    target_link_libraries(artprompt PRIVATE ${SDL2_LIBRARY} ${SDL2_image_LIBRARY})
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -Wall -Wextra -Wvla -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
    -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Wsign-promo \
    -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wundef -Wimplicit-fallthrough \
    -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 \
    -fsanitize-undefined-trap-on-error -fstack-protector-strong -fPIE \
    ")

# Seems fixed atm? Don't know why
# Seems to break debug build rendering
# if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=bounds")

# endif()
