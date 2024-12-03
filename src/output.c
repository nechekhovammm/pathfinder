#include "../inc/pathfinder.h"

// Печатает путь между двумя точками
void print_path_between(const char *src_name, const char *dest_name) {
    mx_printstr("Path: ");
    mx_printstr(src_name);
    mx_printstr(" -> ");
    mx_printstr(dest_name);
    mx_printstr("\n");
}

// Печатает маршрут и расстояние
void print_distance_and_route(int *path, int path_len, t_graph *graph, char **name_list) {
    int total_distance = 0;

    mx_printstr("Route: ");
    for (int i = path_len - 1; i >= 0; i--) {
        mx_printstr(name_list[path[i]]);
        if (i > 0) mx_printstr(" -> ");
    }
    mx_printstr("\n");

    mx_printstr("Distance: ");
    for (int i = path_len - 1; i > 0; i--) {
        t_island *adj = graph->list[path[i]].head;
        while (adj) {
            if (mx_get_name_index(graph, adj->name) == path[i - 1]) {
                mx_printint(adj->weight);
                total_distance += adj->weight;
                if (i > 1) mx_printstr(" + ");
                break;
            }
            adj = adj->next;
        }
    }
    if (path_len > 2) {
        mx_printstr(" = ");
        mx_printint(total_distance);
    }
    mx_printstr("\n");
}

// Рекурсивно печатает все пути
void print_all_paths(t_graph *graph, int src, int dest, t_parent_list **parents,
                     char **name_list, int *path, int path_index) {
    path[path_index] = dest;
    path_index++;

    if (dest == src) {
        mx_printstr("========================================\n");
        print_path_between(name_list[src], name_list[path[0]]);
        print_distance_and_route(path, path_index, graph, name_list);
        mx_printstr("========================================\n");
        return;
    }

    for (t_parent_list *p = parents[dest]; p != NULL; p = p->next) {
        print_all_paths(graph, src, p->parent, parents, name_list, path, path_index);
    }
}

// Печатает все пути из источника
void print_path(t_graph *graph, int *dist, t_parent_list **parents,
                const char *src_name, char **name_list, bool **printed_paths) {
    int src_idx = mx_get_name_index(graph, src_name);
    if (src_idx < 0) {
        mx_printerr("Error: Source name not found in the graph.\n");
        return;
    }

    int *path = malloc(graph->vertices * sizeof(int));
    if (!path) {
        mx_printerr("Error: Memory allocation failed for path.\n");
        exit(1);
    }

    for (int i = 0; i < graph->vertices; i++) {
        if (dist[i] == INT_MAX || i == src_idx) {
            continue;
        }

        if (printed_paths[src_idx][i] || printed_paths[i][src_idx]) {
            continue;
        }

        printed_paths[src_idx][i] = true;

        print_all_paths(graph, src_idx, i, parents, name_list, path, 0);
    }

    free(path);
}
