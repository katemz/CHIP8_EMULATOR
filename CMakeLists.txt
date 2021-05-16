cmake_minimum_required(VERSION 3.5)

project(CHIP8 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    main.cpp
    application.cpp
)

set(HEADERS
    application.h
)

add_executable(CHIP8 ${SOURCES} ${HEADERS})
target_link_libraries(CHIP8 ${SDL2_LIBRARIES} )
