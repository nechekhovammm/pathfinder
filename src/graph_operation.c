#include "../inc/pathfinder.h"

// Инициализация графа
t_graph* initialize_graph(int vertex_count) {
    t_graph* graph = malloc(sizeof(t_graph));
    if (!graph) {
        mx_printerr("error: memory allocation failed\n");
        exit(1);
    }

    graph->vertices = vertex_count;
    graph->list = malloc(vertex_count * sizeof(t_adj_list));
    graph->name_list = malloc(vertex_count * sizeof(char*));

    if (!graph->list || !graph->name_list) {
        mx_printerr("error: memory allocation failed\n");
        free(graph->list);
        free(graph->name_list);
        free(graph);
        exit(1);
    }

    for (int i = 0; i < vertex_count; i++) {
        graph->list[i].head = NULL;
        graph->name_list[i] = NULL; // Инициализация каждого указателя
    }

    return graph;
}

// Добавление ребра в граф
void graph_add_edge(t_graph* graph, const char* from, const char* to, int weight) {
    int from_idx = mx_get_name_index(graph, from);
    int to_idx = mx_get_name_index(graph, to);

    // Если вершина не найдена, добавляем её в список имен
    if (from_idx == -1) {
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->name_list[i] == NULL) {
                graph->name_list[i] = mx_strdup(from);
                from_idx = i;
                break;
            }
        }
    }

    if (to_idx == -1) {
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->name_list[i] == NULL) {
                graph->name_list[i] = mx_strdup(to);
                to_idx = i;
                break;
            }
        }
    }

    if (from_idx == -1 || to_idx == -1) {
        mx_printerr("error: unable to find space for vertices\n");
        exit(1);
    }

    // Добавляем ребро из from в to
    t_island* new_island = malloc(sizeof(t_island));
    if (!new_island) {
        mx_printerr("error: memory allocation failed\n");
        exit(1);
    }
    new_island->name = mx_strdup(to);
    new_island->weight = weight;
    new_island->next = graph->list[from_idx].head;
    graph->list[from_idx].head = new_island;

    // Добавляем обратное ребро для неориентированного графа
    new_island = malloc(sizeof(t_island));
    if (!new_island) {
        mx_printerr("error: memory allocation failed\n");
        exit(1);
    }
    new_island->name = mx_strdup(from);
    new_island->weight = weight;
    new_island->next = graph->list[to_idx].head;
    graph->list[to_idx].head = new_island;
}

// Очистка графа
void clear_graph(t_graph **graph) {
    if (!graph || !*graph) return;

    // Очистка списка смежности
    for (int i = 0; i < (*graph)->vertices; i++) {
        t_island *current = (*graph)->list[i].head;
        while (current) {
            t_island *temp = current;
            current = current->next;
            mx_strdel(&temp->name);
            free(temp);
        }
    }

    free((*graph)->list);
    (*graph)->list = NULL;

    // Очистка списка имен
    if ((*graph)->name_list) {
        for (int i = 0; i < (*graph)->vertices; i++) {
            if ((*graph)->name_list[i]) {
                mx_strdel(&(*graph)->name_list[i]);
            }
        }
        free((*graph)->name_list);
        (*graph)->name_list = NULL;
    }

    free(*graph);
    *graph = NULL;
}

// Получение индекса имени вершины
int mx_get_name_index(t_graph *graph, const char *name) {
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->name_list[i] && mx_strcmp(graph->name_list[i], name) == 0) {
            return i;
        }
    }
    return -1; // Если имя не найдено
}
