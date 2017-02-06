/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 20:51:33 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 20:51:35 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		dont_overflow(char *arg)
{
	long int			nb;
	int					sign;

	sign = 1;
	nb = 0;
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '+' || *arg == '-')
		sign = (*(arg++) == '-') ? -1 : 1;
	while (*arg && nb * sign <= INT_MAX && nb * sign >= INT_MIN)
	{
		nb = nb * 10 + *arg - '0';
		arg++;
	}
	return (nb * sign <= INT_MAX && nb * sign >= INT_MIN);
}

int				ft_strisint(char *arg)
{
	int i;

	i = 0;
	if (!arg[i])
		return (0);
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (dont_overflow(arg));
}
