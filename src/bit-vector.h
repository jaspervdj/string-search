#ifndef BIT_VECTOR_H
#define BIT_VECTOR_H

#include "common.h"

typedef ullong bit_vector;

bit_vector *create_bit_vector_one(int size);

/**
 * Shift the given bit vector to left by one.
 */
void bit_vector_shift_left_one(bit_vector *bv, int size);

/**
 * Or the given bit vector with a given mask.
 */
void bit_vector_or(bit_vector *bv, int size, bit_vector *mask);

/**
 * Set a given position in the bit vector to zero.
 */
void bit_vector_set_zero(bit_vector *bv, int position);

/**
 * Check if a given bit is a zero bit.
 */
int bit_vector_is_zero(bit_vector *bv, int position);

void free_bit_vector(bit_vector *bv);

void print_bit_vector(bit_vector *bv, int size);

#endif
