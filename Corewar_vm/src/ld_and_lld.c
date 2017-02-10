/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_and_lld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:18:29 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 22:18:30 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		my_lld(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	REG(args[1].data) = args[0].value;
	proc->carry = !REG(args[1].data);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | lld ", proc->proc_num);
		print_args(args, g_op_tab[LLD].param_number,
		g_op_tab[LLD].long_inst, 1);
		ft_printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + 2);
}

void		my_ld(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	REG(args[1].data) = args[0].value;
	proc->carry = !REG(args[1].data);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | ld ", proc->proc_num);
		print_args(args, g_op_tab[LD].param_number,
		g_op_tab[LD].long_inst, 1);
		ft_printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + 2);
}
