#include "corewar.h"

void		moove_pc(t_vm *vm, t_proc *proc, unsigned int value)
{
	unsigned int i;

	if (ISACTIV(vm->opt.v, 4))
	{
		i = 0;
		printf("ADV %u (0x%.4x -> 0x%.4x) ", value, proc->pc, proc->pc + value);
		while (i < value)
		{
			printf("%.2x ", vm->mem[proc->pc + i]);
			++i;
		}
		printf("\n");
	}
	proc->pc += value;
}

void		my_live(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	proc->life |= 0b1;
	proc->last_live = vm->total_cycle;
	++vm->live_num;
	if (args[0].value < 0
	&& args[0].value >= -MAX_PLAYERS
	&& !ft_memisset(&vm->c[-args[0].value -1], sizeof(t_champion), 0))
	{
		// printf("jsuis passe la\n");
		vm->last_live = args[0].value;
	}
	// proc->pc += args[0].size + 1;
	// printf("LIVVVVVVE %lld\n", args[0].value);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | live ", proc->proc_num);
		print_args(args, op_tab[LIVE].param_number, op_tab[LIVE].long_inst, MAX_ARGS_NUMBER);
		printf("\n");
	}
	if (ISACTIV(vm->opt.v, 0)
	&& args[0].value < 0
	&& args[0].value >= -MAX_PLAYERS
	&& vm->c[-args[0].value - 1].header.prog_size) // voir pour le player -1
		printf("Player %d (%s) is said to be alive\n", proc->player_num, 
		vm->c[-args[0].value - 1].header.prog_name);
	moove_pc(vm, proc, args[0].size + 1);
	// exit(1);
	(void)vm;(void)proc;(void)args;
}

void		my_add(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	REG(args[2].data) = args[0].value + args[1].value;
	// proc->carry ^= 0b1;
	proc->carry = !REG(args[2].data);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | add r%d r%d r%d", proc->proc_num,
		args[0].data, args[1].data, args[2].data);
		printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
	(void)vm;(void)proc;(void)args;
}

void		my_sub(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	REG(args[2].data) = args[0].value + args[1].value;
	// proc->carry ^= 0b1;
	proc->carry = !REG(args[2].data);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | sub r%d r%d r%d", proc->proc_num,
		args[0].data, args[1].data, args[2].data);
		printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
	(void)vm;(void)proc;(void)args;
}

void		my_or(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	REG(args[2].data) = args[0].value | args[1].value;
	// proc->carry ^= 0b1;
	proc->carry = !REG(args[2].data);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | or ", proc->proc_num);
		print_args(args, op_tab[OR].param_number, op_tab[OR].long_inst, 2);
		printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
	// exit(1);
	(void)vm;(void)proc;(void)args;
}

void		my_xor(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	REG(args[2].data) = args[0].value ^ args[1].value;
	proc->carry = !REG(args[2].data);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | xor ", proc->proc_num);
		print_args(args, op_tab[XOR].param_number, op_tab[XOR].long_inst, 2);
		printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
	(void)vm;(void)proc;(void)args;
}

void		my_and(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	REG(args[2].data) = args[0].value & args[1].value;
	// proc->carry ^= 0b1;
	proc->carry = !REG(args[2].data);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | and ", proc->proc_num);
		print_args(args, op_tab[AND].param_number, op_tab[AND].long_inst, 2);
		printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
	(void)vm;(void)proc;(void)args;
}

void		my_lld(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	// // printf("mon test %hd %hx\n", ()(unsigned short int)53248);
	// printf("%x\n", (unsigned int)-805306110);
	REG(args[1].data) = args[0].value;
	proc->carry = !REG(args[1].data);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | lld ", proc->proc_num);
		print_args(args, op_tab[LLD].param_number, op_tab[LLD].long_inst, 1);
		printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + 2);
	(void)vm;(void)proc;(void)args;
} // same as ld, diff is in get_arg with long_inst

void		my_ld(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	REG(args[1].data) = args[0].value;
	// proc->carry ^= 0b1;
	proc->carry = !REG(args[1].data);
	// printf("carry = %d\n", proc->carry);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | ld ", proc->proc_num);
		print_args(args, op_tab[LD].param_number, op_tab[LD].long_inst, 1);
		printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + 2);
	(void)vm;(void)proc;(void)args;
}

void		my_zjmp(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | zjmp ", proc->proc_num);
		print_args(args, op_tab[ZJMP].param_number, op_tab[ZJMP].long_inst, MAX_ARGS_NUMBER);
		printf(" %s\n", (proc->carry & 0b1) ? "OK" : "FAILED");
	}
	if (proc->carry & 0b1)
	{
		proc->pc = (proc->pc + args[0].value) % MEM_SIZE;
		if (proc->pc < 0)
			proc->pc += MEM_SIZE;
	}
	else
		moove_pc(vm, proc, args[0].size + 1);
	(void)vm;(void)proc;(void)args;
}

void		my_aff(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	if (vm->opt.a & 0b1)
	{
		ft_putchar((unsigned int)args[0].value % 256);
		if (ISACTIV(vm->opt.v, 2))
		{
			printf("Aff %c\n", args[0].value);
		}
	}
	moove_pc(vm, proc, args[0].size + 2);
	(void)vm;(void)proc;(void)args;
}

void		my_lfork(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op		op_tab[INSTR_NUMBER + 1];
	t_list			*new;
	int				new_pc;

	new = ft_lstnew(proc, sizeof(t_proc));
	new_pc = (((t_proc *)new->content)->pc + (args[0].value)) % MEM_SIZE;
	if (new_pc < 0)
		new_pc += MEM_SIZE;
	((t_proc *)new->content)->pc = new_pc;
	vm->list_len += 1;
	((t_proc *)new->content)->proc_num = vm->list_len;
	get_proc_cycle(new->content, vm->mem);
	ft_lstadd(&vm->plst, new);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | lfork ", proc->proc_num);
		print_args(args, op_tab[LFORK].param_number, op_tab[LFORK].long_inst, MAX_ARGS_NUMBER);
		printf(" (%d)\n", ((t_proc *)new->content)->pc);
	}
	moove_pc(vm, proc, args[0].size + 1);
	(void)vm;(void)proc;(void)args;
}

void		my_fork(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op		op_tab[INSTR_NUMBER + 1];
	t_list			*new;
	int				new_pc;

	args[0].value = (short int)args[0].value;
	// if (args[0].value < 0)
	// {
	// 	printf("value == %d\n", args[0].value);
	// 	args[0].value += MEM_SIZE;
	// 	printf("value == %d\n", args[0].value);
	// 	exit(1);
	// }
	new = ft_lstnew(proc, sizeof(t_proc));
	new_pc = (((t_proc *)new->content)->pc + (args[0].value % IDX_MOD)) % MEM_SIZE;
	if (new_pc < 0)
		new_pc += MEM_SIZE;
	((t_proc *)new->content)->pc = new_pc;
	++vm->list_len;
	((t_proc *)new->content)->proc_num = vm->list_len;
	get_proc_cycle(new->content, vm->mem);
	ft_lstadd(&vm->plst, new);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | fork ", proc->proc_num);
		print_args(args, op_tab[FORK].param_number, op_tab[FORK].long_inst, MAX_ARGS_NUMBER);
		printf(" (%d)\n", ((t_proc *)new->content)->pc);
	}
	moove_pc(vm, proc, args[0].size + 1);
	// print_procs(vm, vm->plst, 0);
	// print_vm(vm);
	// exit(1);
	(void)vm;(void)proc;(void)args;
}

void		my_sti(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];
	lint				i;

	args[2].data = (short int)args[2].data;
	i = (proc->pc + ((args[1].value + args[2].value) % IDX_MOD)) % MEM_SIZE;
	// printf("value == %d\n", args[0].value);
	
	write_var(vm->mem, (unsigned char *)&args[0].value, i, REG_SIZE); 
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | sti ", proc->proc_num);
		print_args(args, op_tab[STI].param_number, op_tab[STI].long_inst, 0);
		printf("\n");
		printf("       | -> store to %d + %d = %d (with pc and mod %lld)\n", args[1].value, 
		args[2].value, args[1].value + args[2].value, i);
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
	(void)vm;(void)proc;(void)args;
}

// void		write_var(unsigned char *mem, unsigned char *var, lint beg, size_t len)
void		my_st(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	// printf("data = %x\n", args[1].data);
	// args[0].value = -1;
	// printf("size = %d\n", args[0].size);
	// printf("cible = %d\n", proc->pc + (((short int)args[1].data) % IDX_MOD));
	if (args[1].type == T_REG)
		REG(args[1].data) = args[0].data;
	else
		write_var(vm->mem, (unsigned char *)&args[0].value,
		proc->pc + ((short int)(args[1].data) % IDX_MOD), REG_SIZE);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | st r%d %d", proc->proc_num, args[0].data, (short int)args[1].data);
		// print_args(args, op_tab[ST].param_number, 1);
		printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + 2);
	// print_vm(vm);
	(void)vm;(void)proc;(void)args;
}

void	 	my_lldi(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	// print_vm(vm);
	// printf("test = %x\n", 58368);
	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | lldi ", proc->proc_num);
		print_args(args, op_tab[LLDI].param_number, op_tab[LLDI].long_inst, 2);
		printf("\n       | -> load from %d + %d = %d (with pc %d)\n", args[0].value, 
		args[1].value, args[0].value + args[1].value, proc->pc + ((args[0].value + args[1].value)));
	}
	REG(args[2].data) = get_arg_data(vm->mem,
	proc->pc + ((args[0].value + args[1].value)), REG_SIZE); // same as ldi without idx_mod
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
	(void)vm;(void)proc;(void)args;
}

void		my_ldi(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	if (ISACTIV(vm->opt.v, 2))
	{
		printf("P%5d | ldi ", proc->proc_num);
		print_args(args, op_tab[LDI].param_number, op_tab[LDI].long_inst, 2);
		printf("\n       | -> load from %d + %d = %d (with pc and mod %d)\n", args[0].value, 
		args[1].value, args[0].value + args[1].value, proc->pc + ((args[0].value + args[1].value) % IDX_MOD));
		// printf("args[0] == %d\n", args[0].value);
		// printf("args[0].size == %d\n", args[0].size);
	}
	REG(args[2].data) = get_arg_data(vm->mem,
	proc->pc + ((args[0].value + args[1].value) % IDX_MOD), REG_SIZE);
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
	// exit(1);
	(void)vm;(void)proc;(void)args;
}