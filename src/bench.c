#include "search.h"
#include <sys/time.h>

double get_time() {
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

int main(int argc, char **argv) {
    double mean = 0.0;
    int runs = 100;
    int i;

    for(i = 0; i < runs; i++) {
        double start, stop;

        fprintf(stderr, "Starting run %2d/%d...\n", i, runs);

        start = get_time();
        search(argc, argv);
        stop = get_time();

        mean += (stop - start) / (double) runs;
    }

    fprintf(stderr, "Mean: %f\n", mean);

    return 0;
}
