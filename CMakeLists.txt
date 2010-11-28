cmake_minimum_required(VERSION 2.8)
project("string-search")
set(CMAKE_C_FLAGS, "-Wall -std=c99 -ggdb")
add_definitions() # -DDEBUG)
include_directories(src tests)
link_libraries(m)

add_executable(bin/search0 src/search0.c src/search-files.c src/common.c
        src/main.c)
add_executable(bin/search1 src/search1.c src/search-files.c src/common.c
        src/main.c)
add_executable(bin/search1-bit-vector src/search1-bit-vector.c src/bit-vector.c
        src/search-files.c src/common.c src/main.c)
add_executable(bin/search2 src/search2.c src/search-files.c src/common.c
        src/main.c)
add_executable(bin/search3 src/search3.c src/search-files.c src/common.c
        src/main.c)
add_executable(bin/search4 src/search4.c src/search-files.c src/common.c
        src/main.c)

add_executable(bin/bench0 src/search0.c src/search-files.c src/common.c
        src/bench.c)
add_executable(bin/bench1 src/search1.c src/search-files.c src/common.c
        src/bench.c)
add_executable(bin/bench1-bit-vector src/search1-bit-vector.c src/bit-vector.c
        src/search-files.c src/common.c src/bench.c)
add_executable(bin/bench2 src/search2.c src/search-files.c src/common.c
        src/bench.c)
add_executable(bin/bench3 src/search3.c src/search-files.c src/common.c
        src/bench.c)
add_executable(bin/bench4 src/search4.c src/search-files.c src/common.c
        src/bench.c)

add_executable(tests/generate-text tests/generate-text.c tests/random-text.c
    src/common.c)
add_executable(tests/verify-matches tests/verify-matches.c src/common.c)
add_executable(tests/generate-text-and-matches tests/generate-text-and-matches.c
        src/common.c tests/random-text.c)
