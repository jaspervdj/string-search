/**
 * KMP searching
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

int *skip_table;

/* Macro to get the first mismatch. The result is stored in the i variable. */
#define FIRST_MISMATCH(pattern, pattern_size, buffer, buffer_offset            \
        , assume_equal, i) {                                                   \
    i = assume_equal;                                                          \
    while(i < pattern_size && pattern[i] == buffer[buffer_offset + i]) i++;    \
}

void search_create(const char *pattern, int pattern_size) {
    int offset = 1;
    int equal = 0;
    int i;
    int mismatch;

    skip_table = malloc((pattern_size + 1) * sizeof(int));
    skip_table[0] = skip_table[1] = 1;

    while(offset < pattern_size) {
        FIRST_MISMATCH(pattern, pattern_size, pattern, offset, equal, mismatch);

        if(mismatch == 0) {
            skip_table[offset + 1] = offset + 1;   
            equal = 0;
        }
        else {
            for(i = 1; i <= mismatch; i++) skip_table[offset + i] = offset;
            equal = mismatch - skip_table[mismatch];
        }

        offset += skip_table[mismatch];
    }
}

/**
 * Search a given pattern in a given buffer.
 */
void search_buffer(const char *pattern, int pattern_size,
        const char *file_name, char *buffer, int buffer_size,
        ullong buffer_offset) {
    int i = 0;
    int equal = 0;
    int mismatch;

    while(i + pattern_size - 1 < buffer_size) {
        FIRST_MISMATCH(pattern, pattern_size, buffer, i, equal, mismatch);

        /* Match found */
        if(mismatch >= pattern_size) {
            print_match(file_name, buffer_offset + i);
            i++;
            equal = 0;
        } else {
            i += skip_table[mismatch];
            equal = mismatch == 0 ? 0 : mismatch - skip_table[mismatch];
        }
    }
}

void search_free() {
    free(skip_table);
}
