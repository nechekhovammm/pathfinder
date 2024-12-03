#include "libmx.h"

// Додає буфер до рядка
static int append(char **lineptr, const char *buffer, size_t buf_len, size_t *line_len) {
    *lineptr = realloc(*lineptr, *line_len + buf_len + 1);
    if (!*lineptr) return -1; // Помилка пам'яті
    mx_memcpy(*lineptr + *line_len, buffer, buf_len);
    *line_len += buf_len;
    (*lineptr)[*line_len] = '\0'; // Завершення рядка
    return 0;
}

// Обробляє залишок
static int handle_rem(char **lineptr, char **remainder, size_t *line_len) {
    if (*remainder) {
        *lineptr = mx_strdup(*remainder);
        if (!*lineptr) return -1; // Помилка пам'яті
        *line_len = mx_strlen(*remainder);
        free(*remainder);
        *remainder = NULL;
        return 0;
    }
    *lineptr = malloc(1);
    if (!*lineptr) return -1; // Помилка
    **lineptr = '\0';
    *line_len = 0;
    return 0;
}

// Шукає роздільник
static int find_del(char **lineptr, const char *buffer, size_t buf_size, char delim, char **remainder, size_t *line_len) {
    for (size_t i = 0; i < buf_size; ++i) {
        if (buffer[i] == delim) {
            size_t rem_len = buf_size - (i + 1);
            if (rem_len > 0) {
                *remainder = mx_strndup(buffer + i + 1, rem_len);
                if (!*remainder) return -1; // Помилка пам'яті
            }
            if (append(lineptr, buffer, i, line_len) == -1) return -1;
            return 1; // Знайшли
        }
    }
    return 0; // Не знайдено
}

// Звільняє пам'ять і повертає
static int free_return(int res, char *buffer) {
    free(buffer);
    return res;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static char *rem = NULL;
    char *buffer = malloc(buf_size);
    if (!buffer) return -1; // Помилка пам'яті

    size_t len = 0;
    ssize_t bytes_read = 0;

    if (handle_rem(lineptr, &rem, &len) == -1)
        return free_return(-1, buffer);

    while ((bytes_read = read(fd, buffer, buf_size)) > 0) {
        int result = find_del(lineptr, buffer, bytes_read, delim, &rem, &len);
        if (result == 1) return free_return((int)len, buffer); // Готово
        if (result == -1) return free_return(-1, buffer); // Помилка
        if (append(lineptr, buffer, bytes_read, &len) == -1)
            return free_return(-1, buffer); // Помилка
    }

    free(buffer);
    return (bytes_read == -1) ? -1 : (int)len; // Повернення
}
