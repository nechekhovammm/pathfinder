#include "../inc/pathfinder.h"

void pathfinder(t_graph *graph, char **islands_names) {
    int **distances = malloc(graph->vertices * sizeof(int *));
    t_parent_list **parents = malloc(graph->vertices * sizeof(t_parent_list *));
    bool **printed_paths = malloc(graph->vertices * sizeof(bool *));

    for (int i = 0; i < graph->vertices; i++) {
        distances[i] = malloc(graph->vertices * sizeof(int));
        printed_paths[i] = malloc(graph->vertices * sizeof(bool));
        for (int j = 0; j < graph->vertices; j++) {
            printed_paths[i][j] = false;
        }
    }

    find_paths(graph, islands_names);

    for (int i = 0; i < graph->vertices; i++) {
        free(distances[i]);
        free(printed_paths[i]);
    }

    free(distances);
    free(parents);
    free(printed_paths);
}
