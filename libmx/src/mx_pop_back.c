#include "libmx.h"
void mx_pop_back(t_list **head){
    if (head == NULL || *head == NULL) return;
    t_list *current = *head;
    if (current->next == NULL) { // one node list
        free(*head);
        *head = NULL;
        return;
    }
    while (current->next->next != NULL) current = current->next;
    free(current->next);
    current->next = NULL;
}
