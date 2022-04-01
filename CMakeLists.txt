cmake_minimum_required(VERSION 3.16)

option(parallel "Build parallel version" OFF)

project(HW2 C CXX)

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
target_include_directories(array_tools PUBLIC project/include)

add_library(consistent STATIC project/src/serial_processing.c)
target_include_directories(consistent PUBLIC project/include)
target_link_libraries(consistent HW2 array_tools)

add_library(parallel SHARED project/src/parallel_processing.c)
target_include_directories(parallel PUBLIC project/include)
target_link_libraries(parallel PUBLIC array_tools)


add_executable(HW2 project/src/main.c)

if(parallel)
    message("parallel")
    target_link_libraries(HW2 parallel consistent)
else()
    message("consistent")
    target_link_libraries(HW2 parallel consistent)
endif(parallel)

find_package(GTest REQUIRED)
set(SOURCES tests/run_tests.cpp tests/array_tests.cpp project/include/parallel_processing.h project/include/serial_processing.h)
add_executable(run_tests ${SOURCES})
target_link_libraries(run_tests GTest::GTest array_tools song_tools)