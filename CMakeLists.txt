cmake_minimum_required(VERSION 3.19)

project(chip8)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

add_executable(chip8 src/main.cpp src/Chip8.cpp src/Platform.cpp)
target_link_libraries(chip8 PRIVATE SDL2::SDL2)
target_compile_options(chip8 PRIVATE -Wall)

