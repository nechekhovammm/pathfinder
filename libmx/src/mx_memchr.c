#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    const unsigned char *s1 = (unsigned char *) s;
    unsigned char c1 = (unsigned char) c;  // Беремо байт, який шукаємо
    for (size_t i = 0; i < n; ++i)
        if (s1[i] == c1)                   // Знайшли?
            return (void *) (s1 + i);
    return NULL;                           // А не
}
