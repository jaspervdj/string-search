#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

int pattern_hash;
int most_significant_factor;

int hash_code(const char *string, int string_size) {
    int hash = 0;
    int i;

    for(i = 0; i < string_size; i++) {
        hash = hash * 2 + ((unsigned char) string[i]);
    }

    return hash;
}

void search_create(const char *pattern, int pattern_size) {
    pattern_hash = hash_code(pattern, pattern_size);
    most_significant_factor = 2 << (pattern_size - 2);
}

/**
 * Search a given pattern in a given buffer.
 */
void search_buffer(const char *pattern, int pattern_size,
        const char *file_name, char *buffer, int buffer_size,
        ullong buffer_offset) {
    const char *buffer_start = buffer;
    /* Where to stop matching */
    const char *buffer_end = buffer + buffer_size - pattern_size;
    int buffer_hash = hash_code(buffer, pattern_size);

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

void search_free() {
}
