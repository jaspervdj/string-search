#include <stdio.h>
#include "search-files.h"

/* Entry point for search executables */
int main(int argc, char **argv) {
    /* Check that we have enough arguments. If not, bail out. */
    if(argc < 3) {
        printf("Usage: %s <pattern file> <file> [<file> ...]\n", argv[0]);
        return 1;
    }

    /* Continue using the search_files function */
    return search_files(argv[1], argv + 2, argc - 2);
}
