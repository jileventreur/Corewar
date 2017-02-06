/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flag_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:10:25 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:10:26 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_flag_plus_len(t_flags flags, int *len, long nb)
{
	if (flags.plus && nb >= 0)
		(*len)++;
}

void	pf_flag_plus(t_flags flags, int *ret, long nb)
{
	(void)*ret;
	if (flags.plus && nb >= 0)
	{
		PUTCHAR('+');
	}
	else if (nb < 0)
	{
		PUTCHAR('-');
	}
}
