#ifndef BIT_VECTOR_H
#define BIT_VECTOR_H

#include "common.h"

/**
 * Type used for base elements of a bit_vector
 */
typedef ullong bit_vector;

/**
 * Create a bit_vector with all bits set to 1
 * @param size Number of elements in the vector
 * @return A new bit vector
 */
bit_vector *bit_vector_create_one(int size);

/**
 * Perform a shift-or operation
 * @param bv Bit vector to operate on
 * @param size Number of elements in the vector
 * @param mask Mask to OR with
 */
void bit_vector_shift_or(bit_vector *bv, int size, const bit_vector *mask);

/**
 * Set a given position in the bit vector to zero.
 * @param bv Bit vector to operate on
 * @param position Bit (counted from the right, 0-based) which should be made 0
 */
void bit_vector_set_zero(bit_vector *bv, int position);

/**
 * Check if a given bit is a zero bit.
 * @param bv Bit vector to query
 * @param position Position of the bit to check
 */
int bit_vector_is_zero(const bit_vector *bv, int position);

/**
 * Free up a bit vector
 * @param bv Bit vector to free
 */
void bit_vector_free(bit_vector *bv);

/**
 * Print out a bit vector, can be useful for debugging purposes
 * @param bv Bit vector to print
 * @param size Number of elements in the bit vector
 */
void bit_vector_print(const bit_vector *bv, int size);

#endif
