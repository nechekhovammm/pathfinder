#include "libmx.h"

void *mx_memmove(void *dst, void *src, size_t len) {
    unsigned char *d = (unsigned char *)dst;
    unsigned char *s = (unsigned char *)src;

    if (d == s) return dst;

    if (d < s) {
        return mx_memcpy(dst, src, len); // Копіюємо вперед
    } else {
        for (size_t i = len; i > 0; i--) {
            d[i - 1] = s[i - 1]; // Копіюємо назад 
        }
    }

    return dst;
}
