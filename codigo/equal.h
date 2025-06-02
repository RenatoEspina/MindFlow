#ifndef EQUAL_H
#define EQUAL_H

#include <string.h>

int string_equal(void *a, void *b) {
    return strcmp((char *)a, (char *)b) == 0;
}

int int_equal(void *a, void *b) {
    return *(int *)a == *(int *)b;
}

#endif
