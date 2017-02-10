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

void		print_args(t_arg *args, unsigned int arg_number,
			unsigned char long_inst, unsigned char dest)
{
	unsigned int	i;

	i = 0;
	while (i < arg_number)
	{
		if ((unsigned int)args[i].type == NULL_CODE)
			ft_printf("NULL");
		if ((unsigned int)args[i].type == T_REG && i == dest)
			ft_printf("r%d", args[i].data);
		else if ((unsigned int)args[i].type == T_REG)
			ft_printf("%d", args[i].value);
		else if ((unsigned int)args[i].type == T_IND && long_inst)
		{
			ft_printf("%hd", (short int)args[i].value);
		}
		else if ((unsigned int)args[i].type == T_IND)
			ft_printf("%d", (int)args[i].value);
		else if (args[i].size == 2)
			ft_printf("%hd", (short int)args[i].value);
		else
			ft_printf("%d", args[i].value);
		++i;
		if (i < arg_number)
			ft_printf(" ");
	}
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
	if (vm.opt.g)
		nprint_vm(&vm);
	else
		exec_vm(&vm);
	return (0);
}
