/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:03:16 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 22:03:17 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		my_aff(t_vm *vm, t_proc *proc, t_arg *args)
{
	extern t_op			g_op_tab[INSTR_NUMBER + 1];

	if (vm->opt.a & 0b1)
	{
		ft_putchar((unsigned int)args[0].value % 256);
		if (!vm->opt.g && ISACTIV(vm->opt.v, 2))
		{
			ft_printf("Aff %c\n", args[0].value);
		}
	}
	moove_pc(vm, proc, args[0].size + 2);
}
