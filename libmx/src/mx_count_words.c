#include "libmx.h"
int mx_count_words(const char *str, char c) {
    if (!str) return -1;
    int len = mx_strlen(str), counter = 0;
    for (int i = 0; i < len - 1; ++i) if (str[i] == c && str[i + 1] != c) counter++;
    if (len == 0) return 0;
    if (str[len - 1] == c) counter++;
    if (counter == 0) return 1;
    if (str[0] == c && str[len - 1] == c) return counter - 1;
    if (str[0] != c && str[len - 1] != c) return counter + 1;
    return counter;
}
