/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:18:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/01/20 14:09:02 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *		 --col-->
 *		|
 *		line
 *		|
 *		v
 */

int			find_player(t_list *plst, int i_cell)
{
	t_list	*tmp;

	tmp = plst;
	while (tmp)
	{
		if (((t_proc *)(tmp->content))->pc == i_cell)
			return (((t_proc *)(tmp->content))->player_num);
		tmp = tmp->next;
	}
	return (0);
}

int			valid_proc_window(int *col)
{
	int		line;

	getmaxyx(stdscr, line, *col);

//	line -= INFO_HEIGHT;
//	col -= INFO_WIDTH;
	if (line * (*col) < MEM_SIZE * CELL_LEN)
	{
		mvprintw(line / 2, (*col) / 2, "Window too small.");
		return (FALSE);
	}
	return (TRUE);
}

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

void		nprint_procs(t_vm *vm)
{
	int		col;
	int		y_max;
	int		x_max;

	static int i;

	i++;
	clear();
	if (!valid_proc_window(&col))
	{
		refresh();
		return ;
	}
	else
	{
//		col -= INFO_WIDTH;
		if (col % CELL_LEN != 0)
			col -= col % CELL_LEN;
		y_max = (MEM_SIZE * CELL_LEN) / col;
		if ((MEM_SIZE * CELL_LEN) % col != 0)
			y_max++;
		int j = -1;
		while (++j < y_max)
		{
			if (j == y_max - 1 && (MEM_SIZE * CELL_LEN) % col != 0)
				x_max = (MEM_SIZE * CELL_LEN) % col;
			else
				x_max = col;
			int	i = 0;
			while (i < x_max)
			{
				int i_cell = (j * col + i) / CELL_LEN;
				int	color = find_player(vm->plst, i_cell);
				if (color)
					wattron(stdscr, COLOR_PAIR(color + 10));
				else
					wattron(stdscr, COLOR_PAIR(vm->proc_mem[i_cell]));
				mvprintw(j, i, "%02x", vm->mem[i_cell]);
				if (color)
					wattroff(stdscr, COLOR_PAIR(color + 10));
				else
					wattroff(stdscr, COLOR_PAIR(vm->proc_mem[i_cell]));
				i += CELL_LEN;
				
			}
		}
	}
	refresh();
}

int			valid_infos_window(void)
{
	int		col;
	int		line;

	getmaxyx(stdscr, line, col);
	if (col < INFO_WIDTH || line < INFO_HEIGHT)
	{
		wresize(g_scr_infos, line, col);
		mvwprintw(g_scr_infos, line / 2, col / 2, "Window too small.");
		return (FALSE);
	}
	return (TRUE);
}

void		nprint_infos(t_vm *vm)
{
	int		col;
	int		line;
	int		i;
	int		next_live;

	col = 0;
	line = 0;
	wclear(g_scr_infos);
	if (!valid_infos_window())
	{
		wrefresh(g_scr_infos);
		return ;
	}
	getmaxyx(stdscr, line, col);
	wresize(g_scr_infos, INFO_HEIGHT, INFO_WIDTH);
	getmaxyx(g_scr_infos, col, line);

/*******************************************/
	int		p[MAX_PLAYERS];
	int		all_procs;

	i = -1;
	all_procs = 0;
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
			all_procs++;
		}
	}

/*******************************************/
	i = -1;
	while (++i < line)
		mvwprintw(g_scr_infos, 0, i, "_");

	t_list	*tmp;
	int j;
	int	procs;

	tmp = vm->plst;
	i = 0;

	while (++i <= (int)vm->n_players)
	{
		wattron(g_scr_infos, COLOR_PAIR(i));
		mvwprintw(g_scr_infos, i * 2 - 1, 0, "PLAYER %d", i);
		wattroff(g_scr_infos, COLOR_PAIR(i));
		mvwprintw(g_scr_infos, i * 2 - 1, 9, "_ process : [");
		procs = p[i - 1] * 20 / all_procs;
		j = -1;
		wattron(g_scr_infos, COLOR_PAIR(i));
		while (++j < procs)
			mvwprintw(g_scr_infos, i * 2 - 1, 22 + j, "_");
		wattroff(g_scr_infos, COLOR_PAIR(i));
		mvwprintw(g_scr_infos, i * 2 - 1, 42, "] %d%%", p[i -1] * 100 / all_procs);
		if (is_player_alive(vm->plst, i))
		{
			wattron(g_scr_infos, COLOR_PAIR(2));
			mvwprintw(g_scr_infos, i * 2 - 1, 49, " ALIVE");
			wattroff(g_scr_infos, COLOR_PAIR(2));
		}
		else
		{
			wattron(g_scr_infos, COLOR_PAIR(3));
			mvwprintw(g_scr_infos, i * 2 - 1, 49, " DEAD");
			wattroff(g_scr_infos, COLOR_PAIR(3));
		}
	}

/*******************************************/
	mvwprintw(g_scr_infos, 1, line / 2, "total cycle : %d", vm->total_cycle);

/*******************************************/
	mvwprintw(g_scr_infos, 3, line / 2, "next live check : [");
	i = -1;
	if (vm->next_live_check != 0)
		next_live = (vm->next_live_check * 10) / CYCLE_TO_DIE;
	else
		next_live  = 0;
	wattron(g_scr_infos, COLOR_PAIR(16));
	while (++i < next_live)
		mvwprintw(g_scr_infos, 3, line / 2 + 19 + i, "_");
	wattroff(g_scr_infos, COLOR_PAIR(16));
	mvwprintw(g_scr_infos, 3, line / 2 + 19 + 10, "]");


	mvwprintw(g_scr_infos, 7, line / 2, "n_list : %d", vm->n_players);
/*******************************************/

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
	init_pair(17, COLOR_BLACK, COLOR_BLACK);
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
