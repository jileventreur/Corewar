/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:03:16 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 22:03:17 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		my_zjmp(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | zjmp ", proc->proc_num);
		print_args(args, g_op_tab[ZJMP].param_number,
		g_op_tab[ZJMP].long_inst, MAX_ARGS_NUMBER);
		ft_printf(" %s\n", (proc->carry & 0b1) ? "OK" : "FAILED");
	}
	if (proc->carry & 0b1)
	{
		proc->pc = (proc->pc + (args[0].value % IDX_MOD)) % MEM_SIZE;
		if (proc->pc < 0)
			proc->pc += MEM_SIZE;
	}
	else
		moove_pc(vm, proc, args[0].size + 1);
}
