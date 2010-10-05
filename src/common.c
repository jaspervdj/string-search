#include "common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

inline int fill_next_buffer(char *buffer, int buffer_size, int retain,
        FILE *file) {
    /* Copy the bytes we have to retain. */
    memcpy(buffer, buffer + buffer_size - retain, retain);

    /* Read. */
    return retain + fread(buffer + retain, 1, buffer_size - retain, file);
}

inline char *create_buffer(int buffer_minimum_size, int *buffer_size) {
    int size = 4096;
    while(size < buffer_minimum_size) size <<= 2;
    *buffer_size = size;
#   ifdef DEBUG
    printf("Created a buffer of size: %d\n", size);
#   endif
    return malloc(size);
}
