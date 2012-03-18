#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <swim/stdlib.h>

void * swim_malloc(size_t size) {
    return malloc(size);
}

void swim_free(void * pointer) {
    free(pointer);
}

char * swim_strdup(const char * str) {
    char * dup = swim_malloc(strlen(str) + 1);
    if (dup != NULL) { strcpy(dup, str); }
    return dup;
}
