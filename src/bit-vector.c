#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "bit-vector.h"

bit_vector *bit_vector_create_one(int size) {
    bit_vector *bv = malloc(sizeof(ullong) * size);
    memset(bv, 0xff, sizeof(ullong) * size);
    return bv;
}

void bit_vector_shift_left_one(bit_vector *bv, int size) {
    int i;

    /* For all elements in the vector... */
    for(i = size - 1; i >= 0; i--) {
        /* Shift */
        bv[i] <<= 1;
        /* Carry */
        if(i - 1 >= 0) bv[i] |= bv[i - 1] >> ULLONG_BITS - 1;
    }
}

void bit_vector_or(bit_vector *bv, int size, bit_vector *mask) {
    int i;
    for(i = 0; i < size; i++) bv[i] |= mask[i];
}

void bit_vector_set_zero(bit_vector *bv, int position) {
    int i = position / ULLONG_BITS;
    bv[i] &= ~(1 << position - i * ULLONG_BITS);
}

int bit_vector_is_zero(bit_vector *bv, int position) {
    int i = position / ULLONG_BITS;
    return !(bv[i] & 1 << position - i * ULLONG_BITS);
}

void bit_vector_free(bit_vector *bv) {
    free(bv);
}

void bit_vector_print(bit_vector *bv, int size) {
    int ullong_chars = ULLONG_BITS + 1;
    char *buffer = malloc(size * ullong_chars);
    int i;

    for(i = 0; i < size; i++) {
        to_binary(bv[size - i - 1], buffer + i * ullong_chars);
        buffer[(i + 1) * ullong_chars - 1] = '|';
    }

    buffer[size * ullong_chars - 1] = '\0';

    printf("%s\n", buffer);

    free(buffer);
}
