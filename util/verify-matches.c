/**
 * This tool is used to verify matches. It receives a number of lines in
 *
 *     file_name:position
 *
 * format on stdin. It then opens the corresponding files and verifies that the
 * given position matches the pattern specified by a command-line parameter
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "verify-matches.h"

void parse_line(char *line, char *file, unsigned long long *position) {
    /* Read the file part */
    int i = 0;
    while(line[i] != ':') {
        file[i] = line[i];
        i++;
    }

    /* Add an EOS byte */
    file[i] = '\0';

    /* Read the position */
    sscanf(line + i + 1, "%llu", position);
}

/**
 * Verify a match in the given file on the given position (1-based)
 */
void verify_match(char *pattern, int pattern_size, char *file_name,
        unsigned long long position) {
    /* Open the file and allocate some room for the data */
    FILE *file = fopen(file_name, "r");
    char *match = malloc(pattern_size * sizeof(char));

    /* Seek and read the possible match */
    fseek(file, position - 1, SEEK_SET);
    fread(match, sizeof(char), pattern_size, file);

    /* Check the match */
    if(strncmp(pattern, match, pattern_size)) {
        printf("%s:%llu FALSE\n", file_name, position);
    }

    /* Free up */
    fclose(file);
    free(match);
}

/**
 * Main function
 */
int main(int argc, char **argv) {
    /* The line read, the filename and the position in the file */
    char *line = malloc(1024 * sizeof(char));
    char *file_name = malloc(1024 * sizeof(char));
    unsigned long long position;

    /* The search pattern */
    char *pattern;
    int pattern_size;

    /* Read the pattern */
    if(argc < 2) {
        printf("Usage: %s <pattern file>\n", argv[0]);
        return 1;
    }

    /* Read in the pattern */
    pattern = read_entire_file(argv[1], &pattern_size);

    fgets(line, 1024, stdin);
    while(!feof(stdin)) {
        /* Read and parse */
        parse_line(line, file_name, &position);
        verify_match(pattern, pattern_size, file_name, position);

        fgets(line, 1024, stdin);
    }
    parse_line(line, file_name, &position);

    /* Free up */
    free(line);
    free(file_name);
    free(pattern);

    return 0;
}
