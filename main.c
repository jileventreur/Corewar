#include "corewar.h"

void	ft_error_exit(const char *exit_message)
{
	ft_puterror(exit_message);
	exit(1);
}

// int		dont_overflow(char *arg)
// {
// 	long int			nb;
// 	int					sign;

// 	sign = 1;
// 	nb = 0;
// 	while (ft_isspace(*arg))
// 		arg++;
// 	if (*arg == '+' || *arg == '-')
// 		sign = (*(arg++) == '-') ? -1 : 1;
// 	while (*arg && nb * sign <= INT_MAX && nb * sign >= INT_MIN)
// 	{
// 		nb = nb * 10 + *arg - '0';
// 		arg++;
// 	}
// 	return (nb * sign <= INT_MAX && nb * sign >= INT_MIN);
// }

// int				ft_strisint(char *arg)
// {
// 	int i;

// 	i = 0;
// 	if (!arg[i])
// 		return (0);
// 	while (ft_isspace(arg[i]))
// 		i++;
// 	if (arg[i] == '+' || arg[i] == '-')
// 		i++;
// 	while (arg[i])
// 	{
// 		if (!ft_isdigit(arg[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (dont_overflow(arg));
// }

// int		ft_validchar(char *str, char *valid_char)
// {
// 	int	i;

// 	while (*str)
// 	{
// 		i = 0;
// 		while (valid_char[i] != *str)
// 		{
// 			if (!valid_char[i])
// 				return (0);
// 			++i;
// 		}
// 		++str;
// 	}
// 	return (1);
// }

void	print_memory(unsigned char *mem, unsigned int size)
{
	unsigned int 	i;
	unsigned char	c;

	i = 0;
	while (i < size)
	{
		c = mem[i];
		printf("%2.2x%c%c", c, (i + 1) % 2 == 0 ? ' ' : 0, ((i + 1) % 64) == 0 || i == (size - 1) ? '\n' : 0);
		++i;
	}
}


void	print_champions(t_champion *tab)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!ft_memisset(&tab[i], sizeof(t_champion), 0))
		{
			printf("----- CHAMPION %d -----\n", i + 1);
			printf("NAME = %s\nCOMMENT = %s\n", tab[i].header.prog_name, tab[i].header.comment);
			printf("PROGRAMME:\n");
			print_memory(tab[i].prog, tab[i].header.prog_size);
			printf("-----------------------\n");
		}
		++i;
	}
}

void	print_procs(t_list *lst)
{
	int	i;
	t_proc *tmp;

	printf("----- PROCS -----\n");
	while (lst)
	{
		tmp = (t_proc *)lst->content;
		
		i = 0;
		while (i < REG_NUMBER)
		{
			printf("REG[%d]: %d\n", i, *(int *)tmp->reg[i]);
			++i;
		}
		printf("PC = %d\n", tmp->pc);
		printf("CARRY = %d\n", (int)tmp->carry);
		printf("CYCLE TO WAIT = %u\n", (int)tmp->cycle_to_wait);
		lst = lst->next;
		printf("-----------------\n");
	}
}

void	get_cycle(t_proc *proc, unsigned char *mem)
{
	unsigned char	c;
	extern t_op		op_tab[17];

	c = mem[proc->pc] - 1;
	if (c > 16)
	{
		// printf("%u (0x%x) n'est pas une instruction\n",c + 1,c + 1 );
		proc->cycle_to_wait = 1;
	}
	else
 	{
		proc->cycle_to_wait = op_tab[c].cycle;
 		// printf("ctw = %u\n", proc->cycle_to_wait);
		// printf("l'op code 0x%2.2x correspond a l'instruction %s\n", c, op_tab[c].name);
  	}
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	if (argc == 1)
		ft_error_exit("Error: not enough args\n");
	// if (argc > MAX_PLAYERS + 1)
		// ft_error_exit("Error: too much args\n");
	--argc;
	++argv;
	vm_init(&vm, argc, argv);
	// get_champion(argv[1], &c);
	print_champions(vm.c);
	// printf("\n");
	print_procs(vm.plst);
	print_memory(vm.mem, MEM_SIZE);
	// lst = lst->next;
	// printf("la case contient: [%x]\n", mem[((t_proc *)lst->content)->pc]);
	return (0);
}