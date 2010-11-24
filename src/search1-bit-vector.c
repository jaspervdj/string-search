/**
 * Shift-and searching, using a bit vector
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "common.h"
#include "bit-vector.h"

struct search_state {
    int bit_vector_size;
    bit_vector **character_columns;
};

struct search_state *search_create(const char *pattern, int pattern_size) {
    int i;
    struct search_state *state = malloc(sizeof(struct search_state));

    /* Figure out how many elements we need in our vectors */
    state->bit_vector_size = (pattern_size + ULLONG_BITS - 1) / ULLONG_BITS;

#   ifdef DEBUG
    printf("Using %d ullong elements in the bit vector.\n",
            state->bit_vector_size);
#   endif

    /* Allocate room for the character columns. */
    state->character_columns = malloc(0x100 * sizeof(bit_vector*));
    for(i = 0; i < 0x100; i++) {
        state->character_columns[i] =
                bit_vector_create_one(state->bit_vector_size);
    }

    /* Set the correct patterns bits to 0. */
    for(i = 0; i < pattern_size; i++) {
        bit_vector_set_zero(
                state->character_columns[(unsigned char) pattern[i]], i);
    }

    return state;
}

void search_buffer(struct search_state *state, const char *pattern,
        int pattern_size, char *buffer, int buffer_size,
        const char *file_name, ullong buffer_offset) {
    bit_vector *column;    
    const char *buffer_start = buffer;
    const char *buffer_end = buffer + buffer_size;
    int bit_vector_size = state->bit_vector_size;
    bit_vector **character_columns = state->character_columns;

    /* We want a buffer, really */
    if(buffer_size <= 0 || pattern_size <= 0) return;

    /* Initialize the first column */
    column = bit_vector_create_one(bit_vector_size);
    if(buffer[0] == pattern[0]) bit_vector_set_zero(column, 0);

    while(buffer < buffer_end) {
        /* Shift-Or */
        bit_vector_shift_or(column, bit_vector_size,
                character_columns[(unsigned char) *buffer]);

        /* Check result */
        if(bit_vector_is_zero(column, pattern_size - 1)) {
            print_match(file_name, buffer_offset + (buffer - buffer_start) -
                    pattern_size + 1);
        }

        buffer++;
    }

    bit_vector_free(column);
}

void search_free(struct search_state *state) {
    int i;
    for(i = 0; i < 0xff; i++) bit_vector_free(state->character_columns[i]);
    free(state->character_columns);
    free(state);
}
