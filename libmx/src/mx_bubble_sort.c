#include "libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int swaps = 0;
    int swapped = 1;
    for (int i = 0; i < size - 1 && swapped; i++) {
        swapped = 0;  // Скидаємо прапорець
        for (int j = 0; j < size - i - 1; j++) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {  // Перевірка порядку
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
                swapped = 1;
            }
        }
    }
    return swaps;
}
