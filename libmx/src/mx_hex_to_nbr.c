#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    if (!hex) return 0; // Якщо ..... повертаємо 0

    unsigned long result = 0;
    while (*hex) {
        char c = *hex++;
        int number;

        if (c >= '0' && c <= '9') number = c - '0'; // Перетворення цифр
        else if (c >= 'a' && c <= 'f') number = c - 'a' + 10; // Перетворення літер
        else if (c >= 'A' && c <= 'F') number = c - 'A' + 10; // Перетворення ЛІТЕР
        else return 0; // Невалідний символ

        result = (result << 4) | number; 
    }
    return result;
}
