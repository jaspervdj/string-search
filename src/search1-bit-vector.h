#ifndef SEARCH1_BIT_VECTOR_H
#define SEARCH1_BIT_VECTOR_H

void search_create_bit_vector(const char *pattern, int pattern_size);

void search_buffer_bit_vector(const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        int buffer_size, ullong buffer_offset);

void search_free_bit_vector();

#endif
