#include "libmx.h"
int mx_get_substr_index(const char *str, const char *sub) {
    if (!str || !sub) return -2;
    char *p_sub = mx_strstr(str, sub);
    if (!p_sub || mx_strlen(str) == 0 || mx_strlen(sub) == 0) return -1;
    return (int)(p_sub - str);
}
