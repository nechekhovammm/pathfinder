#include "../inc/pathfinder.h"

// Локальная функция для проверки валидности строки
static void validate_line_local(const char *line, int line_number) {
    int dash_pos = mx_get_char_index(line, '-');
    int comma_pos = mx_get_char_index(line, ',');
    
    if (dash_pos < 0 || comma_pos < 0 || dash_pos >= comma_pos) {
        char *err_message = mx_strjoin("error: line ", mx_itoa(line_number));
        mx_printerr(err_message);
        mx_printerr(" is not valid\n");
        free(err_message);
        exit(1);
    }

    for (int i = 0; line[i]; i++) {
        if (i < dash_pos || (i > dash_pos && i < comma_pos)) {
            if (!mx_isalpha(line[i])) {
                char *err_message = mx_strjoin("error: line ", mx_itoa(line_number));
                mx_printerr(err_message);
                mx_printerr(" is not valid\n");
                free(err_message);
                exit(1);
            }
        } else if (i > comma_pos && !mx_isdigit(line[i])) {
            char *err_message = mx_strjoin("error: line ", mx_itoa(line_number));
            mx_printerr(err_message);
            mx_printerr(" is not valid\n");
            free(err_message);
            exit(1);
        }
    }
}

// Чтение файла
static char *read_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" does not exist\n");
        exit(1);
    }

    char *content = mx_strdup("");
    char buffer[1024];
    int bytes_read;

    while ((bytes_read = read(fd, buffer, 1024)) > 0) {
        char *temp = mx_strjoin(content, buffer);
        free(content);
        content = temp;
    }

    close(fd);

    if (mx_strlen(content) == 0) {
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" is empty\n");
        free(content);
        exit(1);
    }

    return content;
}

// Основная функция парсинга файла
t_graph *parse_file(const char *filename) {
    char *file_content = read_file(filename);
    char **lines = mx_strsplit(file_content, '\n');
    int line_count = 0;

    while (lines[line_count])
        line_count++;

    if (line_count < 2) {
        mx_printerr("error: invalid number of lines\n");
        mx_del_strarr(&lines);
        free(file_content);
        exit(1);
    }

    t_graph *graph = initialize_graph(mx_atoi(lines[0]));

    for (int i = 1; lines[i]; i++) {
        validate_line_local(lines[i], i + 1);  // Используем локальную функцию
        char **parts = mx_strsplit(lines[i], ',');
        char **vertices = mx_strsplit(parts[0], '-');
        
        int weight = mx_atoi(parts[1]);
        if (weight <= 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            mx_del_strarr(&vertices);
            mx_del_strarr(&parts);
            mx_del_strarr(&lines);
            free(file_content);
            exit(1);
        }

        graph_add_edge(graph, vertices[0], vertices[1], weight);

        mx_del_strarr(&vertices);
        mx_del_strarr(&parts);
    }

    mx_del_strarr(&lines);
    free(file_content);
    return graph;
}
