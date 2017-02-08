/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_pc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilano <jilano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:03:16 by cadam             #+#    #+#             */
/*   Updated: 2017/02/07 03:53:26 by jilano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		moove_pc(t_vm *vm, t_proc *proc, unsigned int value)
{
	unsigned int i;

	// if (proc->proc_num == 13)
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
		// ft_printf("proc->pc = %x\n", vm->mem[(proc->pc + value) % MEM_SIZE]);
		// i = (proc->pc + value) % MEM_SIZE;
		// while (i % 64)
		// 	ft_printf("%.2x ", vm->mem[i++]);
	}
	DESACTIV_BIT(vm->proc_mem[proc->pc], PC_BIT);
	proc->pc = (proc->pc + value) % MEM_SIZE;
	ACTIV_BIT(vm->proc_mem[proc->pc], PC_BIT);
}
