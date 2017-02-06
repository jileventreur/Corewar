/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flag_min_width.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:10:17 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:10:19 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	pf_flag_calc_nb(t_flags flags, int len)
{
	int	nb;

	if (!flags.minus)
		nb = flags.min_width - len;
	else
		nb = flags.min_width;
	return (nb);
}

static void	ma_bite(t_flags flags, int write)
{
	if (flags.precision > -1 && flag_is_number(flags))
	{
		PUTCHAR(' ');
	}
	else
	{
		PUTCHAR((flags.zero && !write) ? '0' : ' ');
	}
}

void		pf_flag_min_width(t_flags flags, int len, int *ret, int write)
{
	int	i;
	int nb;

	if (!write && flags.minus)
		return ;
	i = *ret;
	if (flags.precision > -1 && flags.precision > len && !flag_is_char(flags))
		len = flags.precision;
	if (flags.precision > -1 && flags.precision < len
		&& (flags.conv == 's' || flags.conv == 'S'))
		len = flags.precision;
	if (flags.precision > -1 && flags.precision + 2 > len + 2
		&& (flags.conv == 'p'))
		len = flags.precision + 2;
	nb = pf_flag_calc_nb(flags, len);
	while (i < nb)
	{
		ma_bite(flags, write);
		(*ret)++;
		i++;
	}
}
