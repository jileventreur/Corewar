#include "corewar.h"

static int		get_player_number(t_champion *c)
{
	int	i;
	int	cpt;
	
	i = 0;
	cpt = 0;
	while (i < MAX_PLAYERS)
	{
		if (!ft_memisset(&c[i], sizeof(t_champion), 0))
			++cpt;
		++i;
	}
	return (cpt);
}

static void		mem_init(unsigned char *mem, t_champion *c)
{
	int	player_number;
	int	i;

	player_number = get_player_number(c);
	i = -1;
	ft_bzero(mem, MEM_SIZE);
	while (++i < MAX_PLAYERS)
	{
		if (ft_memisset(&c[i], sizeof(t_champion), 0))
			continue ;
		ft_memcpy(mem, c[i].prog, CHAMP_MAX_SIZE);
			mem += MEM_SIZE / player_number;
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

static t_list	*proc_init(t_champion *c)
{
	int		i;
	int		player_number;
	int		player_cpt;
	t_proc	tmp;
	t_list	*lst;

	i = -1;
	ft_bzero(&tmp, sizeof(t_proc));
	lst = NULL;
	player_number = get_player_number(c);
	player_cpt = 0;
	while (++i < MAX_PLAYERS)
	{
		if (ft_memisset(&c[i], sizeof(t_champion), 0))
			continue ;
		tmp.pc = player_cpt * MEM_SIZE / player_number;
		tmp.reg[0][0] = c[i].num;
		// printf("tmp.reg[0][0] == %d\n", tmp.reg[0][0]);
		ft_lstadd(&lst, ft_lstnew(&tmp, sizeof(t_proc)));
		++player_cpt;
	}
	return (lst);
}

void			max_arg_size_init(t_vm *vm)
{
	int				i;
	int				j;
	int				k;
	int				sum;
	extern t_op		op_tab[17];

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
			// printf("op[%d] arg[%d], max_size = %d\n", i, j, k);
			++j;
		}
		vm->max_arg_size[i][MAX_ARGS_NUMBER] = sum;
		// printf("------------------------------\n");
		++i;
	}
}

void			vm_init(t_vm *vm, int argc, char **argv)
{
	// t_champion		c[MAX_PLAYERS];
	// t_list			*lst;
	// unsigned char	mem[MEM_SIZE];

	ft_bzero(vm, sizeof(t_vm));
	get_players(argv, argc, vm->c);
	vm->plst = proc_init(vm->c);
	mem_init(vm->mem, vm->c);
	proc_cycle_init(vm->plst, vm->mem);
	vm->ctd = CYCLE_TO_DIE;
	vm->live_num = 0;
	vm->last_ctd_dec = 0;
	vm->next_live_check = CYCLE_TO_DIE;
	max_arg_size_init(vm);
	// print_memory((unsigned char *)vm->max_arg_size, 17 * 4);
}