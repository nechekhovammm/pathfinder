#include "libmx.h"
int mx_get_char_index(const char *str, char c) {
    if (!str) return -2;
    for (int i = 0; *str != '\0'; i++, str++) if (*str == c) return i;
    return -1;
}
