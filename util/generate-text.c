/**
 * Utility to generate large files of random text
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

#define BUFFER_SIZE 1024
#define DEFAULT_CHUNKS 4

/**
 * Print usage information
 */
void print_usage(int argc, char **argv) {
    printf("Usage: %s [options]\n", argv[0]);
    printf("\n");
    printf("OPTIONS\n");
    printf("\n");
    printf("-a             Only use a-z for the text (Default: bytes)\n");
    printf("-o file        Output file (Default: stdout)\n");
    printf("-s size        Number of %d-byte text chunks (Default: %d)\n",
            BUFFER_SIZE, DEFAULT_CHUNKS);
}

/**
 * Generate a random char
 */
inline unsigned char random_char(int alpha) {
    if(alpha) {
        /* Use both lower and upper case */
        switch(rand() % 2) {
            case 0:
                return 'a' + rand() % ('z' - 'a');
            case 1:
                return 'A' + rand() % ('Z' - 'A');
        }
    } else {
        return rand() % CHAR_MAX;
    }
}

/**
 * Generate random text
 */
void generate_text(int alpha, unsigned long long size, FILE *out) {
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
            buffer[j] = random_char(alpha);
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
    /* Alpha text */
    int alpha = 0;
    /* Output file */
    FILE *out = stdout;
    /* Size in KiB */
    unsigned long long size = DEFAULT_CHUNKS;
    /* Option parsing return code */
    int opt_code;

    /* Parse options */
    while((opt_code = getopt(argc, argv, "aho:s:")) != -1) {
        switch(opt_code) {
            case 'a':
                alpha = 1;
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

    /* Generate the actual text */
    generate_text(alpha, size, out);

    return 0;
}
