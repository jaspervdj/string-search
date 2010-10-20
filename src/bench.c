/**
 * Main method for benchmarking
 */
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include "search.h"

/**
 * A more precise verion of time()
 */
double get_time() {
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

/**
 * Print usage informations
 */
void print_usage(int argc, char **argv) {
    printf("USAGE\n");
    printf("%s [options]\n", argv[0]);
    printf("\n");
    printf("OPTIONS\n");
    printf("-h         Print this info\n");
    printf("-n num     Number of timed runs (Default: 100)\n");
    printf("-o file    Write benchmarks results to (Default: stderr)\n");
    printf("-w num     Number of warmup runs (Default: 10)\n");
    printf("\n");
}

/**
 * Main method
 */
int main(int argc, char **argv) {
    int runs = 100;
    FILE *out = stderr;
    int warmup_runs = 10;
    int opt_code;

    double mean = 0.0;
    int i;

    while((opt_code = getopt(argc, argv, "hn:o:w:")) != -1) {
        switch(opt_code) {
            case 'h':
                print_usage(argc, argv);
                return 0;
            case 'n':
                runs = atoi(optarg);
                break;
            case 'o':
                out = fopen(optarg, "w");
                break;
            case 'w':
                warmup_runs = atoi(optarg);
                break;
            default:
                return 1;
        }
    }

    for(i = 0; i < runs; i++) {
        double start, stop;

        fprintf(stderr, "Starting run %2d/%d...\n", i, runs);

        start = get_time();
        search(argv[optind], argv + optind + 1, argc - optind - 1);
        stop = get_time();

        mean += (stop - start) / (double) runs;
    }

    fprintf(stderr, "Mean: %f\n", mean);

    return 0;
}
