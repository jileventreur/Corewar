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
	// char	color[10];

	i = 0;
	// ft_strcpy(color, "\033[31m");
	// printf("COLOR == %c\n", color[3]);
	while (i < MEM_SIZE)
	{
		c = vm->mem[i];
		// printf("COLOR == %c\n", color[3]);
		// color[3] = '0' + 0b11 & vm->proc_mem[i];
		// printf("COLOR == %c\n", color[3]);
		// printf("c == %d\n", c);
		// printf("%s%2.2x%c%c\033[0m", vm->proc_mem[i] == 0 ? "" : color, c,
		// (i + 1) % 2 == 0 ? ' ' : 0, ((i + 1) % BYTE_LINE_NB) == 0 || i == (MEM_SIZE - 1) ? '\n' : 0);
		++i;
	}
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

void		my_live(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	proc->life ^= 0b1;
	vm->live_num += 1;
	print_args(args, 1);
	if (args[0].value < MAX_PLAYERS &&
	!ft_memisset(&vm->c[args[0].value], sizeof(t_champion), 0))
		vm->last_live = args[0].value;
	proc->pc += args[0].size + 1;
	printf("proc %d is still alive\n", proc->num);
	(void)vm;(void)proc;(void)args;
}

void		my_add(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	REG(args[2].data) = args[0].value + args[1].value;
	proc->carry ^= 0b1;
	proc->pc += args[0].size + args[1].size + args[2].size + 2;
	(void)vm;(void)proc;(void)args;
}

void		my_sub(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	REG(args[2].data) = args[0].value + args[1].value;
	proc->carry ^= 0b1;
	proc->pc += args[0].size + args[1].size + args[2].size + 2;
	(void)vm;(void)proc;(void)args;
}

void		my_or(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	REG(args[2].data) = args[0].value | args[1].value;
	proc->carry ^= 0b1;
	proc->pc += args[0].size + args[1].size + args[2].size + 2;
	(void)vm;(void)proc;(void)args;
}

void		my_and(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	REG(args[2].data) = args[0].value & args[1].value;
	proc->carry ^= 0b1;
	proc->pc += args[0].size + args[1].size + args[2].size + 2;
	(void)vm;(void)proc;(void)args;
}

void		my_xor(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	REG(args[2].data) = args[0].value ^ args[1].value;
	proc->carry ^= 0b1;
	proc->pc += args[0].size + args[1].size + args[2].size + 2;
	(void)vm;(void)proc;(void)args;
}

void		my_zjmp(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	if (proc->carry & 0b1)
		proc->pc = (proc->pc + args[0].value) % MEM_SIZE;
	if (proc->pc < 0)
		proc->pc += MEM_SIZE;
	// proc->carry ^= 0b1;
	(void)vm;(void)proc;(void)args;
}

void		my_aff(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	ft_putchar((unsigned int)args[0].value % 256);
	proc->pc += args[0].size + 2;
	(void)vm;(void)proc;(void)args;
}

void		my_lld(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	REG(args[1].value) = args[0].value;
	proc->carry ^= 0b1;
	proc->pc += args[0].size + args[1].size + 2; 
	(void)vm;(void)proc;(void)args;
} // same as ld, diff is in get_arg with long_inst

void		my_ld(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	REG(args[1].value) = args[0].value;
	proc->carry ^= 0b1;
	proc->pc += args[0].size + args[1].size + 2;
	(void)vm;(void)proc;(void)args;
}

void		my_lfork(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	t_list	*new;

	new = ft_lstnew(proc, sizeof(t_proc));
	((t_proc *)new->content)->pc = (((t_proc *)new->content)->pc +
	(args[1].value)) % MEM_SIZE;
	ft_lstadd(&vm->plst, new);
	proc->pc += args[0].size + 1;
	(void)vm;(void)proc;(void)args;
}

void		my_fork(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	t_list	*new;

	new = ft_lstnew(proc, sizeof(t_proc));
	((t_proc *)new->content)->pc = (((t_proc *)new->content)->pc +
	(args[1].value % IDX_MOD)) % MEM_SIZE;
	ft_lstadd(&vm->plst, new);
	proc->pc += args[0].size + 1;
	(void)vm;(void)proc;(void)args;
}

void		my_sti(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];
	lint				i;

	args[2].data = (short int)args[2].data;
	i = (proc->pc + ((args[1].value + args[2].value) % IDX_MOD)) % MEM_SIZE;
	write_var(vm->mem, (unsigned char *)proc->reg[args[0].value - 1], i, REG_SIZE); 
	printf("-> store to %lld\n", i);
	proc->pc += args[0].size + args[1].size + args[2].size + 2; 
	(void)vm;(void)proc;(void)args;
}

// void		write_var(unsigned char *mem, unsigned char *var, lint beg, size_t len)
void		my_st(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	if (args[1].type == REG_CODE)
		REG(args[1].data) = args[0].value;
	else
		write_var(vm->mem, (unsigned char *)&args[0].value,
		proc->pc + ((args[1].value) % IDX_MOD), args[0].size);
	proc->pc += args[0].size + args[1].size + 2;
	(void)vm;(void)proc;(void)args;
}

void	 	my_lldi(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	REG(args[2].data) = get_arg_data(vm->mem,
	proc->pc + ((args[0].value + args[1].value)), REG_SIZE); // same as ldi without idx_mod
	proc->pc += args[0].size + args[1].size + args[2].size + 2;
	(void)vm;(void)proc;(void)args;
}
void		my_ldi(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	REG(args[2].data) = get_arg_data(vm->mem,
	proc->pc + ((args[0].value + args[1].value) % IDX_MOD), REG_SIZE);
	proc->pc += args[0].size + args[1].size + args[2].size + 2;
	(void)vm;(void)proc;(void)args;
}

void		instruction_manager(t_vm *vm, t_proc *proc)
{
	extern t_op		op_tab[INSTR_NUMBER + 1];
	unsigned char	inst;
	t_arg			args[MAX_ARGS_NUMBER];

	// printf("COUCOUC\n");
	// return ;
	if ((inst = vm->mem[proc->pc] - 1) > INSTR_NUMBER)
		return ;
	// printf("total is %u\n", vm->max_arg_size[inst][MAX_ARGS_NUMBER]);
	// printf("instruction is %s\n", op_tab[inst].name);
	ft_bzero(args, sizeof(t_arg) * MAX_ARGS_NUMBER);
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
	while (vm->plst)
	{
		// printf("la\n");
		exec_procs(vm);
		// printf("pas la\n");
		checks_and_destroy(vm);
	}
	printf("cycle %lld : Game is over, player number %d have win\n",vm->total_cycle,
	vm->last_live + 1);
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
	// printf("COUCOU toi\n");
	vm_init(&vm, argc, argv);
	// printf("DEAD\n");
	// get_champion(argv[1], &c);
	// print_champions(vm.c);
	// printf("\n");
	// print_procs(vm.plst);
	print_memory(vm.mem, MEM_SIZE);
	// printf("\n\n");
	main_loop(&vm);
	// lst = lst->next;
	ft_printf("------------ END ------------\n");
	// printf("la case contient: [%x]\n", mem[((t_proc *)lst->content)->pc]);
	return (0);
}