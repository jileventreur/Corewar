/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:18:24 by nbelouni          #+#    #+#             */
/*   Updated: 2017/01/25 20:44:59 by nbelouni         ###   ########.fr       */
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

void		fill_cell_player(t_list *plst, int array[][2])
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = plst;
	while (tmp)
	{
		array[i][0] = ((t_proc *)(tmp->content))->pc;
		array[i][1] = ((t_proc *)(tmp->content))->player_num;
		tmp = tmp->next;
		i++;
	}
	
}

int			valid_proc_window(int *col)
{
	int		line;

	getmaxyx(stdscr, line, *col);

	line = (INFO_HEIGHT < line) ? line - INFO_HEIGHT : 0;
	if (line * (*col) < MEM_SIZE * CELL_LEN)
	{
		mvprintw(line / 2, (*col) / 2, "Window too small to print processes.");
		return (FALSE);
	}
	return (TRUE);
}

int			find_player(t_vm *vm, int i_cell)
{
	t_list	*tmp;

	tmp = vm->plst;
	while (tmp)
	{
		if (((t_proc *)(tmp->content))->pc == i_cell)
			return (((t_proc *)(tmp->content))->player_num + 10);
		tmp = tmp->next;
	}
	return (vm->proc_mem[i_cell]);
}

void		nprint_procs(t_vm *vm)
{
	int		col;
	int		y_max;
	int		x_max;
	int		board;
//	int		cell_player[vm->list_len][2];
	int 	i;
	int 	j;
	int		i_cell;
	int		color;
	int		new_color;

	clear();
	board = MEM_SIZE * CELL_LEN;
	color = 0;
	if (!valid_proc_window(&col))
	{
		refresh();
		return ;
	}
	else
	{
//		fill_cell_player(vm->plst, cell_player);

		if (col % CELL_LEN != 0)
			col -= col % CELL_LEN;
		y_max = board / col;
		if (board % col != 0)
			y_max++;
		j = -1;
		while (++j < y_max)
		{
			if (j == y_max - 1 && (x_max = board % col) == 0)
				x_max = 0;
			i = 0;
			while (i < x_max)
			{
				i_cell = (j * col + i) / CELL_LEN;
				new_color = find_player(vm, i_cell);
				if (new_color != color)
				{
					wattroff(stdscr, COLOR_PAIR(color));
					color = new_color;
					wattron(stdscr, COLOR_PAIR(color));
				}

				mvprintw(j, i, "%02x", vm->mem[i_cell]);
				i += CELL_LEN;
				
			}
		}
	}
	refresh();
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
int			valid_infos_window(void)
{
	int		i;
	int		col;
	int		line;

	i = -1;
	getmaxyx(stdscr, line, col);
	if (col < INFO_WIDTH || line < INFO_HEIGHT)
	{
		wresize(g_scr_infos, line, col);
		line = (INFO_HEIGHT < line) ? line - INFO_HEIGHT : 0;
		mvwin(g_scr_infos, line, 0);
		i = -1;
		while (++i < col)
			mvwprintw(g_scr_infos, 0, i, "_");

		mvwprintw(g_scr_infos, INFO_HEIGHT / 2, col / 2, "Window too small to print infos.");
		return (FALSE);
	}
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
	wresize(g_scr_infos, INFO_HEIGHT, col);
	mvwin(g_scr_infos, (line - INFO_HEIGHT) >= 0 ? line - INFO_HEIGHT : 0, 0);
	getmaxyx(g_scr_infos, col, line);

/*******************************************/
	int		p[vm->n_players];
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

//	t_list	*tmp;
	int j;
	int	procs;
	int	prog_max_len;
	
	prog_max_len = get_prog_max_len(vm) + 5;

//	tmp = vm->plst;
	i = -1;

	while (++i < (int)vm->n_players)
	{
		mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 0, "%d :", i + 1);
		wattron(g_scr_infos, COLOR_PAIR(i + 1));
		mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 4, "%s", vm->c[i].header.prog_name);
		wattroff(g_scr_infos, COLOR_PAIR(i + 1));
		mvwprintw(g_scr_infos, (i + 1) * 2 - 1, prog_max_len, "_ memory  : [");
		procs = p[i] * 20 / all_procs;
		j = -1;
		wattron(g_scr_infos, COLOR_PAIR(i + 1));
		while (++j < procs)
			mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 13 + prog_max_len	+ j, "_");
		wattroff(g_scr_infos, COLOR_PAIR(i + 1));
		mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 33 + prog_max_len, "] %d%%", p[i] * 100 / all_procs);
		if (is_player_alive(vm->plst, i + 1))
		{
			wattron(g_scr_infos, COLOR_PAIR(2));
			mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 40 + prog_max_len, " ALIVE");
			wattroff(g_scr_infos, COLOR_PAIR(2));
		}
		else
		{
			wattron(g_scr_infos, COLOR_PAIR(3));
			mvwprintw(g_scr_infos, (i + 1) * 2 - 1, 40 + prog_max_len, " DEAD");
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

	i = -1;
	while (++i < (int)(vm->n_players))
	{
		mvwprintw(g_scr_infos, 7, line / 2  + i * 10, "proc : %d", vm->c[i].mem);
	}
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
