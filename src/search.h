#ifndef SEARCH0_H
#define SEARCH0_H

#include "common.h"

/* Search state */
struct search_state;

/* Initialize a search object. */
struct search_state *search_create(const char *pattern, int pattern_size);

/* Perform the actual search. */
void search_buffer(struct search_state *state, const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        int buffer_size, ullong buffer_offset);

/* Release the search data. */
void search_free(struct search_state *state);

#endif
