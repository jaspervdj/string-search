#ifndef SEARCH0_H
#define SEARCH0_H

#include "common.h"

/* Initialize a search object. */
void search_create(const char *pattern, int pattern_size);

/* Perform the actual search. */
void search_buffer(const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        int buffer_size, ullong buffer_offset);

/* Release the search data. */
void search_free();

/* Main function. */
int search(int argc, char **argv);

#endif
