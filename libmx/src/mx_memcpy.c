#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    while (n-- > 0) {
        *d++ = *s++; // Копіюємо байт за байтом
    }
    return dst;
}
