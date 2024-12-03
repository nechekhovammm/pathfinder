#include "libmx.h"

void mx_printstr(const char *s) {
    while (*s) {
        write(1, s++, 1);
    }
}

