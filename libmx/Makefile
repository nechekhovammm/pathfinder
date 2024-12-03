CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj

LIB = libmx.a

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I$(INC_DIR)

all: $(LIB)

$(LIB): $(OBJ)
	@ar rcs $@ $^
	@echo "Static library $(LIB) created."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(LIB)
	@echo "Cleaned up all generated files."

rebuild: clean all

.PHONY: clean rebuild


