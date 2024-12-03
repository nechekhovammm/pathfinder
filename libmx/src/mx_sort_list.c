#include "libmx.h"

// Бульбашковий сорт для зв'язаного списку
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    if (!lst || !lst->next || !cmp) return lst; // Перевірка на NULL

    bool sorted = false;
    t_list *temp;

    while (!sorted) {
        sorted = true;
        temp = lst;
        while (temp->next) {
            if (cmp(temp->data, temp->next->data)) {
                // Обмін даними вузлів
                void *swap = temp->data;
                temp->data = temp->next->data;
                temp->next->data = swap;
                sorted = false;
            }
            temp = temp->next;
        }
    }

    return lst;
}
