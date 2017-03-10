/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 01:17:01 by cadam             #+#    #+#             */
/*   Updated: 2017/03/10 01:17:03 by cadam            ###   ########.fr       */
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
