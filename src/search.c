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
    long long position = 0;
    int i;

    buffer = create_buffer(pattern_size, &buffer_size);

#   ifdef DEBUG
    if(!file) {
        printf("Could not open file.\n");
        return;
    }
#   endif

    result = fill_next_buffer(buffer, buffer_size, 0, file);
    while(result == buffer_size) {

        position += result;
        search_buffer(pattern, pattern_size, file_name, buffer,
                position, result);
        result = fill_next_buffer(buffer, buffer_size, pattern_size - 1, file);
    }

    search_buffer(pattern, pattern_size, file_name, buffer, position, result);
    position += result;

    free(buffer);
    fclose(file);
}

int main(int argc, char **argv) {
    int i;
    const char *pattern;
    int pattern_size;

    /* Check that we have enough arguments. If not, bail out. */
    if(argc < 3) {
        printf("Usage: %s <pattern file> <file> [<file> ...]\n", argv[0]);
        return 1;
    }

    /* Inspect the pattern. */
    pattern = read_entire_file(argv[1], &pattern_size);

#   ifdef DEBUG
    printf("Searching for: %s\n", pattern);
#   endif

    /* Now, loop over the files. */
    for(i = 2; i < argc; i++) {
        search_file(pattern, pattern_size, argv[i]);
    }

    return 0;
}
