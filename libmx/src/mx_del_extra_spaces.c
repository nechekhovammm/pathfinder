#include "libmx.h"
char *mx_del_extra_spaces(const char *str) {
    if (!str) return NULL; // Перевірка на NULL

    char *trimmed = mx_strtrim(str);
    if (!trimmed) return NULL; // Перевірка обрізки

    char *temp = mx_strnew(mx_strlen(trimmed));
    int nl = 0; // Довжина нового рядка

    for (int i = 0; trimmed[i]; i++) {
        if (!mx_isspace(trimmed[i])) 
            temp[nl++] = trimmed[i]; // Копіюємо символ
        else if (nl > 0 && !mx_isspace(temp[nl - 1])) 
            temp[nl++] = ' '; // + пробіл
    }

    char *result = mx_strnew(nl);
    mx_strncpy(result, temp, nl); // Ко
    free(temp);
    free(trimmed);
    return result;
}
