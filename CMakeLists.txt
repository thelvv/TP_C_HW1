cmake_minimum_required(VERSION 3.21)
project(HW1 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wpedantic -Werror --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Werror --coverage")

add_executable(HW1 src/main.c src/song_tools.c include/song_tools.h src/array_tools.c include/array_tools.h)
