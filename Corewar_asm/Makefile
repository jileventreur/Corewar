NAME =	asm

SRC =	fasm/main.c\
		fasm/check.c\
		fasm/check_arg.c\
		fasm/check_instruct.c\
		fasm/check_label.c\
		fasm/error.c\
		fasm/free_it.c\
		fasm/ft_strisint.c\
		fasm/ft_strisuint.c\
		fasm/label_replace.c\
		fasm/name_check.c\
		fasm/print_it.c

OBJ = $(SRC:.c=.o)

GCCF = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJ) 
	make -C libft
	gcc -o $(NAME) $(OBJ) -L libft -lft

%.o: %.c libft/libft.h
	gcc -c -I libft $< -o $@

.PHONY: clean fclean re

clean:
	make -C libft fclean
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all