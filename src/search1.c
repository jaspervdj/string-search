/**
 * Shift-and searching, falling back to brute force if necessary
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "common.h"

struct search_state {
    ullong *character_columns;
    ullong match_column;
};

struct search_state *search_create(const char *pattern, int pattern_size) {
    int i;
    struct search_state *state = malloc(sizeof(struct search_state));

    /* Allocate room for the character columns. Set all bits to 1. */
    state->character_columns = malloc(0x100 * sizeof(ullong));
    memset(state->character_columns, 0xff, 0x100 * sizeof(ullong));

    /* Set the correct patterns bits to 0. */
    for(i = 0; i < MIN(pattern_size, ULLONG_BITS); i++) {
        state->character_columns[pattern[i]] &= ~ULLONG_BIT_AT(i);        
    }

    /* This column is a mask for a match. */
    state->match_column = ULLONG_BIT_AT(MIN(pattern_size, ULLONG_BITS) - 1);

    return state;
}

void search_buffer(struct search_state *state, const char *pattern,
        int pattern_size, char *buffer, int buffer_size,
        const char *file_name, ullong buffer_offset) {
    ullong column;    
    const char *buffer_start = buffer;
    const char *buffer_end = buffer + buffer_size;
    ullong *character_columns = state->character_columns;
    ullong match_column = state->match_column;

    /* We want a buffer, really */
    if(buffer_size <= 0 || pattern_size <= 0) return;

    /* Initialize the first column */
    column = (buffer[0] == pattern[0]) ? ~1 : ~0;

    while(buffer < buffer_end) {
        /* Shift-Or */
        column = (column << 1) | character_columns[(unsigned char) *buffer];

        /* Check result */
        if(!(column & match_column)) {
            /* Further brute-force matching */
            if(pattern_size <= ULLONG_BITS ||
                    !memcmp(buffer + 1, pattern + ULLONG_BITS,
                        pattern_size - ULLONG_BITS)) {
                print_match(file_name, buffer_offset + (buffer - buffer_start) -
                        MIN(pattern_size, ULLONG_BITS) + 1);
            }
        }

        buffer++;
    }
}

void search_free(struct search_state *state) {
    free(state->character_columns);
    free(state);
}
