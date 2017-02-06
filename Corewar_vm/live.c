/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:35:10 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 22:35:11 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		my_live(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	proc->life |= 0b1;
	proc->last_live = vm->total_cycle;
	++vm->live_num;
	if (args[0].value < 0
	&& args[0].value >= -MAX_PLAYERS
	&& !ft_memisset(&vm->c[-args[0].value - 1], sizeof(t_champion), 0))
	{
		vm->last_live = args[0].value;
	}
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | live ", proc->proc_num);
		print_args(args, g_op_tab[LIVE].param_number,
		g_op_tab[LIVE].long_inst, MAX_ARGS_NUMBER);
		ft_printf("\n");
	}
	if (!vm->opt.g && ISACTIV(vm->opt.v, 0) && args[0].value < 0
	&& args[0].value >= -MAX_PLAYERS
	&& vm->c[-args[0].value - 1].header.prog_size)
		ft_printf("Player %d (%s) is said to be alive\n", proc->player_num,
		vm->c[-args[0].value - 1].header.prog_name);
	moove_pc(vm, proc, args[0].size + 1);
}
