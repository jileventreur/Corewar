/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_instructions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:14:43 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 22:14:44 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		my_add(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	REG(args[2].data) = args[0].value + args[1].value;
	proc->carry = !REG(args[2].data);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | add r%d r%d r%d", proc->proc_num,
		args[0].data, args[1].data, args[2].data);
		ft_printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
}

void		my_sub(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	REG(args[2].data) = args[0].value - args[1].value;
	proc->carry = !REG(args[2].data);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | sub r%d r%d r%d", proc->proc_num,
		args[0].data, args[1].data, args[2].data);
		ft_printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
}

void		my_or(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	REG(args[2].data) = args[0].value | args[1].value;
	proc->carry = !REG(args[2].data);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | or ", proc->proc_num);
		print_args(args, g_op_tab[OR].param_number, g_op_tab[OR].long_inst, 2);
		ft_printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
}

void		my_xor(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	REG(args[2].data) = args[0].value ^ args[1].value;
	proc->carry = !REG(args[2].data);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | xor ", proc->proc_num);
		print_args(args, g_op_tab[XOR].param_number,
		g_op_tab[XOR].long_inst, 2);
		ft_printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
}

void		my_and(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	REG(args[2].data) = args[0].value & args[1].value;
	proc->carry = !REG(args[2].data);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | and ", proc->proc_num);
		print_args(args, g_op_tab[AND].param_number,
		g_op_tab[AND].long_inst, 2);
		ft_printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
}
