#include "libmx.h"
char *mx_strcat(char *restrict s1, const char *restrict s2) {
    char* s = s1;
    s1 += mx_strlen(s1);
    while (*s2 != '\0') *s1++ = *s2++;
    *s1 = '\0';
    return s;
}
