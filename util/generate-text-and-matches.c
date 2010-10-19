/**
 * Program that generates text AND matches, so we can easily check a string
 * matching algorithm.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "common.h"

void change_one_character(char *buffer, int pattern_size) {
    int position = rand() % pattern_size;
    buffer[position] += rand();
}

int main(int argc, char **argv) {
    char *pattern;
    int pattern_size;
    unsigned long long position = 1;
    FILE *text_file, *matches_file;
    char *buffer;

    if(argc < 4) {
        printf("Usage: %s <pattern file> <text file> <matches file>\n",
                argv[0]);
        return 1;
    }

    srand(time(0));

    pattern = read_entire_file(argv[1], &pattern_size);
    text_file = fopen(argv[2], "w");
    matches_file = fopen(argv[3], "w");
    buffer = malloc(pattern_size);

    /* Continue forever */
    while(1) {
        /* Take the original pattern, optionally change one character */
        memcpy(buffer, pattern, pattern_size);
        change_one_character(buffer, pattern_size);

        /* Nothing changed, print a match */
        if(!strncmp(buffer, pattern, pattern_size)) {
            fprintf(matches_file, "%llu\n", position);
        }

        /* Write the buffer in any case */
        fwrite(buffer, 1, pattern_size, text_file);
        fwrite("\0", 1, 1, text_file);

        /* Update position */
        position += pattern_size;
    }

    free(pattern);
    fclose(text_file);
    fclose(matches_file);
    free(buffer);
}
