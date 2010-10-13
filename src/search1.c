#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "common.h"

ullong *character_columns;
ullong match_column;

struct search_data *create_search_data(const char *pattern, int pattern_size) {
    int i;

    /* Allocate room for the character columns. Set all bits to 1. */
    character_columns = malloc(0xff * sizeof(ullong));
    memset(character_columns, 0xff, 0xff * sizeof(ullong));

    /* Set the correct patterns bits to 0. */
    for(i = 0; i < pattern_size; i++) {
        character_columns[pattern[i]] &= ~(1 << i);        
    }

    /* This column is a mask for a match. */
    match_column = 1 << pattern_size - 1;
}

/**
 * Search a given pattern in a given buffer.
 */
void search_buffer(const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        int buffer_size, ullong buffer_offset) {
    ullong column;    
    int i;

    /* We want a buffer, really */
    if(buffer_size <= 0 || pattern_size <= 0) return;

    /* Initialize the first column */
    column = (buffer[0] == pattern[0]) ? ~1 : ~0;

    for(i = 1; i < buffer_size; i++) {
        /* Shift-Or */
        column = (column << 1) | character_columns[buffer[i]];

        /* Check result */
        if(!(column & match_column)) {
            print_match(file_name, buffer_offset + i - pattern_size + 1);
        }
    }
}

void free_search_data() {
    free(character_columns);
}
