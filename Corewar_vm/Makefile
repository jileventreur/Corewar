NAME =	corewar

LIBFT_INC = libft/includes
CORE_INC = includes

DIR_SRC = src/

FILES =	aff.c \
		calculation_instructions.c \
		check_and_destroy.c \
		exec_vm.c \
		fork_and_lfork.c \
		ft_lstadd.c \
		ft_lstnew.c \
		get_args.c \
		get_opt.c \
		get_players.c \
		graphic_vm.c \
		ld_and_lld.c \
		ldi_and_lldi.c \
		live.c \
		main.c \
		manage_infos.c \
		moove_pc.c \
		op.c \
		print_args.c \
		print_players.c \
		print_procs.c \
		print_usage.c \
		print_wait_end.c \
		st_and_sti.c \
		vm_init.c \
		window.c \
		zjmp.c
WFLAGS = -Wall -Werror -Wextra

SRC := $(addprefix $(DIR_SRC), $(FILES))

LFLAGS = -L libft/ -lft -lncurses

CC = gcc

OBJ = $(SRC:.c=.o)


all : $(NAME)

%.o: %.c
	$(CC) -c $(WFLAGS) -I $(LIBFT_INC) -I $(CORE_INC) $< -o $@

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