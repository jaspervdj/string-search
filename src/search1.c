#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "common.h"

struct search_data {
    ullong *character_columns;
    /* Column indicating a match */
    ullong match_column;
};

struct search_data *create_search_data(const char *pattern, int pattern_size) {
    struct search_data *data;
    int i;

    data = malloc(sizeof(struct search_data));

    data->character_columns = calloc(0xff, sizeof(ullong));
    for(i = 0; i < pattern_size; i++) {
        data->character_columns[pattern[i]] |= (1 << i);        
    }

    data->match_column = 1 << pattern_size - 1;
}

/**
 * Search a given pattern in a given buffer.
 */
void search_buffer(struct search_data *data, const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        ullong buffer_offset, int buffer_size) {
    ullong column;    
    int i;

    /* We want a buffer, really */
    if(buffer_size <= 0 || pattern_size <= 0) return;

    /* Initialize the first column */
    column = (buffer[0] == pattern[0]) ? 1 : 0;

    for(i = 1; i < buffer_size; i++) {
        /* Shift-1 */
        column <<= 1;
        column |= 1;

        /* And */
        column &= data->character_columns[buffer[i]];

        /* Check result */
        if(column & data->match_column) {
            print_match(file_name, buffer_offset + i - pattern_size + 1);
        }
    }
}

void free_search_data(struct search_data *data) {
    free(data->character_columns);
    free(data);
}
