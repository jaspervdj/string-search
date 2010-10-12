cmake_minimum_required(VERSION 2.8)
project("string-search")
set(CMAKE_C_FLAGS, "-Wall -std=c99 -ggdb")
add_definitions() #-DDEBUG)
include_directories(src)

add_executable(search0 src/search0.c src/search.c src/common.c src/main.c)
add_executable(search1 src/search1.c src/search.c src/common.c src/main.c)

add_executable(bench0 src/search0.c src/search.c src/common.c src/bench.c)
add_executable(bench1 src/search1.c src/search.c src/common.c src/bench.c)

add_executable(util/generate-text util/generate-text.c)
add_executable(util/verify-matches util/verify-matches.c src/common.c)
