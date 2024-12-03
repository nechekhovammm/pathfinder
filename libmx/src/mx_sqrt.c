#include "libmx.h"
int mx_sqrt(int x) {
    if (x < 0) return 0; // В школі казали корінь з -числа не беруть .... 
    int left = 0;
    int right = (x < 46341) ? x : 46340; // щоб не зламати INT_MAX
    while (left <= right) {
        int mid = left + (right - left) / 2; // Вгадуєм середину
        int sq = mid * mid;
        if (sq == x) return mid; // О!
        else if (sq < x) left = mid + 1; // вище
        else right = mid - 1; // Ні нижче
    }
    return 0; // ):
}

