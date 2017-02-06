/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_and_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:03:16 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 22:03:17 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		my_sti(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];
	t_lint				i;

	args[2].data = (short int)args[2].data;
	i = (proc->pc + ((args[1].value + args[2].value) % IDX_MOD)) % MEM_SIZE;
	write_var(vm, proc, (unsigned char *)&args[0].value, i);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | sti ", proc->proc_num);
		print_args(args, g_op_tab[STI].param_number,
		g_op_tab[STI].long_inst, 0);
		ft_printf("\n");
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %lld)\n",
		args[1].value, args[2].value, args[1].value + args[2].value, i);
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
}

void		my_st(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	if (args[1].type == T_REG)
		REG(args[1].data) = args[0].data;
	else
		write_var(vm, proc, (unsigned char *)&args[0].value,
		proc->pc + ((short int)(args[1].data) % IDX_MOD));
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | st r%d %d", proc->proc_num,
		args[0].data, (short int)args[1].data);
		ft_printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + 2);
}
