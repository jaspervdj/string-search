#ifndef SEARCH0_H
#define SEARCH0_H

#include "common.h"

/* Intermediate data used by the search. */
struct search_data;

/* Initialize a search object. */
struct search_data *create_search_data(const char *pattern, int pattern_size);

/* Perform the actual search. */
void search_buffer(struct search_data *data, const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        ullong buffer_offset, int buffer_size);

/* Release the search data. */
void free_search_data(struct search_data *data);

#endif
