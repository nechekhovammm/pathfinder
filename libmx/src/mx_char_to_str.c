#include "libmx.h"

char *mx_char_to_str(char c) {
    char *str = mx_strnew(1); // Виділяємо пам'ять для одного символу і '\0'
    if (!str) return NULL;    // Перевірка на успішне виділення пам'яті
    str[0] = c;               // Присвоюємо символ
    return str;
}
