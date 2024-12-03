#include "../inc/pathfinder.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        inv_number_arguments();
    }

    const char *filename = argv[1];

    // Парсинг файла
    t_graph *graph = parse_file(filename);
    if (!graph) {
        mx_printerr("Error parsing file\n");
        return 1;
    }

    // Выполнение алгоритма поиска путей
    pathfinder(graph, graph->name_list);

    // Очистка памяти
    clear_graph(&graph);

    return 0;
}
