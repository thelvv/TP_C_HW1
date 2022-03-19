cmake_minimum_required(VERSION 3.16)
project(HW1 C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wpedantic -Werror --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Werror")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage")
set(INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/project/include")
set(CMAKE_C_CLANG_TIDY clang-tidy; -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*)

if(address)
    message("address")
    add_compile_options( -fno-omit-frame-pointer -fsanitize=address)
    add_link_options(-fsanitize=address)
elseif(memory)
    message("memory")
    add_compile_options( -fno-omit-frame-pointer -fsanitize=leak)   # -fsanitize=memory don't work, change to leak
    add_link_options(-fsanitize=leak)
elseif(undefined)
    message("undefined")
    add_compile_options( -fno-omit-frame-pointer -fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
elseif(thread)
    message("thread")
    add_compile_options( -fno-omit-frame-pointer -fsanitize=thread)
    add_link_options(-fsanitize=thread)
endif()

add_library(array_tools STATIC project/src/array_tools.c)
add_library(song_tools STATIC project/src/song_tools.c)

target_include_directories(array_tools PUBLIC project/include)
target_include_directories(song_tools PUBLIC project/include)

add_executable(HW1 project/src/main.c)
target_link_libraries(HW1 array_tools)
target_link_libraries(HW1 song_tools)

find_package(GTest REQUIRED)
set(SOURCES tests/run_tests.cpp tests/array_tests.cpp tests/song_tests.cpp)
add_executable(run_tests ${SOURCES})
target_link_libraries(run_tests GTest::GTest array_tools song_tools)