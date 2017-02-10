NAME =	corewar

WFLAGS = -Wall -Werror -Wextra -fsanitize=address

LFLAGS = -L libft/ -lft -lncurses

CC = gcc -g

OBJ = $(SRC:.c=.o)


all : $(NAME)

%.o: %.c
	$(CC) -c $(WFLAGS) -I $(INCLUDES) $< -o $@

$(NAME) : asm vm

asm :
	make -C Corewar_asm
	mv Corewar_asm/asm .
vm :
	make -C Corewar_vm
	mv Corewar_vm/corewar .

clean :
	make -C Corewar_vm clean
	make -C Corewar_asm clean

fclean :
	rm asm vm
	make -C Corewar_vm fclean
	make -C Corewar_asm fclean

re : fclean all


.PHONY: all clean fclean re