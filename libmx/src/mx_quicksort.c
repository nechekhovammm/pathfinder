#include "libmx.h"

static void swap_qs(char **a, char **b) {
    if (a == NULL || b == NULL || *a == NULL || *b == NULL) return;
    char *temp = *a;
    *a = *b;
    *b = temp;
}

int mx_quicksort(char **arr, int left_index, int right_index) {
    if (!arr) return -1; // Перевірка масиву

    int swaps = 0;
    int li = left_index;
    int ri = right_index;
    
    if (li == ri) return swaps; // Вихід, якщо один елемент
    
    char *pivot = arr[(li + ri) / 2];
    if (!pivot) return -1; // Перевірка опорного елемента

    while (li <= ri) {
        if (!arr[li] || !arr[ri]) return -1; // Перевірка елементів масиву
        while (mx_strlen(arr[li]) < mx_strlen(pivot)) li++;
        while (mx_strlen(arr[ri]) > mx_strlen(pivot)) ri--;
        
        if (li <= ri) {
            if (li != ri && mx_strlen(arr[li]) != mx_strlen(arr[ri])) {
                swap_qs(&arr[li], &arr[ri]); // Обмін елементів
                swaps++;
            }
            li++;
            ri--;
        }
    }
    
    if (left_index < ri) swaps += mx_quicksort(arr, left_index, ri); // Ліва частина
    if (li < right_index) swaps += mx_quicksort(arr, li, right_index); // Права частина

    return swaps;
}
