/**
 * Utility to generate large files of random text
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include "random-text.h"

#define BUFFER_SIZE 1024
#define DEFAULT_CHUNKS 4

/**
 * Print usage information
 */
void print_usage(int argc, char **argv) {
    printf("USAGE\n");
    printf("%s [options]\n", argv[0]);
    printf("\n");
    printf("OPTIONS\n");
    printf("-c string  Use only the characters which are in string\n");
    printf("-o file    Output file (Default: stdout)\n");
    printf("-s size    Number of %d-byte text chunks (Default: %d)\n",
            BUFFER_SIZE, DEFAULT_CHUNKS);
}

/**
 * Generate random text
 */
void generate_text(char *list, int list_size,
        unsigned long long size, FILE *out) {
    /* A buffer */
    unsigned char *buffer = malloc(BUFFER_SIZE * sizeof(unsigned char));
    unsigned long long i;

    /* Initialize random seed */
    srand(time(0));

    /* Loop using the size */
    for(i = 0; i < size; i++) {
        int j;
        /* Fill the buffer */  
        for(j = 0; j < BUFFER_SIZE; j++) {
            buffer[j] = random_char(list, list_size);
        }

        /* Flush the buffer */
        fwrite(buffer, sizeof(unsigned char), BUFFER_SIZE, out);
    }

    /* Free up */
    free(buffer);
}

/**
 * Main function
 */
int main(int argc, char **argv) {
    /* Output file */
    FILE *out = stdout;
    /* Size in KiB */
    unsigned long long size = DEFAULT_CHUNKS;
    /* Option parsing return code */
    int opt_code;
    /* List of characters to use */
    char *list = 0;
    int list_size;

    /* Parse options */
    while((opt_code = getopt(argc, argv, "c:ho:s:")) != -1) {
        switch(opt_code) {
            case 'c':
                list = chars_in_string(optarg, strlen(optarg), &list_size);
                break;
            case 'h':
                print_usage(argc, argv); 
                return 0;
            case 'o':
                out = fopen(optarg, "w");
                break;
            case 's':
                size = atoi(optarg);
                break;
            default:
                return 0;
        }
    }

    /* No string given, use default */
    if(!list) {
        int i;
        list = malloc(0x100);
        list_size = 0x100;
        for(i = 0; i < list_size; i++) list[i] = i;
    }

    /* Generate the actual text */
    generate_text(list, list_size, size, out);

    /* Clean up */
    free(list);

    return 0;
}
