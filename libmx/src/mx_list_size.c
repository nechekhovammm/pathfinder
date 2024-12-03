#include "libmx.h"
int mx_list_size(t_list *list){
    int size = 0;
    t_list *copy = list;
    for (; copy; copy = copy->next) size++;
    return size;
}
