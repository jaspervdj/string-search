/**
 * Rabin-Karp implementation
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

struct search_state {
    int pattern_hash;
    int most_significant_factor;
};

int hash_code(const char *string, int string_size) {
    int hash = 0;
    int i;

    for(i = 0; i < string_size; i++) {
        hash = hash * 2 + ((unsigned char) string[i]);
    }

    return hash;
}

struct search_state *search_create(const char *pattern, int pattern_size) {
    struct search_state *state = malloc(sizeof(struct search_state));
    state->pattern_hash = hash_code(pattern, pattern_size);
    state->most_significant_factor = 2 << (pattern_size - 2);
    return state;
}

void search_buffer(struct search_state *state, const char *pattern,
        int pattern_size, char *buffer, int buffer_size,
        const char *file_name, ullong buffer_offset) {
    const char *buffer_start = buffer;
    /* Where to stop matching */
    const char *buffer_end = buffer + buffer_size - pattern_size;
    int buffer_hash = hash_code(buffer, pattern_size);
    int pattern_hash = state->pattern_hash;
    int most_significant_factor = state->most_significant_factor;

    /* Loop through the buffer... */
    while(buffer < buffer_end) {
        /* Compare hashes, and strings if necessary */
        if(buffer_hash == pattern_hash &&
                !strncmp(buffer, pattern, pattern_size)) {
            print_match(file_name, buffer_offset + (buffer - buffer_start));
        }

        /* Update hash */
        buffer_hash = ((buffer_hash -
                ((unsigned char) *buffer) * most_significant_factor) << 1) +
                (unsigned char) *(buffer + pattern_size);

        buffer++;
    }

    /* Comparison for the last position */
    if(buffer_hash == pattern_hash &&
            !strncmp(buffer, pattern, pattern_size)) {
        print_match(file_name, buffer_offset + (buffer - buffer_start));
    }
}

void search_free(struct search_state *state) {
    free(state);
}
