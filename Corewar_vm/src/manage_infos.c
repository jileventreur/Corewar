/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:16:25 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/07 17:22:52 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		clear_and_resize(int line, int col)
{
	static int	old_line;
	static int	old_col;
	int			i;
	char		*s;

	s = " '+' : faster _ '-' : slower _ ' ' : pause _ 'q' : quit ";
	if (col != old_col || line != old_line)
	{
		old_col = col;
		old_line = line;
		wclear(g_scr_infos);
		wresize(g_scr_infos, INFO_HEIGHT, line);
		mvwin(g_scr_infos, (col - INFO_HEIGHT) >= 0 ? col - INFO_HEIGHT : 0, 0);
		getmaxyx(g_scr_infos, col, line);
	}
	else
	{
		old_col = col;
		old_line = line;
	}
	i = -1;
	while (++i < line)
		mvwprintw(g_scr_infos, 0, i, "_");
	mvwprintw(g_scr_infos, 0, 10, s);
}

int			valid_infos_window(int *line)
{
	int			col;
	static int	valid_window;
	char		*s;

	s = "Window too small to print infos.";
	getmaxyx(stdscr, col, *line);
	if (*line < INFO_WIDTH || col < INFO_HEIGHT)
	{
		wclear(g_scr_infos);
		clear_and_resize(*line, col);
		mvwprintw(g_scr_infos, INFO_HEIGHT / 2, (*line) / 2, s);
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

int			get_prog_max_len(t_vm *vm)
{
	int		i;
	int		max;
	int		curr_len;

	i = -1;
	max = 0;
	while (++i < MAX_PLAYERS)
	{
		if ((curr_len = ft_strlen(vm->c[i].header.prog_name)) > max)
			max = curr_len;
	}
	if (max > 15)
		return (15);
	return (max);
}
