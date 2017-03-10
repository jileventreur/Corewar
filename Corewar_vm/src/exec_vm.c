/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilano <jilano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:01:17 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/13 14:56:24 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_proc_cycle(t_proc *proc, unsigned char *mem)
{
	unsigned char	c;
	extern t_op		g_op_tab[INSTR_NUMBER + 1];

	c = mem[proc->pc] - 1;
	if (c > 16)
	{
		proc->cycle_to_wait = 1;
	}
	else
	{
		proc->cycle_to_wait = g_op_tab[c].cycle;
	}
	proc->inst = c;
}

void	instruction_manager(t_vm *vm, t_proc *proc)
{
	extern t_op		g_op_tab[INSTR_NUMBER + 1];
	t_arg			args[MAX_ARGS_NUMBER];

	ft_bzero(args, sizeof(t_arg) * MAX_ARGS_NUMBER);
	*args = (t_arg){DIR_CODE, 0, 0, 0};
	if ((proc->inst) > INSTR_NUMBER)
	{
		proc->pc = (proc->pc + 1) % MEM_SIZE;
		return ;
	}
	if (!get_args(vm, proc, args, g_op_tab + proc->inst))
	{
		return ;
	}
	g_op_tab[proc->inst].f(vm, proc, args);
}

void	exec_procs(t_vm *vm)
{
	t_list	*tmp;
	t_proc	*p;

	tmp = vm->plst;
	while (tmp)
	{
		p = (t_proc *)tmp->content;
		if (--p->cycle_to_wait <= 0)
			instruction_manager(vm, p);
		tmp = tmp->next;
	}
	tmp = vm->plst;
	while (tmp)
	{
		p = (t_proc *)tmp->content;
		if (p->cycle_to_wait <= 0)
			get_proc_cycle(p, vm->mem);
		tmp = tmp->next;
	}
}

void	dump_vm(t_vm *vm)
{
	unsigned int	i;
	unsigned char	c;

	endwin();
	i = 0;
	while (i < MEM_SIZE)
	{
		c = vm->mem[i];
		if (i % BYTE_LINE_NB == 0)
			ft_printf("0x%.4x : ", i);
		ft_printf("%2.2x ", c);
		if (((i + 1) % BYTE_LINE_NB) == 0 || i == (MEM_SIZE - 1))
			ft_printf("\n");
		++i;
	}
	exit(1);
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
		if (vm->opt.d == vm->total_cycle)
			dump_vm(vm);
		++vm->total_cycle;
		if (vm->opt.g)
			get_input_and_fsp(&ch, &refresh_speed);
		else if (ISACTIV(vm->opt.v, 1))
			ft_printf("It is now cycle %lld\n", vm->total_cycle);
		exec_procs(vm);
		checks_and_destroy(vm);
		if (vm->opt.g || vm->opt.s)
			print_all(vm, refresh_speed);
	}
	if (vm->opt.g)
		print_wait_end(vm);
	endwin();
	win = vm->c[-vm->last_live - 1].header.prog_name;
	ft_printf("Contestant %u, \"%s\" has won !\n", -vm->last_live, win);
}
