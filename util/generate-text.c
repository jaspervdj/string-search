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

#define TEXT_TYPE_BYTES 0
#define TEXT_TYPE_ALPHA 1
#define TEXT_TYPE_DNA   2

/**
 * Print usage information
 */
void print_usage(int argc, char **argv) {
    printf("USAGE\n");
    printf("%s [options]\n", argv[0]);
    printf("\n");
    printf("OPTIONS\n");
    printf("-a             Only use a-z for the text (Default: bytes)\n");
    printf("-d             Generate a DNA string (ACGT) (Default: bytes)\n");
    printf("-o file        Output file (Default: stdout)\n");
    printf("-s size        Number of %d-byte text chunks (Default: %d)\n",
            BUFFER_SIZE, DEFAULT_CHUNKS);
}

/**
 * Generate a random char
 */
inline unsigned char random_char(int text_type) {
    switch(text_type) {
        case TEXT_TYPE_ALPHA:
            /* Use both lower and upper case */
            switch(rand() % 2) {
                case 0:
                    return 'a' + rand() % ('z' - 'a');
                case 1:
                    return 'A' + rand() % ('Z' - 'A');
            }
        case TEXT_TYPE_DNA:
            switch(rand() % 4) {
                case 0:
                    return 'A';
                case 1:
                    return 'C';
                case 2:
                    return 'G';
                case 3:
                    return 'T';
            }
        case TEXT_TYPE_BYTES: default:
            return rand() % CHAR_MAX;
    }
}

/**
 * Generate random text
 */
void generate_text(int text_type, unsigned long long size, FILE *out) {
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
            buffer[j] = random_char(text_type);
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
    /* Text type */
    int text_type = TEXT_TYPE_BYTES;
    /* Output file */
    FILE *out = stdout;
    /* Size in KiB */
    unsigned long long size = DEFAULT_CHUNKS;
    /* Option parsing return code */
    int opt_code;

    /* Parse options */
    while((opt_code = getopt(argc, argv, "adho:s:")) != -1) {
        switch(opt_code) {
            case 'a':
                text_type = TEXT_TYPE_ALPHA;
                break;
            case 'd':
                text_type = TEXT_TYPE_DNA;
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
    generate_text(text_type, size, out);

    return 0;
}
