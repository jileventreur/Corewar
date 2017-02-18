/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 19:25:25 by darabi            #+#    #+#             */
/*   Updated: 2015/12/11 16:22:55 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		hexa_reg_check(char c, int value)
{
	if (c != '1')
		return (1);
	if (value >= 0 && value <= REG_NUMBER)
		return (1);
	exit_with_message("Problem with hexa REG");
	return (0);
}

int		good_return(int c, int mult)
{
	if (c >= '0' && c <= '9')
		return ((c - '0') * mult);
	if (c >= 'A' && c <= 'F')
		return ((c - 'A' + 10) * mult);
	if (c >= 'a' && c <= 'f')
		return ((c - 'a' + 10) * mult);
	exit_with_message("Bad character");
	return (0);
}

int		hexa_atoi(char *str)
{
	int count;
	int mult;
	int j;
	int i;

	i = 0;
	mult = 1;
	if (str[1] == '-' || str[i] == '+')
	{
		if (str[1] == '-')
			mult = -1;
		i = 1;
	}
	count = 0;
	j = ft_strlen(str) - 1;
	while (j != i)
	{
		count = good_return(str[j], mult) + count;
		mult = mult * 16;
		--j;
	}
	return (count);
}

int		check_arg_hexa(int j, char **cpy, t_content **list, int count)
{
	j = hexa_atoi(*cpy);
	hexa_reg_check((*list)->type[count], j);
	free(*cpy);
	return (j);
}
