#include "corewar.h"

void	ft_error_exit(const char *exit_message)
{
	ft_puterror(exit_message);
	exit(1);
}

void	print_vm(t_vm *vm)
{
	unsigned int 	i;
	unsigned char	c;
	char	color[10];
	// char	pc_color[10];

	i = 0;
	ft_putstr(CLEAR_SCREEN);
	ft_strcpy(color, "\033[30;40m");
	// ft_strcpy(color, "\033[31;1m");
	// printf("COLOR == %c\n", color[3]);
	while (i < MEM_SIZE)
	// while (i < 5)
	{
		c = vm->mem[i];
	// ft_strcpy(color, "\033[30;40m");
	// color[6] = '0' + (0b11 & vm->proc_mem[i]);
	if (ISACTIV(vm->proc_mem[i], 2))
	{
		color[6] = '0' + (0b11 & vm->proc_mem[i]);
		color[3] = '0';
	}
	else
	{
		color[3] = '0' + (0b11 & vm->proc_mem[i]);
		color[6] = '0';		
	}
		// color[6] = ISACTIV(vm->proc_mem[i], 2) ? '7' : '0';
		// printf("COLOR == %c\n", color[2]);
		// exit(1);
		// if (ISACTIV(vm->proc_mem[i], 2))
		// 	ft_printf("%s%2.2x%c%c\033[0m", vm->proc_mem[i] == 0 ? "" : pc_color, c,
		// 	(i + 1) % 2 == 0 ? ' ' : 0, ((i + 1) % BYTE_LINE_NB) == 0 || i == (MEM_SIZE - 1) ? '\n' : 0);
		// else
		ft_printf("%s%2.2x\033[0m%c%c", vm->proc_mem[i] == 0 ? "" : color, c,
		(i + 1) % 2 == 0 ? ' ' : 0, ((i + 1) % BYTE_LINE_NB) == 0 || i == (MEM_SIZE - 1) ? '\n' : 0);
		++i;
	}
	// ft_printf("\n");
	// exit(1);
}

void	get_proc_cycle(t_proc *proc, unsigned char *mem)
{
	unsigned char	c;
	extern t_op		op_tab[INSTR_NUMBER + 1];

	c = mem[proc->pc] - 1;
	if (c > 16)
	{
		// 2f("%u (0x%x) n'est pas une instruction\n",c + 1,c + 1 );
		proc->cycle_to_wait = 1;
	}
	else
 	{
		proc->cycle_to_wait = op_tab[c].cycle;
 		// printf("ctw = %u\n", proc->cycle_to_wait);
		// printf("l'op code 0x%2.2x correspond a l'instruction %s\n", c, op_tab[c].name);
  	}
}

void print_bits(unsigned int nb, int i)
{
	if (!i)
		return ;
	print_bits(nb >> 1, i - 1);
	printf("%c%c", nb % 2 ? '1' : '0', i == sizeof(char) * 8 ? '\n' : 0);
}

void		null_instr(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	int i = 0;
	int	ptr;
	unsigned short int *test;

	(void)args;
	while (i < 4)
	{
		// printf("args_type[%d] = %d\n", i, args_type[i]);
		++i;
	}
	ptr = (proc->pc + 2) % MEM_SIZE;
	test = (unsigned short int *)&vm->mem[ptr + 1];
	// printf("test = %hx\n", *test);
	(void)vm;
}

void		my_print_args(t_arg args[MAX_ARGS_NUMBER], unsigned int arg_number)
{
	unsigned int	i;

	i = 0;
	// printf("coucou\n");
	while (i < arg_number)
	{
		ft_printf("arg[%d] data %lld (0x%llx)", i, args[i].data, (unsigned long long int)args[i].data);
			if ((unsigned int)args[i].type == NULL_CODE)
				ft_printf(" type null ");
			if ((unsigned int)args[i].type == REG_CODE)
				ft_printf(" type reg ");
			else if ((unsigned int)args[i].type == DIR_CODE)
				ft_printf(" type dir ");
			else
				ft_printf(" type ind ");
		ft_printf("value %lld (0x%llx)\n", args[i].value, (unsigned long long int)args[i].value);
		++i;
	}	
}

void		print_args(t_arg args[MAX_ARGS_NUMBER], unsigned int arg_number, unsigned char long_inst)
{
	unsigned int	i;

	i = 0;
	// printf("coucou\n");
	while (i < arg_number)
	{
		// printf("args_type  = %d\n", args[i].type);
			if ((unsigned int)args[i].type == NULL_CODE)
				ft_printf("NULL");
			if ((unsigned int)args[i].type == T_REG)
				ft_printf("r%lld", args[i].data);
			else if ((unsigned int)args[i].type == T_IND && long_inst)
			{
				ft_printf("%hd", (short int)args[i].value);
			}
			else if ((unsigned int)args[i].type == T_IND)
				ft_printf("%d", (int)args[i].value);
			else if (args[i].size == 2)
				ft_printf("%hd", (short int)args[i].value);
			else
				ft_printf("%hd", (short int)args[i].value);
		++i;
			if (i < arg_number)
				ft_printf(" ");
	}
	// printf("end\n");
}

void		write_var(unsigned char *mem, unsigned char *var, lint beg, size_t len)
{
	size_t	cpt;			

	cpt = 0;
	if (beg < 0)
		beg += MEM_SIZE;
	printf("BEG == %lld\n", beg);
	if (beg + len >= MEM_SIZE)
	{
		while (beg + cpt < MEM_SIZE)
		{
			mem[beg + cpt] = var[len - cpt - 1];
			++cpt;
		}
		beg = -cpt;
	}
	while (cpt < len)
	{
		mem[beg + cpt] = var[len - cpt - 1];
		++cpt;
	}
}

void		instruction_manager(t_vm *vm, t_proc *proc)
{
	extern t_op		op_tab[INSTR_NUMBER + 1];
	unsigned char	inst;
	t_arg			args[MAX_ARGS_NUMBER] = {{DIR_CODE  ,0,0,0}};

	// return ;
	if ((inst = vm->mem[proc->pc] - 1) > INSTR_NUMBER)
		return ;
	// printf("total is %u\n", vm->max_arg_size[inst][MAX_ARGS_NUMBER]);
	// printf("instruction is %s\n", op_tab[inst].name);
	// ft_bzero(args, sizeof(t_arg) * MAX_ARGS_NUMBER);
	if (!get_args(vm, proc, args, op_tab + inst))
	{
	// 	printf("ERREUR\n");
	// exit(1);
		return ;
	}
	// print_vm(vm);
	op_tab[inst].f(vm, proc, args);
	exit(1);
	// proc->pc = (proc->pc + vm->max_arg_size[inst][MAX_ARGS_NUMBER]) % MEM_SIZE;
	(void)vm;
	(void)proc;
}

void		exec_procs(t_vm *vm)
{
	t_list	*tmp;
	t_proc	*p;
	
	tmp = vm->plst;
	// printf("ici\n");
	while (tmp)
	{
		p = (t_proc *)tmp->content;
		// printf("p->cycle_to_wait == %d\n", p->cycle_to_wait);
		if (p->cycle_to_wait == 0)
		{
			instruction_manager(vm, p);
			// p->pc += 7;
			// instruction_manager(vm, p);
			// exit (1);
			get_proc_cycle(p, vm->mem);
		}
		else
			--p->cycle_to_wait;
		tmp = tmp->next;
		// printf("loop\n");
	}
}

void	main_loop(t_vm *vm)
{
	// if (vm->opt.d != -1)
	// {
	// 	while (vm->plst && vm->opt.d != vm->total_cycle)
	// 	{
	// 		exec_procs(vm);
	// 		checks_and_destroy(vm);
	// 	}
	// 	print_vm(vm);
	// 	return ;
	// }
	while (vm->plst)
	{
		// printf("la\n");
		if (vm->opt.d == vm->total_cycle)
		{
			print_vm(vm);
			exit(1);
		}
		if (vm->opt.s && vm->total_cycle % vm->opt.s == 0)
			print_vm(vm);
		if (ISACTIV(vm->opt.v, 1))
			ft_printf("It is now cycle %lld\n", vm->total_cycle);
		exec_procs(vm);
		// printf("pas la\n");
		checks_and_destroy(vm);
	}
	ft_printf("Constestant %u, \"%s\", has won !\n", vm->last_live + 1, vm->c[vm->last_live].header.prog_name);
}

void	introducing_contestants(t_champion *c)
{
	int		i;

	i = -1;
	ft_putstr("Introducing contestants...\n");
	while (++i < MAX_PLAYERS)
	{
		if (ft_memisset(&c[i], sizeof(t_champion), 0))
			continue ;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n", c[i].num, c[i].header.prog_size, c[i].header.prog_name, c[i].header.comment);
	}
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	if (argc == 1)
		ft_error_exit("Error: not enough args\n");
	--argc;
	++argv;
	vm_init(&vm, argc, argv);
	introducing_contestants(vm.c);
	main_loop(&vm);
	return (0);
}