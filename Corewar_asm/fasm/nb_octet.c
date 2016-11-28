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

unsigned int		nb_octet(t_content *list)
{
	unsigned int i;
	unsigned int nb;

	i = 0;
	nb = 1;
	if (!list->type[0])
		return (0);
	if (list->instruct == 1)
		return (5);
	if (list->instruct == 12 || list->instruct == 9 ||\
	list->instruct == 1 || list->instruct == 15)
		;
	else
		++nb;
	while (list->type[i] && i != 3)
	{
		nb = nb + list->type[i] - '0';
		++i;
	}
	return (nb);
}
