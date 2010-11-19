cmake_minimum_required(VERSION 2.8)
project("string-search")
set(CMAKE_C_FLAGS, "-Wall -std=c99 -ggdb")
add_definitions() # -DDEBUG)
include_directories(src util)
link_libraries(m)

add_executable(bin/search0 src/search0.c src/search-files.c src/common.c
        src/main.c)
add_executable(bin/search1 src/search1.c src/search-files.c src/common.c
        src/main.c)
add_executable(bin/search2 src/search2.c src/search-files.c src/common.c
        src/main.c)
add_executable(bin/search3 src/search3.c src/search-files.c src/common.c
        src/main.c)

add_executable(bin/bench0 src/search0.c src/search-files.c src/common.c
        src/bench.c)
add_executable(bin/bench1 src/search1.c src/search-files.c src/common.c
        src/bench.c)
add_executable(bin/bench2 src/search2.c src/search-files.c src/common.c
        src/bench.c)
add_executable(bin/bench3 src/search3.c src/search-files.c src/common.c
        src/bench.c)

add_executable(util/generate-text util/generate-text.c util/random-text.c
    src/common.c)
add_executable(util/verify-matches util/verify-matches.c src/common.c)
add_executable(util/generate-text-and-matches util/generate-text-and-matches.c
        src/common.c util/random-text.c)
