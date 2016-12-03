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

	// return ;
	if ((proc->inst) > INSTR_NUMBER)
	{
		++proc->pc;
		// printf("BAD INSTR\n");
		// exit(1);
		return ;
	}
	// printf("total is %u\n", vm->max_arg_size[inst][MAX_ARGS_NUMBER]);
	// printf("instruction is %s\n", op_tab[inst].name);
	// ft_bzero(args, sizeof(t_arg) * MAX_ARGS_NUMBER);
	if (!get_args(vm, proc, args, op_tab + proc->inst))
	{
		return ;
	}
	op_tab[proc->inst].f(vm, proc, args);
	// print_vm(vm);
	// exit(1);
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
	int i = 0;
	while (tmp)
	{
		// printf("p->cycle_to_wait == %d\n", p->cycle_to_wait);
		p = (t_proc *)tmp->content;
		if (--p->cycle_to_wait <= 0)
		{
			instruction_manager(vm, p);
			get_proc_cycle(p, vm->mem);
			// print_procs(vm, vm->plst, 0);
		}
		tmp = tmp->next;
		// if (i == 1)
		// {
		// 	print_procs(vm, vm->plst, 0);
		// 	exit(1);
		// }
		++i;
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
			// print_procs(vm, vm->plst, 0);
			print_vm(vm);
			// print_procs(vm, vm->plst, 0);
			exit(1);
		}
		if (vm->opt.s && vm->total_cycle % vm->opt.s == 0)
			print_vm(vm);
		++vm->total_cycle;
	}
	printf("Contestant %u, \"%s\", has won !\n", -vm->last_live, vm->c[-vm->last_live - 1].header.prog_name);
}
