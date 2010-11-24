#ifndef SEARCH_H
#define SEARCH_H

#include "common.h"

/**
 * State kept during a search. Different implementations may choose different
 * definitions for this state
 */
struct search_state;

/**
 * Initialize a search_state object.
 * @param pattern Pattern to search for
 * @param pattern_size Size of the pattern
 */
struct search_state *search_create(const char *pattern, int pattern_size);

/* Perform a search on one buffer.
 * @param state The internal search state
 * @param pattern Pattern to search for
 * @param pattern_size Size of the pattern
 * @param buffer Actual buffer to search
 * @param buffer_size Size of the buffer
 * @param file_name Descriptive name of the file we're currently searching in
 * @param buffer_offset Offset of the buffer in the file
 */
void search_buffer(struct search_state *state, const char *pattern,
        int pattern_size, char *buffer, int buffer_size,
        const char *file_name, ullong buffer_offset);

/* Release the internal search state.
 * @param state Search state to free
 */
void search_free(struct search_state *state);

#endif
