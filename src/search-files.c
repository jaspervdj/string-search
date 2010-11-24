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
    struct search_state *state;

    /* Check that the file is open */
    if(!file) {
        printf("Could not open: %s\n", file_name);
        return;
    }

    /* Create a buffer of at least the pattern size */
    buffer = create_buffer(pattern_size, &buffer_size);

    /* Initialize the search state */
    state = search_create(pattern, pattern_size);

    /* Fill in a first buffer */
    result = fill_next_buffer(buffer, buffer_size, 0, file);

    /* While we get a complete buffer back... */
    while(result == buffer_size) {
        /* Search the buffer */
        search_buffer(state, pattern, pattern_size, file_name, buffer,
                result, position);

        /* Update the position and fill in a next buffer */
        position += result - pattern_size + 1;
        result = fill_next_buffer(buffer, buffer_size, pattern_size - 1, file);
    }

    /* At this point, we got less bytes than expected; this means this is the
     * last buffer. We also need to search this one... */
    search_buffer(state, pattern, pattern_size, file_name,
            buffer, result, position);

    /* Now, the search has finished. We can free up our resources. */
    search_free(state);
    free(buffer);
    fclose(file);
}

int search_files(char *pattern_file_name, char **file_names,
        int file_names_size) {
    int i;
    char *pattern;
    int pattern_size = 0;

    /* Inspect the pattern. */
    pattern = read_entire_file(pattern_file_name, &pattern_size);

    /* Throw an error if the pattern is empty */
    if(!pattern || pattern_size <= 0) {
        printf("%s: Incorrect pattern of size %d\n",
                pattern_file_name, pattern_size);
        return 1;
    }

#   ifdef DEBUG
    printf("Searching for: %s\n", pattern);
#   endif

    /* Now, loop over the files. */
    for(i = 0; i < file_names_size; i++) {
        search_file(pattern, pattern_size, file_names[i]);
    }

    /* Free up and return */
    free(pattern);
    return 0;
}
