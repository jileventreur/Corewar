/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_procs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:40:44 by nbelouni          #+#    #+#             */
/*   Updated: 2017/01/26 20:18:07 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			valid_proc_window(int *col)
{
	static int	old_line;
	static int	old_col;
	static int	valid_window;
	int			line;

	getmaxyx(stdscr, line, *col);
	line = (INFO_HEIGHT < line) ? line - INFO_HEIGHT : 0;
	if (line * (*col) < MEM_SIZE * CELL_LEN)
	{
		valid_window = FALSE;
		clear();
		mvprintw(line / 2, (*col) / 2, "Window too small to print processes.");
		refresh();
		return (FALSE);
	}
	if (*col != old_col || line != old_line || valid_window == FALSE)
		clear();
	if (valid_window == FALSE)
		valid_window = TRUE;
	old_col = *col;
	old_line = line;
	return (TRUE);
}

void		init_color_array(t_vm *vm, int *color_array)
{
	t_list	*tmp;
	t_proc	*content;
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		color_array[i] = vm->proc_mem[i];
	}
	tmp = vm->plst;
	while (tmp)
	{
		content = ((t_proc *)(tmp->content));
		color_array[content->pc] = content->player_num + 10;
		tmp = tmp->next;
	}
}

void		print_board(t_vm *vm, int *color_array, int col, int y_max)
{
	int		i;
	int		j;
	int		i_cell;
	int		color;

	j = -1;
	color = 16;
	while (++j < y_max)
	{
		i = 0;
		while (i < col)
		{
			i_cell = (j * col + i) / CELL_LEN;
			if (color_array[i_cell] != color)
			{
				wattroff(stdscr, COLOR_PAIR(color));
				color = color_array[i_cell];
				wattron(stdscr, COLOR_PAIR(color));
			}
			mvprintw(j, i, "%02x", vm->mem[i_cell]);
			i += CELL_LEN;
		}
	}
	wattroff(stdscr, COLOR_PAIR(color));
}

void		print_last_line(t_vm *vm, int *color_array, int col, int y_max)
{
	int		i;
	int		i_cell;
	int		color;

	i = 0;
	color = 16;
	while (i < col)
	{
		i_cell = (y_max * col + i) / CELL_LEN;
		if (color_array[i_cell] != color)
		{
			wattroff(stdscr, COLOR_PAIR(color));
			color = color_array[i_cell];
			wattron(stdscr, COLOR_PAIR(color));
		}
		mvprintw(y_max, i, "%02x", vm->mem[i_cell]);
		i += CELL_LEN;
	}
	wattroff(stdscr, COLOR_PAIR(color));
}

void		nprint_procs(t_vm *vm)
{
	int		col;
	int		y_max;
	int		board;
	int		*color_array;

	board = MEM_SIZE * CELL_LEN;
	if (!valid_proc_window(&col))
		return ;
	else
	{
		if (!(color_array = (int *)malloc(sizeof(int) * MEM_SIZE)))
			return ;
		init_color_array(vm, color_array);
		col -= col % CELL_LEN;
		y_max = board / col;
		if (board % col != 0)
			y_max++;
		print_board(vm, color_array, col, y_max - 1);
		col = board % col;
		if (col != 0)
			print_last_line(vm, color_array, col, y_max - 1);
		free(color_array);
	}
	refresh();
}
