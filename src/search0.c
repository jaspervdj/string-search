#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

void search_create(const char *pattern, int pattern_size) {
}

/**
 * Search a given pattern in a given buffer.
 */
void search_buffer(const char *pattern, int pattern_size,
        const char *file_name, char *buffer, int buffer_size,
        ullong buffer_offset) {
    int i, j;

    for(i = 0; i + pattern_size - 1 < buffer_size; i++) {
        j = 0;
        while(j < pattern_size && pattern[j] == buffer[i + j]) j++;

        if(j >= pattern_size) {
            print_match(file_name, buffer_offset + i);
        }
    }
}

void search_free() {
}
