#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "common.h"

typedef unsigned long long int column_type;

column_type *character_columns;

/* Column indicating a match */
column_type match_column;

void initialize_search(const char *pattern, int pattern_size) {
    int i;
    character_columns = calloc(0xff, sizeof(column_type));
    for(i = 0; i < pattern_size; i++) {
        character_columns[pattern[i]] |= (1 << i);        
    }

    match_column = 1 << pattern_size - 1;
}

/**
 * Search a given pattern in a given buffer.
 */
void search_buffer(const char *pattern, int pattern_size, const char *file_name,
        char *buffer, long long buffer_offset, int buffer_size) {
    column_type column;    
    int i;

    /* We want a buffer, really */
    if(buffer_size <= 0 || pattern_size <= 0) return;

    /* Initialize the first column */
    column = (buffer[0] == pattern[0]) ? 1 : 0;

    for(i = 1; i < buffer_size; i++) {
        /* Shift-1 */
        column <<= 1;
        column |= 1;

        /* And */
        column &= character_columns[buffer[i]];

        /* Check result */
        if(column & match_column) {
            printf("Match!\n");
        }
    }
}

void end_search() {
    free(character_columns);
}
