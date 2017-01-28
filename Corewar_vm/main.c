#include "corewar.h"

void	ft_error_exit(const char *exit_message)
{
	ft_puterror(exit_message);
	exit(1);
}

void		my_print_args(t_arg args[MAX_ARGS_NUMBER], unsigned int arg_number)
{
	unsigned int	i;

	i = 0;
	while (i < arg_number)
	{
		printf("arg[%d] data %d (0x%llx)", i, args[i].data, (unsigned long long int)args[i].data);
			if ((unsigned int)args[i].type == NULL_CODE)
				printf(" type null ");
			if ((unsigned int)args[i].type == REG_CODE)
				printf(" type reg ");
			else if ((unsigned int)args[i].type == DIR_CODE)
				printf(" type dir ");
			else
				printf(" type ind ");
		printf("value %d (0x%llx)\n", args[i].value, (unsigned long long int)args[i].value);
		++i;
	}	
}

void		print_args(t_arg args[MAX_ARGS_NUMBER], unsigned int arg_number, unsigned char long_inst, unsigned char dest)
{
	unsigned int	i;

	i = 0;
	while (i < arg_number)
	{
			if ((unsigned int)args[i].type == NULL_CODE)
				printf("NULL");
			if ((unsigned int)args[i].type == T_REG && i == dest)
				printf("r%d", args[i].data);
			else if ((unsigned int)args[i].type == T_REG)
				printf("%d", args[i].value);
			else if ((unsigned int)args[i].type == T_IND && long_inst)
			{
				printf("%hd", (short int)args[i].value);
			}
			else if ((unsigned int)args[i].type == T_IND)
				printf("%d", (int)args[i].value);
			else if (args[i].size == 2)
				printf("%hd", (short int)args[i].value);
			else
				printf("%d", args[i].value);
		++i;
			if (i < arg_number)
				printf(" ");
	}
}

void		null_instr(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER])
{
	int i = 0;
	int	ptr;
	unsigned short int *test;

	(void)args;
	while (i < 4)
	{
		++i;
	}
	ptr = (proc->pc + 2) % MEM_SIZE;
	test = (unsigned short int *)&vm->mem[ptr + 1];
}


void		write_var(t_vm *vm, t_proc *proc, unsigned char *var, lint beg)
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

void	introducing_contestants(t_champion *c)
{
	int		i;

	i = -1;
	printf("Introducing contestants...\n");
	while (++i < MAX_PLAYERS)
	{
		if (ft_memisset(&c[i], sizeof(t_champion), 0))
			continue ;
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", c[i].num, c[i].header.prog_size, c[i].header.prog_name, c[i].header.comment);
	}
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	if (argc == 1)
		ft_error_exit("Error: not enough args\n");
	--argc;
	++argv;
	vm_init(&vm, argc, argv);
	introducing_contestants(vm.c);
	if (vm.opt.g)
		nprint_vm(&vm);
	else
		exec_vm(&vm);
	return (0);
}
