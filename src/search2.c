/**
 * KMP searching
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

struct search_state {
    int *skip_table;
};

/* Used for debugging purposes. */
void print_skip_table(struct search_state *state,
        const char *pattern, int pattern_size) {
    int i;
    printf("Dumping skip table:\n");

    /* Print a header */
    for(i = 0; i < pattern_size; i++) printf("%3c", pattern[i]);
    printf("\n");

    /* Print the actual numbers */
    for(i = 0; i <= pattern_size; i++) printf("%3d", state->skip_table[i]);
    printf("\n");
}

struct search_state *search_create(const char *pattern, int pattern_size) {
    int offset = 1;
    int equal = 0;
    int i;
    int mismatch;
    struct search_state *state = malloc(sizeof(struct search_state));

    /* Initialization */
    state->skip_table = malloc((pattern_size + 1) * sizeof(int));
    state->skip_table[0] = state->skip_table[1] = 1;

    /* Fill in skip table */
    while(offset < pattern_size) {
        /* Determine first mismatch */
        mismatch = equal;
        while(mismatch < pattern_size &&
                pattern[mismatch] == pattern[offset + mismatch]) mismatch++;

        if(mismatch == 0) {
            state->skip_table[offset + 1] = offset + 1;   
            equal = 0;
        } else {
            for(i = equal + 1; i <= mismatch; i++) {
                state->skip_table[offset + i] = offset;
            }

            equal = mismatch - state->skip_table[mismatch];
        }

        offset += state->skip_table[mismatch];
    }

    /* Debugging */
#   ifdef DEBUG
    print_skip_table(state, pattern, pattern_size);
#   endif

    return state;
}

void search_buffer(struct search_state *state, const char *pattern,
        int pattern_size, char *buffer, int buffer_size,
        const char *file_name, ullong buffer_offset) {
    int mismatch = 0;

    const char *buffer_end = buffer + buffer_size - pattern_size + 1;
    const char *buffer_start = buffer;

    int *skip_table = state->skip_table;

    while(buffer < buffer_end) {
        /* Determine first mismatch */
        while(mismatch < pattern_size &&
                pattern[mismatch] == buffer[mismatch]) mismatch++;

        /* Match found */
        if(mismatch >= pattern_size) {
            print_match(file_name, buffer_offset + (buffer - buffer_start));
        }

        buffer += skip_table[mismatch];
        if(mismatch > 0) mismatch -= skip_table[mismatch];
    }
}

void search_free(struct search_state *state) {
    free(state->skip_table);
    free(state);
}
