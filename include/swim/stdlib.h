#ifndef SWIM_STDLIB_H
#define SWIM_STDLIB_H

#include <stddef.h>

void * swim_malloc(size_t size);

void swim_free(void * pointer);

char * swim_strdup(const char * str);

#endif /* SWIM_STDLIB_H */
