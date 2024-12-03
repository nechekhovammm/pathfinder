#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    if (nbr == 0) return mx_char_to_str('0');
    unsigned long size = 0;
    char str[256];
    const char *hex_digits = "0123456789abcdef"; // Таблиця шістнадцяткових цифр
    while (nbr > 0) {
        str[size++] = hex_digits[nbr % 16];
        nbr /= 16;
    }
    char *result = mx_strnew((int)size);
    if (result == NULL) return NULL;
    for (unsigned long i = 0; i < size; i++) {
        result[i] = str[size - i - 1];
    }
    return result;
}
