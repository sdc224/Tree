cmake_minimum_required(VERSION 3.8)
project(tree)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES queue.h basic.c stack.h)
add_executable(tree ${SOURCE_FILES})
add_executable(basic basic.c)