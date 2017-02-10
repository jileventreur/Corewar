NAME1 =	corewar
NAME2 =	asm

NAME =	$(NAME1) $(NAME2)
WFLAGS = -Wall -Werror -Wextra

LFLAGS = -L libft/ -lft -lncurses

CC = gcc

OBJ = $(SRC:.c=.o)


all : $(NAME)

%.o: %.c
	$(CC) -c $(WFLAGS) -I $(INCLUDES) $< -o $@

$(NAME2) :
	make -C Corewar_asm
	mv Corewar_asm/$(NAME2) .

$(NAME1) :
	make -C Corewar_vm
	mv Corewar_vm/$(NAME1) .

clean :
	make -C Corewar_vm clean
	make -C Corewar_asm clean

fclean :
	rm -rf asm $(NAME)
	make -C Corewar_vm fclean
	make -C Corewar_asm fclean

re : fclean all


.PHONY: all clean fclean re