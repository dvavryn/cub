#Makefile for cub3D

# Project name
NAME = cub3D

# Supress directory change
MAKEFLAGS += --no-print-directory

# Colours
GREEN = \033[0;32m
RED = \033[0;31m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx -lmlx -lXext -lX11 -lm
INCLUDES = -I./inc

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC =	src/main.c\
		src/pixelput.c\
		src/draw.c\
		src/key_handler.c\
		src/render.c\
		src/utils.c\
		src/raycast.c\
		src/dda.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
HEAD = inc/cub3d.h

# Rules
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MLX) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) Compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEAD)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)🧹 Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🧹 $(NAME) removed!"

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug