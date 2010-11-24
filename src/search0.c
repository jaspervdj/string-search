/**
 * A brute-force implementation
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

/* No state for brute-force */
struct search_state {
};

struct search_state *search_create(const char *pattern, int pattern_size) {
    return 0;
}

void search_buffer(struct search_state *state, const char *pattern,
        int pattern_size, char *buffer, int buffer_size,
        const char *file_name, ullong buffer_offset) {
    int i, j;

    for(i = 0; i + pattern_size - 1 < buffer_size; i++) {
        j = 0;
        while(j < pattern_size && pattern[j] == buffer[i + j]) j++;

        if(j >= pattern_size) {
            print_match(file_name, buffer_offset + i);
        }
    }
}

void search_free(struct search_state *state) {
}
