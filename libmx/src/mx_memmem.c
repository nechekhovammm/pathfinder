#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len,
                const void *little, size_t little_len) {
    // Чекаю на нульову довжину або некоректні вказівн
    if (!big || !little || big_len < little_len || little_len == 0)
        return NULL;

    const unsigned char *b = (const unsigned char *)big;
    const unsigned char *l = (const unsigned char *)little;

    // сухен підрядка в буфері
    for (size_t i = 0; i <= big_len - little_len; ++i)
        if (mx_memcmp(b + i, l, little_len) == 0)
            return (void *)(b + i);

    return NULL; // нема
}
