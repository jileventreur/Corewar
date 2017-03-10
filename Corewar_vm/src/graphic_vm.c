/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_vm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:01:46 by nbelouni          #+#    #+#             */
/*   Updated: 2017/02/13 15:08:33 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		is_end_corewar(int ch)
{
	if (ch == 'q')
	{
		endwin();
		exit(1);
	}
}

void		get_input_and_fsp(int *ch, int *refresh_speed)
{
	wtimeout(stdscr, 0);
	if ((*ch = getch()) == ERR)
		return ;
	is_end_corewar(*ch);
	if (*ch == ' ')
	{
		while ((*ch = getch()) != ' ')
			is_end_corewar(*ch);
	}
	else if (*ch == '=' && *refresh_speed > 1000)
		*refresh_speed -= 100;
	else if (*ch == '-' && *refresh_speed < 10000)
		*refresh_speed += 100;
}

void		print_all(t_vm *vm, int refresh_speed)
{
	char	c;

	if (vm->opt.s && !vm->opt.g)
	{
		if (vm->total_cycle % vm->opt.s != 0)
			return ;
		while ((c = getch()) != ' ')
			is_end_corewar(c);
		nprint_procs(vm);
		nprint_infos(vm, refresh_speed);
		return ;
	}
	else if (vm->total_cycle % 50 == 0)
		nprint_procs(vm);
	else if (vm->total_cycle % 20 == 0)
		nprint_infos(vm, refresh_speed);
	usleep(refresh_speed);
}
