/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_and_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilano <jilano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:03:16 by cadam             #+#    #+#             */
/*   Updated: 2017/02/07 05:18:11 by jilano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	write_var(t_vm *vm, t_proc *proc, unsigned char *var, int beg)
{
	size_t	cpt;

	cpt = 0;
	if (beg < 0)
		beg += MEM_SIZE;
	if (beg + REG_SIZE >= MEM_SIZE)
	{
		while (beg + cpt < MEM_SIZE)
		{
			vm->mem[beg + cpt] = var[REG_SIZE - cpt - 1];
			vm->proc_mem[beg + cpt] = proc->player_num;
			++cpt;
		}
		beg = -cpt;
	}
	while (cpt < REG_SIZE)
	{
		vm->mem[beg + cpt] = var[REG_SIZE - cpt - 1];
		vm->proc_mem[beg + cpt] = proc->player_num;
		++cpt;
	}
}

void		my_sti(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];
	int					dest;

	args[2].data = (short int)args[2].data;
	dest = (proc->pc + ((args[1].value + args[2].value) % IDX_MOD)) % MEM_SIZE;
	write_var(vm, proc, (unsigned char *)&args[0].value, dest);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | sti ", proc->proc_num);
		print_args(args, g_op_tab[STI].param_number,
		g_op_tab[STI].long_inst, 0);
		ft_printf("\n");
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		args[1].value, args[2].value, args[1].value + args[2].value, dest);
	}
	moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 2);
}

void		my_st(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op	g_op_tab[INSTR_NUMBER + 1];
	int			dest;

	dest = (proc->pc + ((short int)(args[1].data) % IDX_MOD)) % MEM_SIZE;
	if (args[1].type == T_REG)
		REG(args[1].data) = args[0].data;
	else
		write_var(vm, proc, (unsigned char *)&args[0].value,
		dest);
	if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
	{
		ft_printf("P%5d | st r%d %d", proc->proc_num,
		args[0].data, (short int)args[1].data);
		ft_printf("\n");
	}
	moove_pc(vm, proc, args[0].size + args[1].size + 2);
}
