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

void bit_vector_shift_or(bit_vector *bv, int size, const bit_vector *mask) {
    int i;

    /* For all elements in the vector... */
    for(i = size - 1; i > 0; i--) {
        /* Shift-Or with carry */
        bv[i] = (bv[i] << 1) | mask[i] | (bv[i - 1] >> ULLONG_BITS - 1);
    }

    bv[0] = (bv[0] << 1) | mask[0];
}

void bit_vector_set_zero(bit_vector *bv, int position) {
    int i = position / ULLONG_BITS;
    bv[i] &= ~ULLONG_BIT_AT(position - i * ULLONG_BITS);
}

int bit_vector_is_zero(const bit_vector *bv, int position) {
    int i = position / ULLONG_BITS;
    return !(bv[i] & 1 << position - i * ULLONG_BITS);
}

void bit_vector_free(bit_vector *bv) {
    free(bv);
}

void bit_vector_print(const bit_vector *bv, int size) {
    int i;

    for(i = 0; i < size; i++) {
        char *buffer = to_binary(bv[size - i - 1]);
        printf("%s|", buffer);
        free(buffer);
    }

    printf("\n");
}
