#include "../inc/pathfinder.h"

// Функция для реализации алгоритма Дейкстры
void dijkstra(t_graph* graph, int src_idx, const char *src_name, char **name_list, bool **printed_paths) {
    int v = graph->vertices;
    int dist[v];
    t_parent_list *parents[v];
    t_priority_queue *min_heap = create_min_heap(v);

    // Инициализация расстояний и очереди
    for (int i = 0; i < v; i++) {
        dist[i] = INT_MAX;
        parents[i] = NULL; // Инициализация parents[i] как NULL
        insert_min_node(min_heap, new_heap_node(i, INT_MAX));
    }

    // Установка начальной вершины
    dist[src_idx] = 0;
    decrease_key(min_heap, src_idx, dist[src_idx]);

    while (min_heap->size > 0) {
        t_priority_queue_node *min_node = extract_min_node(min_heap);
        int u = min_node->vertex;
        free(min_node);

        t_island *adj = graph->list[u].head;
        while (adj) {
            int adj_idx = mx_get_name_index(graph, adj->name);
            if (dist[u] != INT_MAX && dist[u] + adj->weight < dist[adj_idx]) {
                dist[adj_idx] = dist[u] + adj->weight;
                decrease_key(min_heap, adj_idx, dist[adj_idx]);

                // Обновляем список родителей
                t_parent_list *new_parent = malloc(sizeof(t_parent_list));
                if (!new_parent) {
                    mx_printerr("Memory allocation error\n");
                    exit(1);
                }
                new_parent->parent = u;
                new_parent->next = parents[adj_idx];
                parents[adj_idx] = new_parent;
            }
            adj = adj->next;
        }
    }

    // Выводим пути
    for (int i = 0; i < v; i++) {
        if (i != src_idx) {
            print_path(graph, dist, parents, src_name, name_list, printed_paths);
        }
    }

    // Освобождаем память для min_heap
    free_min_heap(min_heap);

    // Освобождаем память для parents
    for (int i = 0; i < v; i++) {
        while (parents[i]) {
            t_parent_list *temp = parents[i];
            parents[i] = parents[i]->next;
            if (temp) {
                free(temp);
            }
        }
        parents[i] = NULL; // Устанавливаем NULL после освобождения
    }
}

// Функция для нахождения всех путей
void find_paths(t_graph *graph, char **name_list) {
    int v = graph->vertices;

    // Инициализация массивов для расстояний и напечатанных путей
    bool **printed_paths = malloc(v * sizeof(bool *));
    if (!printed_paths) {
        mx_printerr("Memory allocation error\n");
        exit(1);
    }

    for (int i = 0; i < v; i++) {
        printed_paths[i] = malloc(v * sizeof(bool));
        if (!printed_paths[i]) {
            mx_printerr("Memory allocation error\n");
            for (int j = 0; j < i; j++) {
                free(printed_paths[j]);
            }
            free(printed_paths);
            exit(1);
        }
        for (int j = 0; j < v; j++) {
            printed_paths[i][j] = false;
        }
    }

    for (int i = 0; i < v; i++) {
        dijkstra(graph, i, name_list[i], name_list, printed_paths);
    }

    // Освобождение памяти для printed_paths
    for (int i = 0; i < v; i++) {
        if (printed_paths[i]) {
            free(printed_paths[i]);
            printed_paths[i] = NULL; // Устанавливаем NULL после освобождения
        }
    }
    free(printed_paths);
    printed_paths = NULL; // Устанавливаем NULL после освобождения
}
