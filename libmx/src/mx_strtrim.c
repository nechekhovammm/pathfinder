#include "libmx.h"

char *mx_strtrim(const char *str) {
    if (!str) return NULL; // Перевірка на NULL

    const char *start = str;
    const char *end = str + mx_strlen(str) - 1;

    while (*start && mx_isspace(*start)) start++; // Пропускаємо початок
    if (start > end) return mx_strnew(0); // Весь рядок — пробіли

    while (end > start && mx_isspace(*end)) end--; // Пропускаємо кінець

    int n_len = end - start + 1;
    char *result = mx_strnew(n_len);
    if (!result) return NULL; // Перевірка пам'яті

    return mx_strncpy(result, start, n_len); // Копія очищеного
}
