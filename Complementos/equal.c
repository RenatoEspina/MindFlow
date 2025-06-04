#include <string.h>
#include "equal.h"

int string_equal(void *a, void *b) {
    return strcmp((char *)a, (char *)b) == 0;
}

int int_equal(void *a, void *b) {
    return *(int *)a == *(int *)b;
}
