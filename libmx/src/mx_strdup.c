#include "libmx.h"
char *mx_strdup(const char *s1) {
    char *copy = mx_strnew(mx_strlen(s1));

    if (!copy) return NULL;
    return mx_strcpy(copy, s1);
}
