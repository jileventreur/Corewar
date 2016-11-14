#include "corewar.h"

void		my_live(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	proc->life ^= 0b1;
	vm->live_num += 1;
	// print_args(args, 1);
	if (args[0].value < MAX_PLAYERS &&
	!ft_memisset(&vm->c[args[0].value], sizeof(t_champion), 0))
		vm->last_live = args[0].value;
	proc->pc += args[0].size + 1;
	printf("LIVVVVVVE %lld\n", args[0].value);
	if (ISACTIV(vm->opt.v, 0) && args[0].value < MAX_PLAYERS && vm->c[args[0].value - 1].header.prog_size)
		ft_printf("Player %d (%d) is said to be alive\n", proc->num);
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
	// printf("-> store to %lld\n", i);
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