#include "libmx.h"

// Функція виконує заміни підрядків
static char *logic(const char *str, const char *sub, const char *replace) {
    int sub_len = mx_strlen(sub);
    int rep_len = mx_strlen(replace);
    int sub_count = mx_count_substr(str, sub);

    if (sub_count == 0) return mx_strdup(str); // Немає що замінювати — бери оригінал

    // Розраховуємо довжину нового рядка з урахуванням замін
    int new_len = mx_strlen(str) + sub_count * (rep_len - sub_len);
    char *result = mx_strnew(new_len);
    if (!result) return NULL; // Пам'ять не виділилася
    char *r_ptr = result;
    const char *s_ptr = str;
    const char *found;

    // Замінюємо всі входження підрядка
    while ((found = mx_strstr(s_ptr, sub)) != NULL) {
        // Копіюємо частину до знайденого підрядка
        r_ptr = mx_strncpy(r_ptr, s_ptr, found - s_ptr);
        r_ptr += found - s_ptr;

        // Ставимо новий підрядок
        r_ptr = mx_strncpy(r_ptr, replace, rep_len);
        r_ptr += rep_len;

        s_ptr = found + sub_len;
    }

    // Копіюємо все, що залишилось
    mx_strcpy(r_ptr, s_ptr);
    return result;
}

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace) return NULL;
    if (mx_strlen(sub) == 0) return mx_strdup(str);
    return logic(str, sub, replace);
}

