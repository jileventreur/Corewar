/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 16:01:26 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/13 14:50:19 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			is_player_alive(t_list *plst, int player)
{
	t_list			*tmp;
	unsigned int	player_num;

	tmp = plst;
	while (tmp)
	{
		player_num = ((t_proc *)(tmp->content))->player_num;
		if (player_num == (unsigned int)player ||
			player_num == (unsigned int)player + MAX_PLAYERS)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		print_pourcent(int curr_value, int max_value, int line, int col)
{
	int j;
	int	total;

	j = 0;
	total = curr_value * 20 / ((max_value > 0) ? max_value : 1);
	while (j < total)
	{
		mvwprintw(g_scr_infos, line, col + j, "=");
		j++;
	}
	while (j < 20)
	{
		mvwprintw(g_scr_infos, line, col + j, " ");
		j++;
	}
}

void		print_is_alive(t_vm *vm, int line, int col, int player)
{
	if (is_player_alive(vm->plst, player))
	{
		wattron(g_scr_infos, COLOR_PAIR(2));
		mvwprintw(g_scr_infos, line, col, " ALIVE");
		wattroff(g_scr_infos, COLOR_PAIR(2));
	}
	else
	{
		wattron(g_scr_infos, COLOR_PAIR(3));
		mvwprintw(g_scr_infos, line, col, " DEAD ");
		wattroff(g_scr_infos, COLOR_PAIR(3));
	}
}

void		print_color_infos(t_vm *vm, int all_procs, int total, int *p)
{
	int		i;
	int		line;
	int		prog_max_len;
	char	*s;

	(void)all_procs;
	i = -1;
	line = 2;
	prog_max_len = get_prog_max_len(vm) + 5;
	while (++i < MAX_PLAYERS)
	{
		if (!vm->c[i].num)
			continue ;
		s = ft_strsub(vm->c[i].header.prog_name, 0, prog_max_len - 5);
		wattron(g_scr_infos, COLOR_PAIR(vm->c[i].num));
		mvwprintw(g_scr_infos, line, 4, "%s", s);
		print_pourcent(p[i], MEM_SIZE, line, 17 + prog_max_len);
		print_pourcent(vm->c[i].procs, total, line + 2, 17 + prog_max_len);
		wattroff(g_scr_infos, COLOR_PAIR(vm->c[i].num));
		print_is_alive(vm, line, 44 + prog_max_len, vm->c[i].num);
		line += 4;
		free(s);
	}
}

void		print_players(t_vm *vm, int allprocs, int *p)
{
	int i;
	int	line;
	int	len;
	int	procs;

	line = 2;
	len = get_prog_max_len(vm) + 5;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (!vm->c[i].num)
			continue ;
		procs = vm->c[i].procs * 100 / vm->list_len;
		mvwprintw(g_scr_infos, line, 0, "%d :", vm->c[i].num);
		mvwprintw(g_scr_infos, line, len, "_ memory     : [");
		mvwprintw(g_scr_infos, line, 37 + len, "] %d%%  ",
		p[i] * 100 / MEM_SIZE);
		mvwprintw(g_scr_infos, line + 2, len, "_ processes  : [");
		mvwprintw(g_scr_infos, line + 2, 37 + len, "] %d%%  ", procs);
		line += 4;
	}
	print_color_infos(vm, allprocs, vm->list_len, p);
}
