NAME	:= libft.a
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror

SRCS	:=\
		./ft_ctype/ft_isalnum.c\
		./ft_ctype/ft_isalpha.c\
		./ft_ctype/ft_isascii.c\
		./ft_ctype/ft_isdigit.c\
		./ft_ctype/ft_isprint.c\
		./ft_ctype/ft_isspace.c\
		./ft_ctype/ft_tolower.c\
		./ft_ctype/ft_toupper.c\
		\
		./ft_custom/ft_split.c\
		./ft_custom/ft_striteri.c\
		./ft_custom/ft_strjoin.c\
		./ft_custom/ft_strjoinc.c\
		./ft_custom/ft_strmapi.c\
		./ft_custom/ft_strtrim.c\
		./ft_custom/ft_substr.c\
		./ft_custom/free_split.c\
		\
		./ft_lst/ft_lstadd_back.c\
		./ft_lst/ft_lstadd_front.c\
		./ft_lst/ft_lstclear.c\
		./ft_lst/ft_lstdelone.c\
		./ft_lst/ft_lstiter.c\
		./ft_lst/ft_lstlast.c\
		./ft_lst/ft_lstnew.c\
		./ft_lst/ft_lstsize.c\
		\
		./ft_printf/ft_printf.c\
		./ft_printf/ft_putchar.c\
		./ft_printf/ft_puts.c\
		./ft_printf/ft_putnbr.c\
		./ft_printf/ft_putunbr.c\
		./ft_printf/ft_putnbr_hex.c\
		./ft_printf/ft_padress.c\
		./ft_printf/ft_putulong_hex.c\
		\
		./ft_put_fd/ft_putchar_fd.c\
		./ft_put_fd/ft_putendl_fd.c\
		./ft_put_fd/ft_putnbr_fd.c\
		./ft_put_fd/ft_putstr_fd.c\
		\
		./ft_stdlib/ft_atoi.c\
		./ft_stdlib/ft_atol.c\
		./ft_stdlib/ft_calloc.c\
		./ft_stdlib/ft_itoa.c\
		./ft_stdlib/ft_realloc.c\
		\
		./ft_string/ft_bzero.c\
		./ft_string/ft_memchr.c\
		./ft_string/ft_memcmp.c\
		./ft_string/ft_memcpy.c\
		./ft_string/ft_memmove.c\
		./ft_string/ft_memset.c\
		./ft_string/ft_strchr.c\
		./ft_string/ft_strdup.c\
		./ft_string/ft_strndup.c\
		./ft_string/ft_strlcat.c\
		./ft_string/ft_strlcpy.c\
		./ft_string/ft_strlen.c\
		./ft_string/ft_strncmp.c\
		./ft_string/ft_strcmp.c\
		./ft_string/ft_strnstr.c\
		./ft_string/ft_strrchr.c\
		\
		./get_next_line/get_next_line.c\
		./get_next_line/get_next_line_utils.c\

OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re









