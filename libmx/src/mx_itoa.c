#include "libmx.h"

char *mx_itoa(int number) {
    if (number == 0) return mx_char_to_str('0');
    char str[64];
    int size = 0;
    long long int copy = (long long int) number;
    int minus = (number < 0) ? 1 : 0;
    if (minus) copy = -copy; // Перетворення числа на рядок у зворотному порядку
    for (; copy > 0; copy /= 10) str[size++] = (char)((copy % 10) + '0');
    if (minus) str[size++] = '-';
    char *result = mx_strnew(size);
    if (!result) return NULL; // Реверс рядка
    for (int i = 0; i < size; i++) result[i] = str[size - i - 1];
    return result;
}
