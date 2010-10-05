#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

int fill_next_buffer(char *buffer, int buffer_size, int retain, FILE *file);

char *create_buffer(int buffer_minimum_size, int *buffer_size);

char *read_entire_file(const char *file_name, int *buffer_size);

#endif
