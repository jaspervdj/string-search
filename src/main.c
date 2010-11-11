#include "search-files.h"

int main(int argc, char **argv) {
    /* Check that we have enough arguments. If not, bail out. */
    if(argc < 3) {
        printf("Usage: %s <pattern file> <file> [<file> ...]\n", argv[0]);
        return 1;
    }

    return search_files(argv[1], argv + 2, argc - 2);
}
