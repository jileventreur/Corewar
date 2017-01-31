/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:01:17 by nbelouni          #+#    #+#             */
/*   Updated: 2017/01/31 17:57:04 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		ch;
	int		refresh_speed;
	char	*win;

	ch = -1;
	refresh_speed = 5000;
	while (vm->plst)
	{
		if (vm->opt.g)
			get_input_and_fsp(&ch, &refresh_speed);
		if (ISACTIV(vm->opt.v, 1))
			printf("It is now cycle %lld\n", vm->total_cycle);
		exec_procs(vm);
		checks_and_destroy(vm);
		if (vm->opt.g)
			print_all(vm, refresh_speed);
		++vm->total_cycle;
	}
	endwin();
	win = vm->c[-vm->last_live - 1].header.prog_name;
	printf("Contestant %u, \"%s\", has won !\n", -vm->last_live, win);
}
