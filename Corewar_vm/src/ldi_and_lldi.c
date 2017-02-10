/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_and_lldi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:03:16 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 22:03:17 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		my_lldi(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | lldi ", proc->proc_num);
		print_args(args, g_op_tab[LLDI].param_number,
		g_op_tab[LLDI].long_inst, 2);
		ft_printf("\n       | -> load from %d + %d = %d (with pc %d)\n",
		args[0].value, args[1].value, args[0].value + args[1].value,
		proc->pc + ((args[0].value + args[1].value)));
	}
	REG(args[2].data) = get_arg_data(vm->mem,
	proc->pc + ((args[0].value + args[1].value)), REG_SIZE);
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
}

void		my_ldi(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | ldi ", proc->proc_num);
		print_args(args, g_op_tab[LDI].param_number,
		g_op_tab[LDI].long_inst, 2);
		ft_printf("\n       | -> load from %d + %d = %d (with pc and mod %d)\n",
		args[0].value, args[1].value, args[0].value + args[1].value,
		proc->pc + ((args[0].value + args[1].value) % IDX_MOD));
	}
	REG(args[2].data) = get_arg_data(vm->mem,
	proc->pc + ((args[0].value + args[1].value) % IDX_MOD), REG_SIZE);
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
}
