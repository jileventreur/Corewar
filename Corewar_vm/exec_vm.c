#include "corewar.h"

void	get_proc_cycle(t_proc *proc, unsigned char *mem)
{
	unsigned char	c;
	extern t_op		op_tab[INSTR_NUMBER + 1];

	c = mem[proc->pc] - 1;
	if (c > 16)
	{
		proc->cycle_to_wait = 1;
	}
	else
	{
		proc->cycle_to_wait = op_tab[c].cycle;
	}
	proc->inst = c;
}

void		instruction_manager(t_vm *vm, t_proc *proc)
{
	extern t_op		op_tab[INSTR_NUMBER + 1];
	t_arg			args[MAX_ARGS_NUMBER] = {{DIR_CODE  ,0,0,0}};

	if ((proc->inst) > INSTR_NUMBER)
	{
		++proc->pc;
		return ;
	}
	if (!get_args(vm, proc, args, op_tab + proc->inst))
	{
		return ;
	}
	op_tab[proc->inst].f(vm, proc, args);
}

void		exec_procs(t_vm *vm)
{
	t_list	*tmp;
	t_proc	*p;

	tmp = vm->plst;
	while (tmp)
	{
		p = (t_proc *)tmp->content;
		if (--p->cycle_to_wait <= 0)
		{
			instruction_manager(vm, p);
			get_proc_cycle(p, vm->mem);
		}
		tmp = tmp->next;
	}
}

void	exec_vm(t_vm *vm)
{
	while (vm->plst)
	{
		if (ISACTIV(vm->opt.v, 1))
			printf("It is now cycle %lld\n", vm->total_cycle);
		exec_procs(vm);
		checks_and_destroy(vm);
		if (vm->opt.d == vm->total_cycle)
		{
			nprint_procs(vm);
			exit(1);
		}

		if (vm->opt.s && vm->total_cycle % vm->opt.s == 0)
			nprint_procs(vm);
		if (vm->total_cycle % 100 == 0)
		{
			nprint_procs(vm);
		}
		usleep(5000);
		++vm->total_cycle;
	}
	printf("Contestant %u, \"%s\", has won !\n", -vm->last_live, vm->c[-vm->last_live - 1].header.prog_name);
}
