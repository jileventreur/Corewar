/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 21:33:27 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 21:33:28 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		print_usage2(void)
{
	ft_printf("    -g\t: Ncurses output mode\n");
	ft_printf("\033[0m");
	exit(0);
}

void			print_usage(void)
{
	ft_printf("\033[33;1m");
	ft_printf("Usage: ./corewar [-d N -s N -v [0..31] | -g] [-h] [-a]");
	ft_printf(" [-n [1..4]] <champion1.cor> <...>\n");
	ft_printf("    -a\t: Prints output from \"aff\"");
	ft_printf("(Default is to hide it)\n");
	ft_printf("    -d, -dump N\t: ");
	ft_printf("Dumps memory after N cycles then exits\n");
	ft_printf("    -n N\t: Assign a number to the next champion\n");
	ft_printf("    -s N\t: Runs N cycles, dumps memory, pauses,");
	ft_printf(" then repeats\n");
	ft_printf("    -v N\t: Verbosity levels, ");
	ft_printf("can be added together to enable several\n");
	ft_printf("\t\t\t- 0 : Show only essentials\n");
	ft_printf("\t\t\t- 1 : Show lives\n");
	ft_printf("\t\t\t- 2 : Show cycles\n");
	ft_printf("\t\t\t- 4 : Show operations ");
	ft_printf("(Params are NOT litteral ...)\n");
	ft_printf("\t\t\t- 8 : Show deaths\n");
	ft_printf("\t\t\t- 16 : Show PC movements (Except for jumps)\n");
	print_usage2();
}
