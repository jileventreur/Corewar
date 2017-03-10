/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 21:20:50 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 21:20:51 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			ft_round(double nb)
{
	return (nb < 0 ? (int)(nb - 0.5) : (int)(nb + 0.5));
}

static void	introducing_contestants(t_champion *c)
{
	int		i;

	i = -1;
	ft_printf("Introducing contestants...\n");
	while (++i < MAX_PLAYERS)
	{
		if (ft_memisset(&c[i], sizeof(t_champion), 0))
			continue ;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		c[i].num, c[i].header.prog_size,
		c[i].header.prog_name, c[i].header.comment);
	}
}

int			main(int argc, char **argv)
{
	t_vm	vm;

	if (argc == 1)
		ft_error_exit("Error: not enough args (use -h to see usage)\n");
	--argc;
	++argv;
	vm_init(&vm, argc, argv);
	introducing_contestants(vm.c);
	if (vm.opt.g || vm.opt.s)
		nprint_vm(&vm);
	else
		exec_vm(&vm);
	return (0);
}
