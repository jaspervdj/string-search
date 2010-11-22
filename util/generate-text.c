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
#include "common.h"

#define DEFAULT_SIZE (4 * 1024)

/**
 * Print usage information
 */
void print_usage(int argc, char **argv) {
    printf("USAGE\n");
    printf("%s [options]\n", argv[0]);
    printf("\n");
    printf("OPTIONS\n");
    printf("-c string  Use only the characters which are in string\n");
    printf("-f file    Use only the characters which are in file\n");
    printf("-o file    Output file (Default: stdout)\n");
    printf("-r seed    Use given random seed\n");
    printf("-s size    Number of bytes (Default: %d)\n", DEFAULT_SIZE);
}

/**
 * Generate random text
 */
void generate_text(char *list, int list_size,
        unsigned long long size, FILE *out) {
    unsigned long long i;

    /* Loop using the size */
    for(i = 0; i < size; i++) {
        char c = random_char(list, list_size);

        /* Flush the buffer */
        fwrite(&c, sizeof(char), 1, out);
    }
}

/**
 * Main function
 */
int main(int argc, char **argv) {
    /* Temporary */
    char *tmp;
    int tmp_size;
    /* Output file */
    FILE *out = stdout;
    /* Text size */
    unsigned long long size = DEFAULT_SIZE;
    /* Option parsing return code */
    int opt_code;
    /* List of characters to use */
    char *list = 0;
    int list_size;

    /* Initialize random seed */
    srand(time(0));

    /* Parse options */
    while((opt_code = getopt(argc, argv, "c:f:ho:r:s:")) != -1) {
        switch(opt_code) {
            /* Take characters from string */
            case 'c':
                if(list) free(list);
                list = chars_in_string(optarg, strlen(optarg), &list_size);
                break;

            /* Take characters from file */
            case 'f':
                if(list) free(list);
                tmp = read_entire_file(optarg, &tmp_size);
                list = chars_in_string(tmp, tmp_size, &list_size);
                free(tmp);
                break;

            /* Print help */
            case 'h':
                print_usage(argc, argv); 
                return 0;

            /* Set output file */
            case 'o':
                out = fopen(optarg, "w");
                break;

            /* Set random seed */
            case 'r':
                srand(atoi(optarg));
                break;

            /* Set text size */
            case 's':
                size = atoi(optarg);
                break;

            /* All else */
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
