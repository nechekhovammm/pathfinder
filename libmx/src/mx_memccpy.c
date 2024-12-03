#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    while (n-- > 0) {
        *d++ = *s++;
        if (*(d - 1) == (unsigned char)c) {
            return d;
        }
    }
    return NULL;
}
//kj[
