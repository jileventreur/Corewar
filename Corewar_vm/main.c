#include "corewar.h"

void	ft_error_exit(const char *exit_message)
{
	ft_puterror(exit_message);
	exit(1);
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
	printf("test = %hx\n", *test);
	(void)vm;
}

void		print_args(t_arg args[MAX_ARGS_NUMBER], unsigned int arg_number)
{
	unsigned int	i;

	i = 0;
	while (i < arg_number)
	{
		printf("arg[%d] data %lld (0x%llx)", i, args[i].data, (unsigned long long int)args[i].data);
			if ((unsigned int)args[i].type == NULL_CODE)
				printf(" type null ");
			if ((unsigned int)args[i].type == REG_CODE)
				printf(" type reg ");
			else if ((unsigned int)args[i].type == DIR_CODE)
				printf(" type dir ");
			else
				printf(" type ind ");
		printf("value %lld (0x%llx)\n", args[i].value, (unsigned long long int)args[i].value);
		++i;
	}
}

void		write_var(unsigned char *mem, unsigned char *var, lint beg, size_t len)
{
	size_t	cpt;			

	cpt = 0;
	if (beg < 0)
		beg += MEM_SIZE;
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

void		live(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	(void)vm;
	(void)proc;
	(void)args;
}

void		sti(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];
	lint				i;
	// printf("WELCOME IN LIVE\n");
	// while (i < 4)
	// {
	// 	printf("args_type[%d] = %d\n", i, args_type[i]);
	// 	++i;
	// }
	// printf("ptr = %x\n", vm->mem[ptr]);
	// test = (unsigned short int *)&vm->mem[ptr + 1];
	// printf("test = %x\n", (signed)get_arg(vm->mem, ptr, 2));
	// printf("name %s\n", op_tab[STI].name);
	(void)vm;

	print_args(args, 3);
	*(int *)proc->reg[0]= 0x00abcdef;
	// print_memory(vm->mem, MEM_SIZE);
	args[1].data = (short int)args[1].data;
	args[2].data = (short int)args[2].data;
	printf("sti r%s %lld (0x%llx) + %lld (0x%llx)\n", ft_itoa(args[0].data), args[1].value,
	args[1].value, args[2].value, args[2].value);
	i = (proc->pc + ((args[1].value + args[2].value) % IDX_MOD)) % MEM_SIZE;
	// printf("I == %lld\n", i);
	write_var(vm->mem, (unsigned char *)proc->reg[args[0].value - 1], i, REG_SIZE); 
	printf("-> store to %lld\n", i);
	// printf("\n");
	// print_memory(vm->mem, MEM_SIZE);
	(void)vm;
	(void)proc;
	(void)args;
	exit (1);
}

void		instruction_manager(t_vm *vm, t_proc *proc)
{
	extern t_op		op_tab[INSTR_NUMBER + 1];
	unsigned char	inst;
	t_arg			args[MAX_ARGS_NUMBER];

	if ((inst = vm->mem[proc->pc] - 1) > INSTR_NUMBER)
		return ;
	// printf("total is %u\n", vm->max_arg_size[inst][MAX_ARGS_NUMBER]);
	// printf("instruction is %s\n", op_tab[inst].name);
	if (!get_args(vm, proc, args, op_tab + inst))
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
	// print_memory(vm.mem, MEM_SIZE);
	main_loop(&vm);
	// lst = lst->next;
	// printf("la case contient: [%x]\n", mem[((t_proc *)lst->content)->pc]);
	return (0);
}