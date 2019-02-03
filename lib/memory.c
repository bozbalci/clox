#include <clox/memory.h>

#include <clox/common.h>

#include <stdlib.h>

void *reallocate(void *previous, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(previous);
        return NULL;
    }

    return realloc(previous, newSize);
}