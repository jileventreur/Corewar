#include "corewar.h"

lint		get_arg_data(unsigned char mem[MEM_SIZE], int beg, unsigned int len)
{
	lint			res;
	unsigned int	cpt;

	res = 0;
	cpt = 0;
	if (beg < 0)
		beg += MEM_SIZE;
	if (beg + len >= MEM_SIZE)
	{
		while (cpt < len)
		{
			res <<= 8;
			res += mem[(beg + cpt) % MEM_SIZE];
			++cpt;
		}
	}
	else
	{
		while (cpt < len)
		{
			res <<= 8;
			res += mem[(beg + cpt)];
			++cpt;
		}
	}
	return ((len == 2) ? (short int)res : (int)res); // if (len != 2 -> len == 4 || len == 1) and len == 1 -> reg -> unsigned anyway
}

static int		get_arg_value(t_vm *vm, t_proc *proc, t_arg *args, unsigned char long_inst)
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
		long_inst ? ((short int)args->data + proc->pc) : ((short int)args->data + proc->pc) % IDX_MOD, long_inst ? 2 : 4);
	}
	return (1);
}

static int		ocp_analyse(t_op *inst, unsigned char ocp, t_arg args[MAX_ARGS_NUMBER])
{
	unsigned char		cpt;
	int					ret;

	cpt = MAX_ARGS_NUMBER - 1;

	// printf("Opcode = %d\n", ZJMP);
	ret = 0;
	while (cpt > inst->param_number - 1)
	{
		ocp >>= 2;
		--cpt;
	}
	while (cpt < 42) // quick & dirty
	{
		args[cpt].type = ocp & 0b11;
		if (!(inst->param_mask[cpt] & (1 << ((args[cpt].type) - 1))))
		{
			ret |= 0b1;
			// printf("ERROR WITH ARG %u\n", cpt);
		}
		ocp >>= 2;
		--cpt;
	}
	return (ret);
}

int				get_args(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER], t_op *inst)
{
	unsigned int		i;
	int					ptr;
	unsigned int		dir_adr;
	unsigned char		valid_inst;
	
	if (inst->ocp & 0b1 && ocp_analyse(inst, vm->mem[(proc->pc + 1) % MEM_SIZE], args))
	{
		// printf("YO\n");
		valid_inst = 0;
	}
	else
		valid_inst = 1;
	i = 0;
	ptr = (proc->pc + 1 + inst->ocp) % MEM_SIZE;
 	dir_adr = (inst->direct_adr == 0) * 2;
	while (i < inst->param_number)
	{
		if (args[i].type == T_REG)
			args[i].size = T_REG;
		else 
			args[i].size = (args[i].type == T_DIR) ? T_DIR + dir_adr : 2;
		args[i].data = get_arg_data(vm->mem, ptr, args[i].size);
		valid_inst &= get_arg_value(vm, proc, args + i, inst->long_inst);
		ptr = (ptr + args[i].size) % MEM_SIZE;
		++i;
	}
	if (!valid_inst)
	{
		moove_pc(vm, proc, args[0].size + args[1].size + args[2].size + 1 + inst->ocp);
		return (0);
	}
	return (1);
}