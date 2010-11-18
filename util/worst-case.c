/**
 * Utility to generate worst-case scenario's
 */
#include <unistd.h>
#include <stdio.h>

#define CHUNK_SIZE 1024
#define DEFAULT_CHUNKS 4

/**
 * Print usage information
 */
void print_usage(int argc, char **argv) {
    printf("USAGE\n");
    printf("%s [options]\n", argv[0]);
    printf("\n");
    printf("OPTIONS\n");
    printf("-o file    Output file (Default: stdout)\n");
    printf("-s size    Number of %d-byte text chunks (Default: %d)\n",
            CHUNK_SIZE, DEFAULT_CHUNKS);
}

/**
 * Generate random text
 */
void worst_case(unsigned long long size, FILE *out) {
    unsigned long long i;
    for(i = 0; i < size - 1; i++) fwrite("a", sizeof(char), 1, out);
    fwrite("b", sizeof(char), 1, out);
}

/**
 * Main function
 */
int main(int argc, char **argv) {
    /* Output file */
    FILE *out = stdout;
    /* Size in chunks */
    unsigned long long chunks = DEFAULT_CHUNKS;
    /* Option parsing return code */
    int opt_code;

    /* Parse options */
    while((opt_code = getopt(argc, argv, "ho:s:")) != -1) {
        switch(opt_code) {
            /* Print help */
            case 'h':
                print_usage(argc, argv); 
                return 0;

            /* Set output file */
            case 'o':
                out = fopen(optarg, "w");
                break;

            /* Set text size */
            case 's':
                chunks = atoi(optarg);
                break;

            /* All else */
            default:
                return 0;
        }
    }

    /* Generate the actual text */
    worst_case(chunks * CHUNK_SIZE, out);

    return 0;
}
