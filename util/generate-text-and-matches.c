/**
 * Program that generates text AND matches, so we can easily check a string
 * matching algorithm.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include "common.h"

/* Flag indicating that the generator is running */
int running;

/**
 * Generate a list of all unique characters in a string.
 * list_size will contain the length of the resulting list.
 */
char *chars_in_string(char *string, int string_size, int *list_size) {
    char *seen_chars = calloc(0x100, sizeof(char));
    char *list = calloc(0x100, sizeof(char));
    int i;

    *list_size = 0;
    for(i = 0; i < string_size; i++) {
        /* Not seen yet */
        if(!seen_chars[(unsigned char) (string[i])]) {
            seen_chars[(unsigned char) (string[i])] = 1;
            list[*list_size] = string[i];
            (*list_size)++;
        }
    }

    free(seen_chars);
    return list;
}

/**
 * Get a random character from the list
 */
char random_char(char *list, int list_size) {
    return list[rand () % list_size];
}

/**
 * Signal handler
 */
void stop_running_handler(int code) {
    printf("Signal received, closing...\n");
    running = 0;
}

int main(int argc, char **argv) {
    char *pattern;
    int pattern_size;
    unsigned long long position = 1;
    FILE *text_file, *matches_file;
    char *buffer;
    int i;
    /* List of all characters in the pattern */
    char *list;
    int list_size;

    if(argc < 4) {
        printf("Usage: %s <pattern file> <text file> <matches file>\n",
                argv[0]);
        return 1;
    }

    srand(time(0));

    /* Open files and read the search pattern */
    pattern = read_entire_file(argv[1], &pattern_size);
    text_file = fopen(argv[2], "w");
    matches_file = fopen(argv[3], "w");

    /* Get all characters from the search pattern */
    list = chars_in_string(pattern, pattern_size, &list_size);

    /* Initialize a random buffer */
    buffer = malloc(pattern_size);
    for(i = 0; i < pattern_size; i++) buffer[i] = random_char(list, list_size);

    /* Print the first part */
    fwrite(buffer, 1, pattern_size - 1, text_file);

    /* Continue until interrupted */
    running = 1;
    signal(SIGINT, stop_running_handler);
    while(running) {
        /* Write the character */
        fwrite(buffer + pattern_size - 1, 1, 1, text_file);

        /* Print a match if needed */
        if(!strncmp(buffer, pattern, pattern_size)) {
            fprintf(matches_file, "%llu\n", position);
        }

        /* Shift the buffer and a new char */
        memcpy(buffer, buffer + 1, pattern_size - 1);
        buffer[pattern_size - 1] = random_char(list, list_size);

        /* Update position */
        position += 1;
    }

    free(pattern);
    fclose(text_file);
    fclose(matches_file);
    free(buffer);
    free(list);

    return 0;
}
