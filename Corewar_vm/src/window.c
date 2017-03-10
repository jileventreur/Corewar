/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:18:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/13 15:15:04 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		process_per_player(t_vm *vm, int *p, int *all_procs)
{
	int	i;

	i = -1;
	*all_procs = 0;
	while (++i < MAX_PLAYERS)
		p[i] = 0;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (vm->proc_mem[i] > 0)
		{
			if (vm->proc_mem[i] <= (unsigned char)MAX_PLAYERS)
				p[vm->proc_mem[i] - 1] += 1;
			else
				p[vm->proc_mem[i] - (unsigned char)(MAX_PLAYERS) - 1] += 1;
			*all_procs += 1;
		}
	}
}

void		print_next_check(t_vm *vm, int line)
{
	int		i;
	float	next_live;

	mvwprintw(g_scr_infos, 4, line / 2, "next live check : [");
	i = 0;
	if (vm->next_live_check != 0 && vm->ctd != 0)
		next_live = ft_round(
		(float)(vm->next_live_check * 10) / (float)vm->ctd);
	else
		next_live = 0;
	wattron(g_scr_infos, COLOR_PAIR(16));
	while (i < next_live)
	{
		mvwprintw(g_scr_infos, 4, line / 2 + 20 + i, "=");
		i++;
	}
	wattroff(g_scr_infos, COLOR_PAIR(16));
	while (++i < 11)
		mvwprintw(g_scr_infos, 4, line / 2 + 20 + i, " ");
	mvwprintw(g_scr_infos, 4, line / 2 + 20 + i, "]");
}

void		nprint_infos(t_vm *vm, int fps)
{
	int		line;
	int		p[MAX_PLAYERS];
	int		all_procs;
	int		frames;

	line = 0;
	if (!valid_infos_window(&line))
	{
		wrefresh(g_scr_infos);
		return ;
	}
	process_per_player(vm, p, &all_procs);
	print_players(vm, all_procs, p);
	mvwprintw(g_scr_infos, 2, line / 2, "total cycle : %d", vm->total_cycle);
	print_next_check(vm, line);
	frames = fps > 0 ? (1000000 / (fps * 20)) : 0;
	mvwprintw(g_scr_infos, 8, line / 2, "frames per second :", frames);
	mvwprintw(g_scr_infos, 10, line / 2, "- info window : %d ", frames);
	frames = fps > 0 ? (1000000 / (fps * 50)) : 0;
	mvwprintw(g_scr_infos, 12, line / 2, "- processes window : %d ", frames);
	wrefresh(g_scr_infos);
}

void		init_ncurses(void)
{
	initscr();
	keypad(stdscr, TRUE);
	curs_set(0);
	noecho();
	start_color();
	attron(A_BOLD);
	attroff(A_BOLD);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_WHITE);
	init_pair(6, COLOR_GREEN, COLOR_WHITE);
	init_pair(7, COLOR_RED, COLOR_WHITE);
	init_pair(8, COLOR_BLUE, COLOR_WHITE);
	init_pair(9, COLOR_WHITE, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(12, COLOR_BLACK, COLOR_GREEN);
	init_pair(13, COLOR_BLACK, COLOR_RED);
	init_pair(14, COLOR_BLACK, COLOR_BLUE);
	init_pair(15, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(16, COLOR_CYAN, COLOR_BLACK);
	init_pair(17, COLOR_BLACK, COLOR_CYAN);
}

void		nprint_vm(t_vm *vm)
{
	int		col;
	int		line;
	int		ch;

	init_ncurses();
	getmaxyx(stdscr, col, line);
	g_scr_infos = newwin(INFO_HEIGHT, line, col - INFO_HEIGHT, 0);
	clear();
	nprint_procs(vm);
	nprint_infos(vm, 0);
	while ((ch = getch()) != ' ')
	{
		nprint_procs(vm);
		nprint_infos(vm, 0);
		is_end_corewar(ch);
	}
	exec_vm(vm);
}
