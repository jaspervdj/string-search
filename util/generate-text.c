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
    printf("-s size        Number of %d-byte text chunks (Default: %d)\n",
            BUFFER_SIZE, DEFAULT_CHUNKS);
    printf("-o file        Output file (Default: stdout)\n");
}

/**
 * Generate random text
 */
void generate_text(unsigned long long size, FILE *out) {
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
            buffer[j] = rand() % CHAR_MAX;
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
    /* Size in KiB */
    unsigned long long size = DEFAULT_CHUNKS;
    /* Output file */
    FILE *out = stdout;
    /* Option parsing return code */
    int opt_code;

    /* Parse options */
    while((opt_code = getopt(argc, argv, "hs")) != -1) {
        switch(opt_code) {
            case 'h':
                print_usage(argc, argv); 
                return 0;
            case 's':
                size = atoi(optarg);
                break;
            default:
                return 0;
        }
    }

    /* Generate the actual text */
    generate_text(size, out);

    return 0;
}
