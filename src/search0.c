#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

struct search_data *create_search_data(const char *pattern, int pattern_size) {
    return 0;
}

/**
 * Search a given pattern in a given buffer.
 */
void search_buffer(struct search_data *data, const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        ullong buffer_offset, int buffer_size) {
    int i, j;

    for(i = 0; i + pattern_size - 1 < buffer_size; i++) {
        j = 0;
        while(j < pattern_size && pattern[j] == buffer[i + j]) j++;

        if(j >= pattern_size) {
            print_match(file_name, buffer_offset + i);
        }
    }
}

void free_search_data(struct search_data *data) {
}
