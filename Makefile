NAME := cub3d
CC := cc
CFLAGS := -Wall -Wextra -g
INC := -Iinc -Ilibs/libft
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, objs/%.o, $(SRCS))
LIBFT := libs/libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libs/libft -s

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "Compilation completed!"

objs/%.o: src/%.c | objs
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

objs:
	@mkdir -p objs

clean:
	@rm -rf objs
	@make -C libs/libft clean -s

fclean: clean
	@rm -f $(NAME)
	@make -C libs/libft fclean -s

re: fclean all

.PHONY: all clean fclean re