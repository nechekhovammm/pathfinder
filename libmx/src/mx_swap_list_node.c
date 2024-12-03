#include "libmx.h"
void mx_swap_list_node(t_list *a, t_list *b) {
    void *temp = a->data;
    a->data = b->data;
    b->data = temp;
}
