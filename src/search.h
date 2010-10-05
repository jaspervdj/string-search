#ifndef SEARCH0_H
#define SEARCH0_H

void intialize_search(const char *pattern, int pattern_size);

void search_buffer(const char *pattern, int pattern_size, const char *file_name,
        char *buffer, long long buffer_offset, int buffer_size);

void end_search();

#endif
