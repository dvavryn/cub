NAME := cub3d
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
INC := -Iinc -Ilibs/libft
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, objs/%.o, $(SRCS))
LIBFT := libs/libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libs/libft

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

objs/%.o: src/%.c | objs
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

objs:
	@mkdir -p objs

clean:
	@rm -rf objs
	@make -C libs/libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libs/libft fclean

re: fclean all

.PHONY: all clean fclean re