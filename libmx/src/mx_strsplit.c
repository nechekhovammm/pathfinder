#include "libmx.h"

// Функція для отримання слова з рядка
static char *get_word(const char *s, char c) {
    while (*s == c && *s) s++;
    int index = mx_get_char_index(s, c);
    if (index == -1) index = mx_strlen(s);

    char *word = mx_strnew(index);
    if (!word) return NULL;
    mx_strncpy(word, s, index);
    return word;
}

// Функція для очищення пам'яті
static void *free_memory(char **arr, int count) {
    if (!arr) return NULL;
    for (int i = 0; i < count; i++) free(arr[i]);
    free(arr);
    return NULL;
}

char **mx_strsplit(const char *s, char c) {
    if (!s) return NULL;

    int word_count = mx_count_words(s, c);
    if (word_count == 0) {
        char **arr = malloc(sizeof(char *));
        if (arr) arr[0] = NULL;
        return arr;
    }

    char **arr = malloc((word_count + 1) * sizeof(char *));
    if (!arr) return NULL;

    for (int i = 0; i < word_count; i++) {
        char *word = get_word(s, c);
        if (!word) return free_memory(arr, i);

        arr[i] = word;
        while (*s == c && *s) s++; // Пропускаємо роздільники
        s += mx_strlen(word);
    }
    arr[word_count] = NULL;
    return arr;
}
