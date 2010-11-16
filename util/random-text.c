#include <stdlib.h>

char *chars_in_string(char *string, int string_size, int *list_size) {
    char *seen_chars = calloc(0x100, sizeof(char));
    char *list = calloc(0x100, sizeof(char));
    int i;

    *list_size = 0;
    for(i = 0; i < string_size; i++) {
        /* Not seen yet */
        if(!seen_chars[(unsigned char) (string[i])]) {
            seen_chars[(unsigned char) (string[i])] = 1;
            list[*list_size] = string[i];
            (*list_size)++;
        }
    }

    free(seen_chars);
    return list;
}

char random_char(char *list, int list_size) {
    return list[rand () % list_size];
}

