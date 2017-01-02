#include "corewar.h"

static void		mem_init(unsigned char mem[MEM_SIZE], unsigned char proc_mem[MEM_SIZE], t_champion *c, int player_number)
{
	int	i;

	i = -1;
	ft_bzero(mem, MEM_SIZE);
	ft_bzero(proc_mem, MEM_SIZE);
	while (++i < MAX_PLAYERS)
	{
		if (ft_memisset(&c[i], sizeof(t_champion), 0))
			continue ;
		ft_memcpy(mem, c[i].prog, c[i].header.prog_size);
		*proc_mem = c[i].num | PC_BIT;
		ft_memset(proc_mem + 1, c[i].num, c[i].header.prog_size - 1);
		mem += MEM_SIZE / player_number;
		proc_mem += MEM_SIZE / player_number;
	}
}

static void		proc_cycle_init(t_list *lst, unsigned char *mem)
{
	while (lst)
	{
		get_proc_cycle(lst->content, mem);
		lst = lst->next;
	}
}

static t_list	*proc_init(t_champion *c, int player_number)
{
	int		i;
	int		player_cpt;
	t_proc	tmp;
	t_list	*lst;

	i = -1;
	ft_bzero(&tmp, sizeof(t_proc));
	lst = NULL;
	player_cpt = 0;
	while (++i < MAX_PLAYERS)
	{
		if (ft_memisset(&c[i], sizeof(t_champion), 0))
			continue ;
		tmp.pc = player_cpt * MEM_SIZE / player_number;
		*(int *)(tmp.reg[0]) = c[i].num * -1; // a voir si on laisse en -num ou pas
		tmp.player_num = c[i].num;
		tmp.proc_num = ++player_cpt;
		ft_lstadd(&lst, ft_lstnew(&tmp, sizeof(t_proc)));
	}
	return (lst);
}

void			max_arg_size_init(t_vm *vm)
{
	extern t_op		op_tab[17];
	int				i;
	int				j;
	int				k;
	int				sum;

	i = 0;
	while (i < 17)
	{
		sum = 0;
		j = 0;
		while (j < 3)
		{
			k = 1 << sizeof(char) * 8;
			while (k && op_tab[i].param_mask[j] / k == 0)
				k >>= 1;
			vm->max_arg_size[i][j] = k;
			sum += k;
			++j;
		}
		vm->max_arg_size[i][MAX_ARGS_NUMBER] = sum;
		++i;
	}
}

void			print_opt(t_opt *opt)
{
	printf("opt->a is %s\n", opt->a ? "ON" : "OFF");
	printf("opt->d is %d\n", opt->d);
	printf("opt->s is %d\n", opt->s);
	printf("opt->v is %d\n", opt->v);
}

void			get_opt(char ***argv_source, int *argc, t_opt *opt)
{
	int		i;
	char	**argv;

	i = 0;
	argv = *argv_source;
	opt->d = -1;
	while (i < *argc && **argv == '-')
	{
		if (ft_strlen(*argv) < 2)
			ft_error_exit("Error: no option after -\n");
		if (*(*argv + 1) == 'n')
			break ;
		if (!ft_isanyof(*(*argv + 1), OPTION))
			ft_error_exit("Error: incompatible option\n");
		if (*(*argv + 1) == 'a' && (*(*argv + 2)) == '\0')
			opt->a = 1;
		else if (*(*argv + 1) == 'd' || !ft_strcmp("-dump", *argv))
		{
			if (i + 1 >= *argc)
				ft_error_exit("Error: no argument after -d\n");
			if (!ft_strisuint(*++argv))
				ft_error_exit("Error: argument after -d is not an unsigned number\n");
			opt->d = ft_atoi(*argv);
			++i;
		}
		else if (*(*argv + 1) == 's' && (*(*argv + 2)) == '\0')
		{
			if (i + 1 >= *argc)
				ft_error_exit("Error: no argument after -d\n");
			if (!ft_strisuint(*++argv))
				ft_error_exit("Error: argument after -s is not an unsigned number\n");
			if ((opt->s = ft_atoi(*argv)) == 0)
				ft_error_exit("Error: argument after -s can't be zero\n");
			++i;
		}
		else if (*(*argv + 1) == 'v' && (*(*argv + 2)) == '\0')
		{
			if (i + 1 >= *argc)
				ft_error_exit("Error: no argument after -d\n");
			if (!ft_strisuint(*++argv))
				ft_error_exit("Error: argument after -v is not an unsigned number\n");
			opt->v = ft_atoi(*argv);
			++i;
		}
		else
			ft_error_exit("Error: multiple option not allowed\n");
		++argv;
		++i;
	}
	*argv_source = argv;
	*argc -= i;
}

void			vm_init(t_vm *vm, int argc, char **argv)
{
	int		player_number;
	int		i;

	i = MAX_PLAYERS -1;
	ft_bzero(vm, sizeof(t_vm));
	get_opt(&argv, &argc, &vm->opt);
	if ((player_number = get_players(argv, argc, vm->c)) == 0)
		ft_error_exit("Error: No champion\n");
	vm->plst = proc_init(vm->c, player_number);
	mem_init(vm->mem, vm->proc_mem, vm->c, player_number);
	proc_cycle_init(vm->plst, vm->mem);
	vm->ctd = CYCLE_TO_DIE;
	vm->live_num = 0; // could be rm 
	vm->total_cycle = 1;
	vm->last_ctd_dec = 1;
	vm->next_live_check = CYCLE_TO_DIE;
	vm->list_len = player_number;
	while (ft_memisset(&vm->c[i], sizeof(t_champion), 0))
	--i;
	vm->last_live = -(i + 1);
	max_arg_size_init(vm);
}
