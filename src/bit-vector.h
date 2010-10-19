#ifndef BIT_VECTOR_H
#define BIT_VECTOR_H

#include "common.h"

typedef ullong bit_vector;

bit_vector *bit_vector_create_one(int size);

/**
 * Shift the given bit vector to left by one.
 */
void bit_vector_shift_left_one(bit_vector *bv, int size);

/**
 * Set a given position in the bit vector to zero.
 */
void bit_vector_set_zero(bit_vector *bv, int position);

/**
 * Check if a given bit is a zero bit.
 */
int bit_vector_is_zero(bit_vector *bv, int position);

void bit_vector_free(bit_vector *bv);

void bit_vector_print(bit_vector *bv, int size);

#endif
