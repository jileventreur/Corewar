#include "corewar.h"

void	get_proc_cycle(t_proc *proc, unsigned char *mem)
{
	unsigned char	c;
	extern t_op		op_tab[INSTR_NUMBER + 1];

	c = mem[proc->pc] - 1;
	if (c > 16)
	{
		// printf("%u (0x%x) n'est pas une instruction\n",c + 1,c + 1 );
		// exit(1);
		proc->cycle_to_wait = 1;
	}
	else
 	{
		proc->cycle_to_wait = op_tab[c].cycle;
 		// printf("ctw = %u\n", proc->cycle_to_wait);
		// printf("l'op code 0x%2.2x correspond a l'instruction %s\n", c, op_tab[c].name);
  	}
}

void		instruction_manager(t_vm *vm, t_proc *proc)
{
	extern t_op		op_tab[INSTR_NUMBER + 1];
	unsigned char	inst;
	t_arg			args[MAX_ARGS_NUMBER] = {{DIR_CODE  ,0,0,0}};

	// return ;
	if ((inst = vm->mem[proc->pc] - 1) > INSTR_NUMBER)
	{
		++proc->pc;
		// printf("BAD INSTR\n");
		// exit(1);
		return ;
	}
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
			// print_procs(vm, vm->plst, 0);
		}
		else
			--p->cycle_to_wait;
		tmp = tmp->next;
		// printf("loop\n");
	}
}

void	exec_vm(t_vm *vm)
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
	// print_vm(vm);
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
