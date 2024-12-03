#include "../inc/pathfinder.h"

// Генерация сообщения об ошибке
void generate_error_message(const char *line_num_str, char **message) {
    int length = 15 + mx_strlen(line_num_str) + 14;
    *message = mx_strnew(length);
    mx_strcpy(*message, "error: line ");
    mx_strcat(*message, line_num_str);
    mx_strcat(*message, " is not valid\n");
}

// Обработка ошибки и очистка ресурсов
void handle_error(const char *message, t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list) {
    if (message) {
        mx_printerr(message);
    }
    if (filestr) mx_strdel(&filestr);
    if (lines) mx_del_strarr(&lines);
    if (graph) clear_graph(&graph);
    if (temp_name_list) mx_del_strarr(&temp_name_list);
    if (edge_list) mx_del_strarr(&edge_list);
    exit(-1);
}

// Проверка существования файла
void error_file_not_exist(const char *filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" does not exist\n");
    exit(-1);
}

// Проверка пустого файла
void error_file_empty(const char *filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" is empty\n");
    exit(-1);
}

// Проверка превышения длины мостов
void bridge_overload(t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list, char *island_to, char *island_from) {
    handle_error("error: sum of bridges lengths is too big\n", graph, lines, filestr, temp_name_list, edge_list);
    mx_strdel(&island_to);
    mx_strdel(&island_from);
}

// Проверка первой строки файла
void check_first_line(const char *firstline, t_graph *graph, char **lines, char *filestr) {
    if (not_a_number(firstline) || firstline[0] == '0') {
        handle_error("error: line 1 is not valid\n", graph, lines, filestr, NULL, NULL);
    }

    long long value = mx_atoi(firstline);
    if (value <= 0 || value > INT_MAX) {
        handle_error("error: line 1 is not valid\n", graph, lines, filestr, NULL, NULL);
    }
}

// Неправильное количество аргументов
void inv_number_arguments(void) {
    mx_printerr("usage: ./pathfinder [filename]\n");
    exit(-1);
}

// Проверка количества островов
void islands_number(t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list) {
    handle_error("error: invalid number of islands\n", graph, lines, filestr, temp_name_list, edge_list);
}

// Неверная строка
void is_invalid_line(int idx) {
    char *line_str = mx_itoa(idx);
    mx_printerr("error: line ");
    mx_printerr(line_str);
    mx_printerr(" is not valid\n");
    mx_strdel(&line_str);
    exit(-1);
}

// Проверка на дублирование мостов
int is_dup(char *edge, char **edge_list, int edge_count, t_graph *graph, char **lines, char *filestr, char **temp_name_list, char *island_to, char *island_from) {
    for (int i = 0; i < edge_count; i++) {
        if (mx_strcmp(edge, edge_list[i]) == 0) {
            handle_error("error: duplicate bridges\n", graph, lines, filestr, temp_name_list, edge_list);
            mx_strdel(&island_to);
            mx_strdel(&island_from);
            return 1;
        }
    }
    return 0;
}

// Проверка строки на корректность
void validate_line(const char *line, int line_num, t_graph *graph, char **lines, char *filestr, char **temp_name_list, char **edge_list) {
    char *line_num_str = mx_itoa(line_num);
    char *error_message = NULL;

    int dash_index = mx_get_char_index(line, '-');
    if (dash_index < 1) {
        generate_error_message(line_num_str, &error_message);
        handle_error(error_message, graph, lines, filestr, temp_name_list, edge_list);
    }

    int comma_index = mx_get_char_index(line, ',');
    if (comma_index <= dash_index + 1) {
        generate_error_message(line_num_str, &error_message);
        handle_error(error_message, graph, lines, filestr, temp_name_list, edge_list);
    }

    const char *weight_str = &line[comma_index + 1];
    long long weight_ll = mx_atoi(weight_str);
    if (not_a_number(weight_str) || weight_str[0] == '-' || weight_str[0] == '0' || weight_ll <= 0 || weight_ll > INT_MAX) {
        generate_error_message(line_num_str, &error_message);
        handle_error(error_message, graph, lines, filestr, temp_name_list, edge_list);
    }

    char *island_from = mx_strndup(line, dash_index);
    char *island_to = mx_strndup(&line[dash_index + 1], comma_index - dash_index - 1);
    if (mx_strcmp(island_from, island_to) == 0) {
        mx_strdel(&island_from);
        mx_strdel(&island_to);
        generate_error_message(line_num_str, &error_message);
        handle_error(error_message, graph, lines, filestr, temp_name_list, edge_list);
    }

    mx_strdel(&island_from);
    mx_strdel(&island_to);
    mx_strdel(&line_num_str);
    mx_strdel(&error_message);
}

// Проверка на число
bool not_a_number(const char *str) {
    if (!str || !*str) return true;

    for (int i = 0; str[i]; i++) {
        if (!mx_isdigit(str[i])) {
            return true;
        }
    }
    return false;
}
