#include "corewar.h"

void	ft_error_exit(const char *exit_message)
{
	ft_puterror(exit_message);
	exit(1);
}

void	get_proc_cycle(t_proc *proc, unsigned char *mem)
{
	unsigned char	c;
	extern t_op		op_tab[17];

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

int		ocp_analyse(t_op *inst_op, unsigned char ocp, unsigned char *args)
{
	// extern t_op		op_tab[17];
	unsigned char		cpt;

	cpt = MAX_ARGS_NUMBER - 1;

	while (cpt > inst_op->param_number - 1)
	{
		ocp >>= 2;
		--cpt;
	}
	// printf("ocp = %x\n", ocp);
	while (cpt < 42) // lol jsuis sur ca va marcher et jtrouve ca trop con
	{
		// if (inst_op->param_mask[cpt] & (1 << ((ocp & 0b11) - 1)))
		// {
		// 	printf("le param %d est %d\n", (int)cpt, (ocp & 0b11));
		// }
		// else
		// {
		// 	printf("le param %d est %d\n", (int)cpt, (ocp & 0b11));
			// args[cpt] = -1;
			// ft_error_exit("Error: BAD ARG BASTARD\n");
		// }
		if (!(args[cpt] = inst_op->param_mask[cpt] & (1 << ((ocp & 0b11) - 1))))
		{
			printf("ERROR WITH ARG %u\n", cpt);
			return (0);
		}
		ocp >>= 2;
		--cpt;
	}
	// printf("\n");
	// exit (0);
	return (1);
}

void		null_instr(t_vm *vm, t_proc *proc, unsigned char args_type[MAX_ARGS_NUMBER])
{
	int i = 0;
	int	ptr;
	unsigned short int *test;

	while (i < 4)
	{
		printf("args_type[%d] = %d\n", i, args_type[i]);
		++i;
	}
	ptr = (proc->pc + 2) % MEM_SIZE;
	test = (unsigned short int *)&vm->mem[ptr + 1];
	printf("test = %hx\n", *test);
	(void)vm;
}

long long unsigned int	get_arg(unsigned char *mem, unsigned int beg, unsigned int len)
{
	long long unsigned int	res;
	unsigned int			cpt;

	res = 0;
	cpt = 0;
	if (beg + len >= MEM_SIZE)
	{
		while (cpt < len)
		{
			res <<= 8;
			res += mem[(beg + cpt) % MEM_SIZE];
			++cpt;
		}
	}
	else
	{
		while (cpt < len)
		{
			res <<= 8;
			res += mem[(beg + cpt) % MEM_SIZE];
			++cpt;
		}
	}
	return (res);
}

void		sti(t_vm *vm, t_proc *proc, unsigned char args_type[MAX_ARGS_NUMBER])
{
	int i = 0;
	int	ptr;
	unsigned short int *test;
	extern t_op		op_tab[17];

	printf("WELCOME IN LIVE\n");
	while (i < 4)
	{
		printf("args_type[%d] = %d\n", i, args_type[i]);
		++i;
	}
	ptr = (proc->pc + 2) % MEM_SIZE;
	printf("ptr = %x\n", vm->mem[ptr]);
	test = (unsigned short int *)&vm->mem[ptr + 1];
	printf("test = %x\n", (signed)get_arg(vm->mem, ptr, 2));
	printf("name %s\n", op_tab[STI].name);
	(void)vm;
}

void		instruction_manager(t_vm *vm, t_proc *proc)
{
	unsigned char	inst;
	unsigned char	args[4];
	extern t_op		op_tab[17];


	if ((inst = vm->mem[proc->pc] - 1) > 16)
		return ;
	printf("total is %u\n", vm->max_arg_size[inst][MAX_ARGS_NUMBER]);
	printf("instruction is %s\n", op_tab[inst].name);
	if(!ocp_analyse(&op_tab[inst], vm->mem[(proc->pc + 1) % MEM_SIZE], args))
		return ;
	op_tab[inst].f(vm, proc, args);
	// proc->pc = (proc->pc + vm->max_arg_size[inst][MAX_ARGS_NUMBER]) % MEM_SIZE;
	(void)vm;
	(void)proc;
}

void		exec_procs(t_vm *vm)
{
	t_list	*tmp;
	t_proc	*p;
	
	tmp = vm->plst;
	while (tmp)
	{
		p = (t_proc *)tmp->content;
		if (p->cycle_to_wait == 0)
		{
			instruction_manager(vm, p);
			// p->pc += 7;
			// instruction_manager(vm, p);
			exit (1);
			get_proc_cycle(p, vm->mem);
		}
		else
			--p->cycle_to_wait;
		tmp = tmp->next;
	}
}

void	main_loop(t_vm *vm)
{
	while (vm->plst)
	{
		exec_procs(vm);
		checks_and_destroy(vm);
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
	// print_champions(vm.c);
	// printf("\n");
	// print_procs(vm.plst);
	print_memory(vm.mem, MEM_SIZE);
	main_loop(&vm);
	// lst = lst->next;
	// printf("la case contient: [%x]\n", mem[((t_proc *)lst->content)->pc]);
	return (0);
}