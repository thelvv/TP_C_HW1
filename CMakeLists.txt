cmake_minimum_required(VERSION 3.16)
project(HW2 C CXX)

option(parallel "build" OFF)


set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread ")
set(CMAKE_C_CLANG_TIDY clang-tidy; -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Werror -fPIC")
set(INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/project/include")

if(address)
    message("address")
    add_compile_options( -fno-omit-frame-pointer -fsanitize=address)
    add_link_options(-fsanitize=address)
elseif(memory)
    message("memory")
    add_compile_options( -fno-omit-frame-pointer -fsanitize=leak)
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


add_subdirectory(project)

add_executable(HW2 project/src/main.c)

if(parallel)
    message("parallel")
    target_link_libraries(HW2 parallel gcov)
else()
    message("consistent")
    target_link_libraries(HW2 consistent gcov)
endif(parallel)

find_package(GTest REQUIRED)
set(SOURCES tests/run_tests.cpp tests/array_tests.cpp tests/serial_tests.cpp tests/parallel_tests.cpp)
add_executable(run_tests ${SOURCES})
target_link_libraries(run_tests GTest::GTest consistent parallel)