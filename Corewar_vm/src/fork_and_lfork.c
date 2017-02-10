/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_lfork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilano <jilano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:03:16 by cadam             #+#    #+#             */
/*   Updated: 2017/02/07 06:16:14 by jilano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		my_lfork(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op		g_op_tab[INSTR_NUMBER + 1];
	t_list			*new;
	int				new_pc;

	new = ft_lstnew(proc, sizeof(t_proc));
	new_pc = (((t_proc *)new->content)->pc + (args[0].value)) % MEM_SIZE;
	if (new_pc < 0)
		new_pc += MEM_SIZE;
	((t_proc *)new->content)->pc = new_pc;
	((t_proc *)new->content)->proc_num = ++vm->list_len;
	++vm->c[((t_proc *)new->content)->player_num - 1].procs;
	ft_lstadd(&vm->plst, new);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | lfork ", proc->proc_num);
		print_args(args, g_op_tab[LFORK].param_number,
		g_op_tab[LFORK].long_inst, MAX_ARGS_NUMBER);
		ft_printf(" (%d)\n", ((t_proc *)new->content)->pc);
	}
	moove_pc(vm, proc, args[0].size + 1);
}

void		my_fork(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op		g_op_tab[INSTR_NUMBER + 1];
	t_list			*new;
	int				new_pc;

	args[0].value = (short int)args[0].value;
	new = ft_lstnew(proc, sizeof(t_proc));
	new_pc = (((t_proc *)new->content)->pc
	+ (args[0].value % IDX_MOD)) % MEM_SIZE;
	if (new_pc < 0)
		new_pc += MEM_SIZE;
	((t_proc *)new->content)->pc = new_pc;
	((t_proc *)new->content)->proc_num = ++vm->list_len;
	++vm->c[((t_proc *)new->content)->player_num - 1].procs;
	ft_lstadd(&vm->plst, new);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | fork ", proc->proc_num);
		print_args(args, g_op_tab[FORK].param_number,
		g_op_tab[FORK].long_inst, MAX_ARGS_NUMBER);
		ft_printf(" (%d)\n", ((t_proc *)new->content)->pc);
	}
	moove_pc(vm, proc, args[0].size + 1);
}
