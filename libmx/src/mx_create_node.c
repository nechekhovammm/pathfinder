#include "libmx.h"

t_list *mx_create_node(void *data) {
    t_list *node = (t_list *)malloc(sizeof(t_list));
    if (!node) return NULL; // Перевірка виділення пам'яті
    node->data = data; // Ініціалізація даними
    node->next = NULL; // Наступний вузол - NULL
    return node;
}
