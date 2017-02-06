/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flag_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:10:13 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:10:15 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_flag_hash(t_flags flags, int *ret, int nb)
{
	if (flags.hash)
	{
		if ((flags.conv == 'X' || flags.conv == 'x') && nb != 0)
		{
			PUTSTR(flags.conv == 'X' ? "0X" : "0x");
			(*ret) += 2;
			return (2);
		}
		else if (flags.conv == 'o' || flags.conv == 'O')
		{
			if (nb != 0 || (flags.precision > -1 && !flags.min_width
				&& nb == 0))
			{
				PUTCHAR('0');
				return (1);
			}
		}
	}
	return (0);
}
