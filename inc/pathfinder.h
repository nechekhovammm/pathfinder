#pragma once

#include "../libmx/inc/libmx.h"

// Замена для INT_MAX (если нет <limits.h>)
#define INT_MAX 2147483647

// Определение структур
typedef struct s_island t_island;
typedef struct s_graph t_graph;
typedef struct s_priority_queue t_priority_queue;
typedef struct s_priority_queue_node t_priority_queue_node;
typedef struct s_adj_list t_adj_list;
typedef struct s_parent_list t_parent_list;
typedef struct s_path t_path;

// Структуры данных
struct s_island {
    char *name;
    int weight;
    t_island *next;
};

struct s_adj_list {
    t_island *head;
};

struct s_graph {
    int vertices;
    t_adj_list *list;
    char **name_list;
};

struct s_priority_queue {
    int size;
    int capacity;
    t_priority_queue_node **nodes;
};

struct s_priority_queue_node {
    int vertex;
    int distance;
    int parent;
};

struct s_parent_list {
    int parent;
    struct s_parent_list *next;
};

struct s_path {
    int *nodes;
    int length;
    int total_distance;
};

// Прототипы функций

// Валидация
void inv_number_arguments(void);
void validate_line(const char *line, int line_num, t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list);
void validate_file_exists(const char *filename);
void validate_file_not_empty(const char *filename);
void validate_bridge_weights(t_graph *graph, char **lines, char *file_content, char **temp_name_list, char **edge_list, char *island_to, char *island_from);
void validate_first_line(const char *line, t_graph *graph, char **lines, char *file_content);
void validate_island_count(t_graph *graph, char **lines, char *file_content, char **temp_name_list, char **edge_list);

// Алгоритмы
void find_paths(t_graph *graph, char **name_list);
void dijkstra(t_graph *graph, int src_idx, const char *src_name, char **name_list, bool **printed_paths);

// Очередь приоритетов
t_priority_queue_node* new_heap_node(int v, int dist);
t_priority_queue* create_min_heap(int capacity);
void free_min_heap(t_priority_queue *min_heap);
void swap_nodes(t_priority_queue_node *a, t_priority_queue_node *b);
void heapify(t_priority_queue *min_heap, int ind);
t_priority_queue_node* extract_min_node(t_priority_queue *min_heap);
void insert_min_node(t_priority_queue *min_heap, t_priority_queue_node *node);

// Работа с графом
t_graph* initialize_graph(int vertex_count);
void graph_add_edge(t_graph *graph, const char *from, const char *to, int weight);
void clear_graph(t_graph **graph); // Добавлено
int mx_get_name_index(t_graph *graph, const char *name); // Добавлено

// Парсер файлов
t_graph* parse_file(const char *filename);

// Алгоритм поиска путей
void pathfinder(t_graph *graph, char **islands_names); // Добавлено

// Печать и вывод
void print_path(t_graph *graph, int *dist, t_parent_list **parents, const char *src_name, char **name_list, bool **printed_paths);

// Утилиты
bool not_a_number(const char *str); // Добавлено
void decrease_key(t_priority_queue *min_heap, int vertex, int distance);
void print_all_paths(t_graph *graph, int src, int dest, t_parent_list **parents,
                     char **name_list, int *path, int path_index);
void graph_add_edge(t_graph *graph, const char *from, const char *to, int weight);
int mx_get_name_index(t_graph *graph, const char *name);
void print_all_paths(t_graph *graph, int src, int dest, t_parent_list **parents,
                     char **name_list, int *path, int path_index);
