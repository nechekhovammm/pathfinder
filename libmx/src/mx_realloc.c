#include "libmx.h"
void *mx_realloc(void *ptr, size_t size) {
    if (size == 0 && ptr) {
        free(ptr);
        return NULL;
    }

    if (!ptr) {
        return malloc(size);
    }

    // Немає необхідності в malloc_usable_size, замінимо на стандартний realloc
    void *new_ptr = realloc(ptr, size);
    return new_ptr;
}

