#include "libmx.h"

static int count_len(const char *file) {
    int fd = open(file, O_RDONLY);
    if (fd < 0) return -1; // Помилка відкриття

    int len = 0;
    char buf;
    ssize_t bread;

    while ((bread = read(fd, &buf, 1)) > 0) len++; // Підрахунок символів
    if (bread < 0) {
        close(fd);
        return -1; // Помилка читання
    }

    if (close(fd) < 0) return -1; // Помилка закриття
    return len;
}

static char *logic(const char *file, int len) {
    char *result = mx_strnew(len);
    if (!result) return NULL; // Помилка пам'яті

    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        free(result);
        return NULL; // Помилка відкриття
    }

    if (read(fd, result, len) < len) {
        free(result);
        close(fd);
        return NULL; // Помилка читання
    }

    if (close(fd) < 0) {
        free(result);
        return NULL; // Помилка закриття
    }

    return result;
}

char *mx_file_to_str(const char *file) {
    if (!file) return NULL; // Перевірка на NULL
    int len = count_len(file);
    if (len <= 0) return (len == 0) ? mx_strnew(0) : NULL; // Обробка довжини
    return logic(file, len);
}
