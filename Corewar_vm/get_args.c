#include "corewar.h"

static lint		get_arg_data(unsigned char *mem, unsigned int beg, unsigned int len)
{
	lint			res;
	unsigned int	cpt;

	res = 0;
	cpt = 0;
	// printf("BEG == %u\n", beg);
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
			res += mem[(beg + cpt) % MEM_SIZE];
			++cpt;
		}
	}
	return (res);
}

static int		get_arg_value(t_vm *vm, t_proc *proc, t_arg *args, int ptr)
{
	// printf("%x\n", vm->mem[ptr]);
	(void)ptr;
	if (args->type == NULL_CODE)
		return (0);
	else if (args->type == REG_CODE)
	{
		if ((unsigned)args->data - 1 > 15)
			return (0);
		args->value = *(int *)proc->reg[args->data - 1];
	}
	else if (args->type == DIR_CODE)
		args->value = args->data;
	else
	{	
		// printf("data == %hd\n", (short int)args->data);
		// printf("mem[%lld]\n", llabs((args->data) % MEM_SIZE));
		// ()vm->mem[llabs((args->data) % MEM_SIZE)]);
		args->value = get_arg_data(vm->mem, (short int)args->data, 4);
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

	while (cpt > inst->param_number - 1)
	{
		ocp >>= 2;
		--cpt;
	}
	while (cpt < 42) // lol jsuis sur ca va marcher et jtrouve ca trop con
	{
		if (!(args[cpt].type = inst->param_mask[cpt] & (1 << ((ocp & 0b11) - 1))))
		{
			printf("ERROR WITH ARG %u\n", cpt);
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
	
	printf("opcode == %d\n", inst->opcode);
	if (inst->opcode != 1 && !ocp_analyse(inst, vm->mem[(proc->pc + 1) % MEM_SIZE], args))
		return (0);
	i = 0;
	ptr = (proc->pc + 2) % MEM_SIZE;
	dir_adr = (inst->direct_adr == 0) * 2;
	while (i < inst->param_number)
	{
		args[i].size = (args[i].type != REG_CODE) ? 2 + dir_adr : 1;
		args[i].data = get_arg_data(vm->mem, ptr, args[i].size);
		if (!get_arg_value(vm, proc, args + i, ptr))
			return (0);
		++i;
		ptr = (ptr + args[i].size) % MEM_SIZE;
	}
	// print_args(args, 3);
	return (1);
}