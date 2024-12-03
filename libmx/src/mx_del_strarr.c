#include "libmx.h"
void mx_del_strarr(char ***arr) {
    if (!arr || !*arr) return;

    for (int i = 0; (*arr)[i] != NULL; i++) { // Ошибка может быть здесь
        free((*arr)[i]);
        (*arr)[i] = NULL;
    }
    free(*arr);
    *arr = NULL;
}
