#include "libmx.h"

int mx_atoi(const char *str) {
    if (!str) return 0;
    int result = 0;
    int sign = 1;

    while (mx_isspace(*str)) // Пропуск пробелов
        str++;

    if (*str == '-') { // Обработка знака
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (mx_isdigit(*str)) { // Преобразование в число
        result = result * 10 + (*str - '0');
        str++;
    }

    return result * sign;
}
