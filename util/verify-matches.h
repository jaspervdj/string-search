#ifndef VERIFY_MATCHES_H
#define VERIFY_MATCHES_H

/**
 * Parse the given line of format "file:position" into the two fields.
 */
void parse_line(char *line, char *file, unsigned long long *position);

#endif
