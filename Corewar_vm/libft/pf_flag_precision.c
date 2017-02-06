/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flag_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:10:29 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:10:30 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_flag_precision_zero(t_flags flags)
{
	int i;
	int ret;

	ret = 0;
	if (flags.precision == 0 && flags.hash
		&& (flags.conv == 'o' || flags.conv == 'O'))
	{
		PUTCHAR('0');
		ret++;
	}
	else if (flags.hash)
	{
		i = 0;
		while (i < flags.precision)
		{
			PUTCHAR('0');
			ret++;
			i++;
		}
	}
	return (ret);
}

void	pf_flag_precision(t_flags flags, int len, int nb, int *ret)
{
	int i;

	if (flags.precision > -1)
	{
		if (flags.conv == 'd' || flags.conv == 'i' || flags.conv == 'D')
		{
			if (flags.plus || (nb < 0 && len - 1 < flags.precision))
			{
				PUTCHAR('0');
				(*ret)++;
			}
		}
		i = 0;
		while (i < flags.precision - len)
		{
			PUTCHAR('0');
			(*ret)++;
			i++;
		}
	}
}
