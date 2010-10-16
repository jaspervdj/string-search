#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "common.h"
#include "search1-ullong.h"
#include "search1-bit-vector.h"

int use_ullong;

search_create(const char *pattern, int pattern_size) {
    use_ullong = pattern_size <= ULLONG_BITS;
    if(use_ullong) search_create_ullong(pattern, pattern_size);
    else search_create_bit_vector(pattern, pattern_size);

#   ifdef DEBUG
    if(use_ullong) printf("Using a single ullong for shift-and.\n");
    else printf("Using a bit vector for shift-and.\n");
#   endif
}

void search_buffer(const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        int buffer_size, ullong buffer_offset) {
    if(use_ullong) {
        search_buffer_ullong(pattern, pattern_size, file_name, buffer,
                buffer_size, buffer_offset);
    } else {
        search_buffer_bit_vector(pattern, pattern_size, file_name, buffer,
                buffer_size, buffer_offset);
    }
}

void search_free() {
    if(use_ullong) search_free_ullong();
    else search_free_bit_vector();
}
