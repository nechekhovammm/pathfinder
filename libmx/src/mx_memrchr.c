#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    const unsigned char *ptr = s;
    for (size_t i = n; i > 0; i--) {
        if (ptr[i - 1] == (unsigned char)c) { // Йдемо з кінця
            return (void *)(ptr + i - 1);
        }
    }
    return NULL;  // Не знайшли ?? ПО новой Миша все ...
}