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

void	print_usage(void)
{
	ft_printf("Usage: ../source/corewar [-d N -s N -v [0..31] | -g | -a] [-n] <champion1.cor> <...>\n");
	ft_printf("    -a        : Prints output from \"aff\"");
	ft_printf("(Default is to hide it)\n");
	ft_printf("#### TEXT OUTPUT MODE");
	ft_printf(" ##########################################################\n");
	ft_printf("    -d N      : Dumps memory after N cycles then exits\n");
	ft_printf("
	ft_printf("    -s N      : Runs N cycles, dumps memory, pauses, then repeats\n");
	ft_printf("    -v N      : Verbosity levels, can be added together to enable several\n");
	ft_printf("                - 0 : Show only essentials\n");
	ft_printf("                - 1 : Show lives\n");
	ft_printf("                - 2 : Show cycles\n");
	ft_printf("                - 4 : Show operations (Params are NOT litteral ...)\n");
	ft_printf("                - 8 : Show deaths\n");
	ft_printf("                - 16 : Show PC movements (Except for jumps)\n");

}
