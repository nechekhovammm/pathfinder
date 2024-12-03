#include "libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    if (!s1 && !s2) return NULL; // Обидва NULL
    if (!s1) return mx_strdup(s2); // s1 NULL
    if (!s2) return mx_strdup(s1); // s2 NULL

    int total_length = mx_strlen(s1) + mx_strlen(s2);
    char *result = mx_strnew(total_length);
    if (!result) return NULL; // Помилка пам'яті

    mx_strcpy(result, s1); // Копіюємо s1
    mx_strcat(result, s2); // Додаємо s2

    return result;
}
