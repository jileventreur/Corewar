/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_pc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:03:16 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 22:03:17 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		moove_pc(t_vm *vm, t_proc *proc, unsigned int value)
{
	unsigned int i;

	if (!vm->opt.g && ISACTIV(vm->opt.v, 4))
	{
		i = 0;
		ft_printf("ADV %u (0x%.4x -> 0x%.4x) ", value, proc->pc,
		proc->pc + value);
		while (i < value)
		{
			ft_printf("%.2x ", vm->mem[proc->pc + i]);
			++i;
		}
		ft_printf("\n");
	}
	DESACTIV_BIT(vm->proc_mem[proc->pc], PC_BIT);
	proc->pc = (proc->pc + value) % MEM_SIZE;
	ACTIV_BIT(vm->proc_mem[proc->pc], PC_BIT);
}
