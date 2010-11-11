#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include "common.h"

/**
 * Search the given file for the given term.
 */
void search_file(const char *pattern, int pattern_size, const char *file_name) {
    FILE *file = fopen(file_name, "r");
    char *buffer;
    int buffer_size;
    size_t result;
    ullong position = 1;
    int i;

    buffer = create_buffer(pattern_size, &buffer_size);

#   ifdef DEBUG
    if(!file) {
        printf("Could not open file.\n");
        return;
    }
#   endif

    search_create(pattern, pattern_size);

    result = fill_next_buffer(buffer, buffer_size, 0, file);
    while(result == buffer_size) {
        search_buffer(pattern, pattern_size, file_name, buffer,
                result, position);
        position += result - pattern_size + 1;
        result = fill_next_buffer(buffer, buffer_size, pattern_size - 1, file);
    }

    search_buffer(pattern, pattern_size, file_name, buffer, result, position);

    search_free();

    free(buffer);
    fclose(file);
}

int search_files(char *pattern_file_name, char **file_names,
        int file_names_size) {
    int i;
    char *pattern;
    int pattern_size;

    /* Inspect the pattern. */
    pattern = read_entire_file(pattern_file_name, &pattern_size);

#   ifdef DEBUG
    printf("Searching for: %s\n", pattern);
#   endif

    /* Now, loop over the files. */
    for(i = 0; i < file_names_size; i++) {
        search_file(pattern, pattern_size, file_names[i]);
    }

    free(pattern);

    return 0;
}
