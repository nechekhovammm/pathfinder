#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    if (count) *count = 0;
    if (!arr || !s || size <= 0 || !count) return -1;
    
    int left = 0, right = size - 1;
    int mid;

    while (right >= left) {
        (*count)++;
        mid = (left + right) / 2;
        int similarity = mx_strcmp(arr[mid], s);
        
        if (similarity == 0) return mid;  // Найдено!
        else if (similarity < 0) left = mid + 1;
        else right = mid - 1;
    }
    
    *count = 0;  // Сброс
    return -1;
}
