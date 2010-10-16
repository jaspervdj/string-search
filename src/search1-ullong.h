#ifndef SEARH1_ULLONG_H
#define SEARH1_ULLONG_H

void search_create_ullong(const char *pattern, int pattern_size);

void search_buffer_ullong(const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        int buffer_size, ullong buffer_offset);

void search_free_ullong();

#endif
