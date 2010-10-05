#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

/**
 * Search a given pattern in a given buffer.
 */
void search_buffer(const char *pattern, int pattern_size, const char *file_name,
        char *buffer, long long buffer_offset, int buffer_size) {
    int i, j;

    for(i = 0; i + pattern_size - 1 < buffer_size; i++) {
        j = 0;
        while(j < pattern_size && pattern[j] == buffer[i + j]) j++;

        if(j >= pattern_size) {
            printf("%s:%lld\n", file_name, buffer_offset + i);
        }
    }
}
