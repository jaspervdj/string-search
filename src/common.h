#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <limits.h>

/**
 * Longest possible unsigned
 */
typedef unsigned long long ullong;

/**
 * Number of bits in an ullong
 */
#define ULLONG_BITS (sizeof(ullong) * CHAR_BIT)

/**
 * Return an ullong with only the xth byte set to 1
 */
#define ULLONG_BIT_AT(x) ((ullong) 1 << x)

/**
 * Minimum of two values
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * Square a value
 */
#define SQUARE(a) ((a) * (a))

/**
 * Absolute value
 */
#define ABS(a) ((a) > 0 ? (a) : (-(a)))

/**
 * Fill in a next buffer. The last "retain" bytes are kept in the buffer, but
 * moved to the front. The rest of the buffer is filled with bytes from the
 * given file.
 * @param buffer Buffer to fill
 * @param buffer_size Size of the buffer
 * @param retain Number of bytes to retain
 * @param file File to read new bytes from
 * @return Number of bytes in the buffer (i.e. bytes retained + bytes read)
 */
int fill_next_buffer(char *buffer, int buffer_size, int retain, FILE *file);

/**
 * Create a new buffer with a nice size.
 * @param buffer_minimum_size Minimum size for the buffer
 * @param buffer_size Will contain the actual size of the returned buffer
 * @return A new buffer
 */
char *create_buffer(int buffer_minimum_size, int *buffer_size);

/**
 * Read an entire file and put it in a buffer
 * @param file_name Name of the file to read
 * @param buffer_size Will contain the actual size of the returned buffer
 * @return A new buffer, containing the entire file
 */
char *read_entire_file(const char *file_name, int *buffer_size);

/**
 * Print a match at the given position in the given file, using the requested
 * format.
 * @param file_name File in which the match was found
 * @param position Exact position of the match
 */
void print_match(const char *file_name, ullong position);

/**
 * Convert an ullong to a human-readable binary representation
 * @param n Number to convert to binary
 * @return \0-terminated buffer containing the binary representation
 */
char *to_binary(ullong n);

#endif
