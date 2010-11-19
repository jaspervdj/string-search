#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

int hash_code(const char *string, int string_size) {
    int hash = 0;
    int i;

    for(i = 0; i < string_size; i++) {
        hash = hash * 2 + ((unsigned char) string[i]);
        // printf("%d\n", hash);
    }

    return hash;
}

void search_create(const char *pattern, int pattern_size) {
}

/**
 * Search a given pattern in a given buffer.
 */
void search_buffer(const char *pattern, int pattern_size,
        const char *file_name, char *buffer, int buffer_size,
        ullong buffer_offset) {
    int pattern_hash = hash_code(pattern, pattern_size);
    int buffer_hash = hash_code(buffer, pattern_size - 1);
    int i;

    for(i = 0; i + pattern_size - 1 < buffer_size; i++) {
        buffer_hash = (buffer_hash << 1) +
                (unsigned char) buffer[i + pattern_size - 1];

        if(buffer_hash == pattern_hash) {
            print_match(file_name, buffer_offset + i);
        }

        buffer_hash -= ((unsigned char) buffer[i]) * (2 << (pattern_size - 2));
    }
}

void search_free() {
}
