# Название финального исполняемого файла
NAME = pathfinder

# Компилятор и флаги
CC = clang
CFLAGS = -fsanitize=address -g -Wall -Wextra -Werror -Wpedantic -Iinc -Ilibmx/inc
LDFLAGS = -Llibmx -lmx

# Каталоги
SRCD = src
INCD = inc
OBJD = obj
LIBD = libmx

# Исходные файлы
SRCS = $(SRCD)/main.c \
       $(SRCD)/graph_operation.c \
       $(SRCD)/priority_queue.c \
       $(SRCD)/file_parser.c \
       $(SRCD)/shortest_paths.c \
       $(SRCD)/output.c \
       $(SRCD)/input_validator.c \
       $(SRCD)/pathfinder.c

# Объектные файлы
OBJS = $(SRCS:$(SRCD)/%.c=$(OBJD)/%.o)

# Библиотека
LIBMX = $(LIBD)/libmx.a

# Основное правило
all: $(NAME)

# Линковка
$(NAME): $(OBJS) $(LIBMX)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Компиляция объектных файлов
$(OBJD)/%.o: $(SRCD)/%.c | $(OBJD)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание директории для объектных файлов
$(OBJD):
	mkdir -p $(OBJD)

# Сборка библиотеки
$(LIBMX):
	$(MAKE) -C $(LIBD)

# Очистка
clean:
	rm -rf $(OBJD)
	rm -f $(NAME)
	$(MAKE) clean -C $(LIBD)

uninstall: clean
	$(MAKE) uninstall -C $(LIBD)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
