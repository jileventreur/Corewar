/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:18:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/01/26 20:22:20 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			is_player_alive(t_list *plst, int player)
{
	t_list	*tmp;

	tmp = plst;
	while (tmp)
	{
		if (((t_proc *)(tmp->content))->player_num == (unsigned int)player ||
			((t_proc *)(tmp->content))->player_num == (unsigned int)player + MAX_PLAYERS)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		clear_and_resize(int line, int col)
{
	static int	old_line;
	static int	old_col;
	int			i;

	if (col != old_col || line != old_line)
	{
		wresize(g_scr_infos, INFO_HEIGHT, line);
		mvwin(g_scr_infos, (col - INFO_HEIGHT) >= 0 ? col - INFO_HEIGHT : 0, 0);
		getmaxyx(g_scr_infos, col, line);
	}
	old_col = col;
	old_line = line;
	i = -1;
	while (++i < line)
		mvwprintw(g_scr_infos, 0, i, "_");
}

int			valid_infos_window(int *line)
{
	int			col;
	static int	valid_window;

	getmaxyx(stdscr, col, *line);
	if (*line < INFO_WIDTH || col < INFO_HEIGHT)
	{
		wclear(g_scr_infos);
		clear_and_resize(*line, col);
		mvwprintw(g_scr_infos, INFO_HEIGHT / 2, (*line) / 2, "Window too small to print infos.");
		return (FALSE);
	}
	if (valid_window == FALSE)
	{
		wclear(g_scr_infos);
		valid_window = TRUE;
	}
	clear_and_resize(*line, col);
	return (TRUE);
}

int			get_prog_max_len(t_vm * vm)
{
	int		i;
	int		max;
	int		curr_len;

	i = -1;
	max = 0;
	while (++i < (int)vm->n_players)
	{
		if ((curr_len = ft_strlen(vm->c[i].header.prog_name)) > max)
			max = curr_len;
	}
	return (max);
}

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

void		print_players(t_vm *vm, int all_procs, int *p)
{
//	t_list	*tmp;
	int i;
	int j;
	int	procs;
	int	prog_max_len;
	
	prog_max_len = get_prog_max_len(vm) + 5;

//	tmp = vm->plst;
	i = -1;

	while (++i < (int)vm->n_players)
	{
		mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 0, "%d :", i + 1);
		mvwprintw(g_scr_infos, (i + 1) * 2 - 1, prog_max_len, "_ memory  : [");
		mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 33 + prog_max_len, "] %d%%", p[i] * 100 / all_procs);
	}
	i = -1;
	while (++i < (int)vm->n_players)
	{
		wattron(g_scr_infos, COLOR_PAIR(i + 1));
		mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 4, "%s", vm->c[i].header.prog_name);
		procs = p[i] * 20 / all_procs;
		j = -1;
		while (++j < procs)
			mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 13 + prog_max_len + j, "_");
		while (++j < 20)
			mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 13 + prog_max_len + j, " ");
		wattroff(g_scr_infos, COLOR_PAIR(i + 1));
		if (is_player_alive(vm->plst, i + 1))
		{
			wattron(g_scr_infos, COLOR_PAIR(2));
			mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 40 + prog_max_len, " ALIVE");
			wattroff(g_scr_infos, COLOR_PAIR(2));
		}
		else
		{
			wattron(g_scr_infos, COLOR_PAIR(3));
			mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 40 + prog_max_len, " DEAD ");
			wattroff(g_scr_infos, COLOR_PAIR(3));
		}
	}
}
void		nprint_infos(t_vm *vm)
{
	int		line;
	int		p[vm->n_players];
	int		all_procs;
	int		i;
	int		next_live;

	(void)vm;
	line = 0;
	if (!valid_infos_window(&line))
	{
		wrefresh(g_scr_infos);
		return ;
	}
	process_per_player(vm, p, &all_procs);
	print_players(vm, all_procs, p);
	mvwprintw(g_scr_infos, 1, line / 2, "total cycle : %d", vm->total_cycle);
	mvwprintw(g_scr_infos, 3, line / 2, "next live check : ");
	i = -1;
	if (vm->next_live_check != 0)
		next_live = (vm->next_live_check * 10) / CYCLE_TO_DIE;
	else
		next_live  = 0;
	wattron(g_scr_infos, COLOR_PAIR(17));
	while (++i < next_live)
		mvwprintw(g_scr_infos, 3, line / 2 + 19 + i, " ");
	wattroff(g_scr_infos, COLOR_PAIR(16));
	while (++i < 10)
		mvwprintw(g_scr_infos, 3, line / 2 + 19 + i, " ");
	wrefresh(g_scr_infos);
}

void		init_ncurses()
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

void		nprint_vm(t_vm * vm)
{
//	int		ch = -1;	// Key pressed ID
	int		col = 0, line = 0;

	init_ncurses();
	getmaxyx(stdscr, col, line);
	g_scr_infos = newwin(INFO_HEIGHT, line, col - INFO_HEIGHT, 0);
	getmaxyx(g_scr_infos, col, line);
//	while (ch != 'q')
//	{
		clear();
		nprint_procs(vm);
		exec_vm(vm);
//		cbreak();
//		wtimeout(stdscr, 5000);
//		ch = getch();
//		refresh();
//	}
	endwin();
}
