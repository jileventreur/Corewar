NAME =	corewar

WFLAGS = -Wall -Werror -Wextra -fsanitize=address

LFLAGS = -L libft/ -lft -lncurses

CC = gcc

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
	mv Corewar_vm/corewar vm

clean :
	make -C Corewar_vm clean
	make -C Corewar_asm clean

fclean :
	rm -rf asm vm
	make -C Corewar_vm fclean
	make -C Corewar_asm fclean

re : fclean all


.PHONY: all clean fclean re