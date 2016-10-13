NAME =	corewar

INCLUDES = libft/includes/

SRC =	ft_lstadd.c \
		ft_lstnew.c \
		ft_memisset.c \
		ft_strisuint.c \
		get_players.c \
		main.c \
		op.c \
		print_fct.c \
		vm_init.c

WFLAGS = -Wall -Werror -Wextra

LFLAGS = -L libft/ -lft

CC = gcc -g

OBJ = $(SRC:.c=.o)


all : $(NAME)

%.o: %.c
	$(CC) -c $(WFLAGS) -I $(INCLUDES) $< -o $@

$(NAME) : $(OBJ)
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(WFLAGS) $(SDL) $(LFLAGS)

clean :
	rm -rf $(OBJ)
	make -C libft clean

fclean : clean
	rm -f $(NAME)
	make -C libft fclean

re : fclean all

lre :
	make -C libft/ re

.PHONY: all clean fclean re