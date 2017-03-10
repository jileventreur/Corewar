/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wait_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 01:11:32 by cadam             #+#    #+#             */
/*   Updated: 2017/03/10 01:11:33 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	screen_change(void)
{
	static int	old_y = -1;
	static int	old_x = -1;
	int			x;
	int			y;

	if (old_y == -1)
	{
		getmaxyx(stdscr, old_y, old_x);
		return (1);
	}
	getmaxyx(stdscr, y, x);
	if (y != old_y || x != old_x)
	{
		old_y = y;
		old_x = x;
		return (1);
	}
	return (0);
}

void		print_wait_end(t_vm *vm)
{
	int		ch;
	int		x_max;
	int		y_max;
	char	*s;

	wclear(stdscr);
	getmaxyx(stdscr, y_max, x_max);
	refresh();
	ft_asprintf(&s, "Contestant %u, \"%s\" has won !\n",
	-vm->last_live, vm->c[-vm->last_live - 1].header.prog_name);
	while ((ch = getch()) != 'q' && ch != ' ')
	{
		refresh();
		if (!screen_change())
			continue ;
		wclear(stdscr);
		getmaxyx(stdscr, y_max, x_max);
		refresh();
		nprint_infos(vm, 0);
		mvprintw((y_max - INFO_HEIGHT) / 2, (x_max) / 2 - ft_strlen(s) / 2, s);
		refresh();
	}
	free(s);
}
