#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "common.h"
#include "bit-vector.h"

int bit_vector_size;
bit_vector **character_columns;

struct search_data *create_search_data(const char *pattern, int pattern_size) {
    int i;

    /* Figure out how many elements we need in our vectors */
    bit_vector_size = (pattern_size + ULLONG_BITS - 1) / ULLONG_BITS;

    /* Allocate room for the character columns. */
    character_columns = malloc(0xff * sizeof(bit_vector*));
    for(i = 0; i < 0xff; i++) {
        character_columns[i] = bit_vector_create_one(bit_vector_size);
    }

    /* Set the correct patterns bits to 0. */
    for(i = 0; i < pattern_size; i++) {
        bit_vector_set_zero(character_columns[pattern[i]], i);
    }
}

/**
 * Search a given pattern in a given buffer.
 */
void search_buffer(const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        int buffer_size, ullong buffer_offset) {
    bit_vector *column;    
    const char *buffer_start = buffer;
    const char *buffer_end = buffer + buffer_size;

    /* We want a buffer, really */
    if(buffer_size <= 0 || pattern_size <= 0) return;

    /* Initialize the first column */
    column = bit_vector_create_one(bit_vector_size);
    if(buffer[0] == pattern[0]) bit_vector_set_zero(column, 0);

    while(buffer < buffer_end) {
        /* Shift-Or */
        bit_vector_shift_left_one(column, bit_vector_size);
        bit_vector_or(column, bit_vector_size, character_columns[*buffer]);

        /* Check result */
        if(bit_vector_is_zero(column, pattern_size - 1)) {
            print_match(file_name, buffer_offset + (buffer - buffer_start) -
                    pattern_size + 1);
        }

        buffer++;
    }

    bit_vector_free(column);
}

void free_search_data() {
    int i;
    for(i = 0; i < 0xff; i++) bit_vector_free(character_columns[i]);
    free(character_columns);
}
