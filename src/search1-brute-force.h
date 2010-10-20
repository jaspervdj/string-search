#ifndef SEARH1_BRUTE_FORCE_H
#define SEARH1_BRUTE_FORCE_H

void search_create_brute_force(const char *pattern, int pattern_size);

void search_buffer_brute_force(const char *pattern,
        int pattern_size, const char *file_name, char *buffer,
        int buffer_size, ullong buffer_offset);

void search_free_brute_force();

#endif
