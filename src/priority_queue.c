#include "../inc/pathfinder.h"

// Создание нового узла кучи
t_priority_queue_node* new_heap_node(int v, int dist) {
    t_priority_queue_node* node = malloc(sizeof(t_priority_queue_node));
    if (!node) {
        mx_printerr("Memory allocation error\n");
        exit(1);
    }
    node->distance = dist;
    node->vertex = v;
    node->parent = -1;
    return node;
}

// Создание кучи
t_priority_queue* create_min_heap(int capacity) {
    t_priority_queue* min_heap = malloc(sizeof(t_priority_queue));
    if (!min_heap) {
        mx_printerr("Memory allocation error\n");
        exit(1);
    }
    min_heap->size = 0;
    min_heap->capacity = capacity;
    min_heap->nodes = malloc(capacity * sizeof(t_priority_queue_node *));
    if (!min_heap->nodes) {
        free(min_heap);
        mx_printerr("Memory allocation error\n");
        exit(1);
    }
    return min_heap;
}

// Освобождение кучи
void free_min_heap(t_priority_queue *min_heap) {
    if (!min_heap) return; // Проверка на NULL
    for (int i = 0; i < min_heap->size; i++) {
        if (min_heap->nodes[i]) { // Проверка на NULL перед освобождением
            free(min_heap->nodes[i]);
            min_heap->nodes[i] = NULL; // Установка NULL
        }
    }
    if (min_heap->nodes) {
        free(min_heap->nodes);
        min_heap->nodes = NULL; // Установка NULL
    }
    free(min_heap);
    min_heap = NULL; // Установка NULL
}

// Обмен узлов в куче
void swap_nodes(t_priority_queue_node *a, t_priority_queue_node *b) {
    t_priority_queue_node temp = *a;
    *a = *b;
    *b = temp;
}

// Восстановление кучи
void heapify(t_priority_queue *min_heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < min_heap->size && min_heap->nodes[left]->distance < min_heap->nodes[smallest]->distance)
        smallest = left;

    if (right < min_heap->size && min_heap->nodes[right]->distance < min_heap->nodes[smallest]->distance)
        smallest = right;

    if (smallest != index) {
        swap_nodes(min_heap->nodes[smallest], min_heap->nodes[index]);
        heapify(min_heap, smallest);
    }
}

// Извлечение минимального узла
t_priority_queue_node* extract_min_node(t_priority_queue *min_heap) {
    if (min_heap->size <= 0)
        return NULL;

    t_priority_queue_node *root = min_heap->nodes[0];
    t_priority_queue_node *last_node = min_heap->nodes[min_heap->size - 1];
    min_heap->nodes[0] = last_node;
    min_heap->size--;
    heapify(min_heap, 0);

    return root;
}

// Вставка узла в кучу
void insert_min_node(t_priority_queue *min_heap, t_priority_queue_node *node) {
    if (min_heap->size == min_heap->capacity) {
        mx_printerr("Heap overflow\n");
        return;
    }

    min_heap->size++;
    int i = min_heap->size - 1;
    min_heap->nodes[i] = node;

    while (i != 0 && min_heap->nodes[i]->distance < min_heap->nodes[(i - 1) / 2]->distance) {
        swap_nodes(min_heap->nodes[i], min_heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Уменьшение значения в куче
void decrease_key(t_priority_queue *min_heap, int vertex, int distance) {
    int i;

    // Найти индекс узла в массиве кучи
    for (i = 0; i < min_heap->size; i++) {
        if (min_heap->nodes[i]->vertex == vertex) {
            break;
        }
    }

    if (i == min_heap->size) {
        mx_printerr("Error: Vertex not found in the heap\n");
        return;
    }

    // Обновить расстояние
    min_heap->nodes[i]->distance = distance;

    // Поднятие узла вверх, если это необходимо
    while (i != 0 && min_heap->nodes[i]->distance < min_heap->nodes[(i - 1) / 2]->distance) {
        swap_nodes(min_heap->nodes[i], min_heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
