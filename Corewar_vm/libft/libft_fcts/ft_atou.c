/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:43:59 by darabi            #+#    #+#             */
/*   Updated: 2015/12/04 14:22:14 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atou(const char *str)
{
	int				i;
	unsigned int	temp;
	unsigned int	nb;

	i = 0;
	temp = 0;
	nb = 0;
	if (!str)
		return (-1);
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r'\
	|| str[i] == '\v' || str[i] == '\f') && str[i])
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		nb = temp + str[i] - '0';
		temp = nb * 10;
		i++;
	}
	return (nb);
}
