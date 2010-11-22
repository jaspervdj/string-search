#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

int *skip_table;

void search_create(const char *pattern, int pattern_size) {
    int i;
    skip_table = malloc(0x100 * sizeof(int));

    for(i = 0; i < 0x100; i++) skip_table[i] = pattern_size;
    for(i = 0; i < pattern_size - 1; i++) {
        skip_table[(unsigned char) pattern[i]] = pattern_size - i - 1;
    }
}

void search_buffer(const char *pattern, int pattern_size,
        const char *file_name, char *buffer, int buffer_size,
        ullong buffer_offset) {
    const char *buffer_start = buffer + pattern_size - 1;
    const char *buffer_end = buffer + buffer_size;
    char pattern_last = pattern[pattern_size - 1];

    buffer = (char *) buffer_start;
    while(buffer < buffer_end) {
        if(*buffer == pattern_last &&
                !strncmp(buffer - pattern_size + 1, pattern, pattern_size)) {
            print_match(file_name, buffer_offset + (buffer - buffer_start));
        }

        buffer += skip_table[(unsigned char) *buffer];
    }
}

void search_free() {
    free(skip_table);
}
