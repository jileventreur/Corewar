/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilano <jilano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 20:52:38 by cadam             #+#    #+#             */
/*   Updated: 2017/02/07 06:34:12 by jilano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_arg_value(t_vm *vm, t_proc *proc, t_arg *args,
			unsigned char long_inst)
{
	if (args->type == NULL_CODE)
	{
		return (1);
	}
	else if (args->type == REG_CODE)
	{
		if ((unsigned)args->data - 1 > 15)
			return (0);
		args->value = REG(args->data);
	}
	else if (args->type == DIR_CODE)
		args->value = args->data;
	else
	{
		args->value = get_arg_data(vm->mem,
		long_inst ? ((short int)args->data + proc->pc) :
		((short int)args->data + proc->pc) % IDX_MOD, long_inst ? 2 : 4);
	}
	return (1);
}

t_lint		get_arg_data(unsigned char *mem, int beg, unsigned int len)
{
	t_lint			res;
	unsigned int	cpt;

	res = 0;
	cpt = 0;
	if (beg < 0)
		beg += MEM_SIZE;
	if (beg + len >= MEM_SIZE)
		while (cpt < len)
		{
			res <<= 8;
			res += mem[(beg + cpt) % MEM_SIZE];
			++cpt;
		}
	else
		while (cpt < len)
		{
			res <<= 8;
			res += mem[(beg + cpt)];
			++cpt;
		}
	return ((len == 2) ? (short int)res : (int)res);
}

static int	arg_size_init(t_arg *arg, unsigned int dir_adr)
{
	if (arg->type == T_REG)
		return (T_REG);
	if (arg->type == NULL_CODE)
		return (0);
	return ((arg->type == T_DIR) ? T_DIR + dir_adr : T_DIR);
}

static int	ocp_analyse(t_op *inst, unsigned char ocp, t_arg *args)
{
	unsigned char		cpt;
	int					ret;

	cpt = MAX_ARGS_NUMBER - 1;
	ret = 0;
	while (cpt > inst->param_number - 1)
	{
		ocp >>= 2;
		--cpt;
	}
	while (cpt < 42)
	{
		args[cpt].type = ocp & 0b11;
		if (!(inst->param_mask[cpt] & (1 << ((args[cpt].type) - 1))))
		{
			ret |= 0b1;
		}
		ocp >>= 2;
		--cpt;
	}
	return (ret);
}

int			get_args(t_vm *vm, t_proc *proc, t_arg *args, t_op *inst)
{
	int					ptr;
	unsigned int		i;
	unsigned int		dir_adr;
	unsigned char		valid_inst;

	valid_inst = !(inst->ocp & 0b1
	&& ocp_analyse(inst, vm->mem[(proc->pc + 1) % MEM_SIZE], args));
	i = 0;
	ptr = (proc->pc + 1 + inst->ocp) % MEM_SIZE;
	dir_adr = (inst->direct_adr == 0) * 2;
	while (i < inst->param_number)
	{
		args[i].size = arg_size_init(args + i, dir_adr);
		args[i].data = get_arg_data(vm->mem, ptr, args[i].size);
		valid_inst &= get_arg_value(vm, proc, args + i, inst->long_inst);
		ptr = (ptr + args[i++].size) % MEM_SIZE;
	}
	if (!valid_inst)
	{
		moove_pc(vm, proc,
		args[0].size + args[1].size + args[2].size + 1 + inst->ocp);
		return (0);
	}
	return (1);
}
