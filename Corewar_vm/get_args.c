#include "corewar.h"

lint		get_arg_data(unsigned char mem[MEM_SIZE], int beg, unsigned int len)
{
	lint			res;
	unsigned int	cpt;

	res = 0;
	cpt = 0;
	// ft_printf("mem[%u]", beg);
	// ft_printf(" (%x)\n", mem[beg]);
	// printf("len = %u\n", len);
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
	// printf("res == %lld\n", res);
		}
	}
	// printf("fres == %lld\n", res);
	return (res);
}

static int		get_arg_value(t_vm *vm, t_proc *proc, t_arg *args, unsigned char long_inst)
{
	// printf("coucou\n");
	// printf("%x\n", vm->mem[ptr]);
	if (args->type == NULL_CODE)
	{
		printf("oui?\n");
		return (0);
	}
	else if (args->type == REG_CODE)
	{
		// printf("data = %lld\n", args->data);		
		// printf("jai rien a foutre la\n");
		if ((unsigned)args->data - 1 > 15)
			return (0);
		args->value = REG(args->data - 1);
	}
	else if (args->type == DIR_CODE)
		args->value = args->data;
	else
	{	
		// printf("data == %hd\n", (short int)args->data);
		// printf("mem[%lld]\n", llabs((args->data) % MEM_SIZE));
		// ()vm->mem[llabs((args->data) % MEM_SIZE)]);
		// args->value = get_arg_data(vm->mem,
		// long_inst ? (short int)args->data : (short int)args->data % IDX_MOD, long_inst ? 2 : 4);
		args->value = get_arg_data(vm->mem,
		long_inst ? ((short int)args->data + proc->pc) : ((short int)args->data + proc->pc) % IDX_MOD, long_inst ? 2 : 4);
		// print_vm(vm);exit(1);
		// printf("long_inst %d\n", long_inst);
		// BSWAP_32(*(int *)(vm->mem + llabs((args->data) % MEM_SIZE)));
		// printf("value == %llu (0x%lx)\n", args->value, (unsigned long int)args->value);
		// printf("test %x\n", *(int *)(vm->mem));
	}
	return (1);
}

static int		ocp_analyse(t_op *inst, unsigned char ocp, t_arg args[MAX_ARGS_NUMBER])
{
	unsigned char		cpt;

	cpt = MAX_ARGS_NUMBER - 1;

	// printf("Opcode = %d\n", ZJMP);
	if (inst->opcode == ZJMP + 1)
		return (1);
	while (cpt > inst->param_number - 1)
	{
		ocp >>= 2;
		--cpt;
	}
	while (cpt < 42) // lol jsuis sur ca va marcher et jtrouve ca trop con
	{
		if (!(args[cpt].type = inst->param_mask[cpt] & (1 << ((ocp & 0b11) - 1))))
		{
			ft_printf("ERROR WITH ARG %u\n", cpt);
			return (0);
		}
		ocp >>= 2;
		--cpt;
	}
	return (1);
}

int				get_args(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER], t_op *inst)
{
	unsigned int		i;
	int					ptr;
	unsigned int		dir_adr;
	
	// print_vm(vm);
	// printf("opcode == %d\n", inst->opcode);
	if (inst->ocp & 0b1 && !ocp_analyse(inst, vm->mem[(proc->pc + 1) % MEM_SIZE], args))
	{
		// printf("BALEC FRERE\n");
		return (0);
	}
	// if (inst->opcode == 1)
	// {
	// 	args[0].type = DIR_CODE; // pour le test GERER LES INST SANS OCP
	// }
	// printf("coucou inst is  %s\n", inst->name);
	// exit(0);
	// printf("ocp ? %d\n", inst->ocp);
	i = 0;
	ptr = (proc->pc + 1 + inst->ocp) % MEM_SIZE;
	dir_adr = (inst->direct_adr == 0) * 2;
	while (i < inst->param_number)
	{
		if (args[i].type == T_REG)
			args[i].size = T_REG;
		else 
			args[i].size = (args[i].type == T_DIR) ? T_DIR + dir_adr : 2;
		// args[i].size = (args[i].type != REG_CODE) ? 2 + dir_adr : 1;
		args[i].data = get_arg_data(vm->mem, ptr, args[i].size);
		// printf("size %u type = %d\n", args[i].size, args[i].type);
		if (!get_arg_value(vm, proc, args + i, inst->long_inst))
		{
	// 		printf("ERREUR\n");
	// exit(0);
			return (0);
		}
		ptr = (ptr + args[i].size) % MEM_SIZE;
		++i;
		// printf("ptr = %d size = %u\n", ptr, args[i].size);
	}
	// print_args(args, 3);
	// exit(0);
	return (1);
}