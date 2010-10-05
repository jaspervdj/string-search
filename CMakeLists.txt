cmake_minimum_required(VERSION 2.8)
project("string-search")
set(CMAKE_C_FLAGS, "-Wall -std=c99")
add_definitions(-DDEBUG)
include_directories(src)

# Search 1
add_executable(search1 src/search1.c src/common.c)
