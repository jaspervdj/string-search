#ifndef GENERATE_TEXT_H
#define GENERATE_TEXT_H

/**
 * Generate a list of all unique characters in a string.
 * list_size will contain the length of the resulting list.
 */
char *chars_in_string(char *string, int string_size, int *list_size);

/**
 * Get a random character from the list
 */
char random_char(char *list, int list_size);

#endif
