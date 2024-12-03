#include "libmx.h"
double mx_pow(double n, unsigned int pow) {
    double result = 1.0;
    for(; pow > 0; pow--) result *= n;
    return result;
}
