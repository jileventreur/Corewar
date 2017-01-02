/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 18:18:24 by nbelouni          #+#    #+#             */
/*   Updated: 2016/12/15 20:16:03 by nbelouni         ###   ########.fr       */
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

int			valid_window(int *col)
{
	int		line;

	getmaxyx(stdscr, line, *col);

	if (line * (*col) < MEM_SIZE * CELL_LEN)
	{
		mvprintw(line / 2, (*col) / 2, "Window too small.");
		return FALSE;
	}
	return (TRUE);
}

void		nprint_procs(t_vm *vm)
{
	int		col;
	int		y_max;
	int		x_max;

	clear();
	if (!valid_window(&col))
	{
		refresh();
		return ;
	}
	else
	{
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
	init_pair(16, COLOR_BLACK, COLOR_CYAN);
	init_pair(17, COLOR_BLACK, COLOR_BLACK);
}

void		nprint_vm(t_vm * vm)
{
	int					ch = -1;	// Key pressed ID

	(void)vm;

	init_ncurses();
	while (ch != 'q')
	{
		clear();
//		nprint_procs(vm);
		exec_vm(vm);
		cbreak();
		wtimeout(stdscr, 5000);
		ch = getch();
		refresh();
	}
	endwin();
}
