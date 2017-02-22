/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilano <jilano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 21:33:27 by cadam             #+#    #+#             */
/*   Updated: 2017/02/07 00:15:23 by jilano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		mem_init(unsigned char *mem, unsigned char *proc_mem,
				t_champion *c, int player_number)
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
		*proc_mem = c[i].num + 4;
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
		*(int *)(tmp.reg[0]) = c[i].num * -1;
		tmp.player_num = c[i].num;
		tmp.proc_num = ++player_cpt;
		ft_lstadd(&lst, ft_lstnew(&tmp, sizeof(t_proc)));
	}
	return (lst);
}

void			vm_init(t_vm *vm, int argc, char **argv)
{
	int		player_number;
	int		i;

	i = MAX_PLAYERS - 1;
	ft_bzero(vm, sizeof(t_vm));
	get_opt(&argv, &argc, &vm->opt);
	if ((player_number = get_players(argv, argc, vm->c)) == 0)
		ft_error_exit("Error: No champion\n");
	vm->plst = proc_init(vm->c, player_number);
	mem_init(vm->mem, vm->proc_mem, vm->c, player_number);
	proc_cycle_init(vm->plst, vm->mem);
	vm->ctd = CYCLE_TO_DIE;
	vm->procs_death_nb = 0;
	vm->live_num = 0;
	vm->total_cycle = 0;
	vm->last_ctd_dec = 1;
	vm->next_live_check = CYCLE_TO_DIE;
	vm->list_len = player_number;
	vm->n_players = player_number;
	while (ft_memisset(&vm->c[i], sizeof(t_champion), 0))
		--i;
	vm->last_live = -(i + 1);
}
