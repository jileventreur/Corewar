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

int		is_it_good(char c, int mask)
{
	if (mask == 0 || !c)
		return (0);
	if (c == 'r' && (mask & T_REG))
		return (REG_SIZE);
	if (c == '%' && (mask & T_DIR))
		return (DIR_SIZE);
	if (c != 'r' && c != '%' && (mask & T_IND))
		return (IND_SIZE);
	return (-1);
}

char	update_octet(unsigned char octet, int j, char c, t_content **list)
{
	if (j > 0)
		octet = octet << 2;
	if (c == '%')
	{
		octet = octet + DIR_CODE;
		(*list)->type[j] = '0' + DIR_SIZE;
	}
	else if (c == 'r')
	{
		octet = octet + REG_CODE;
		(*list)->type[j] = '0' + T_REG;
	}
	else
	{
		octet = octet + IND_CODE;
		(*list)->type[j] = '0' + IND_SIZE;
	}
	(*list)->type[j + 1] = 0;
	return (octet);
}
