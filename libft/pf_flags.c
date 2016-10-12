/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:20:35 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:20:36 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	pf_flags_init(void)
{
	t_flags	ret;

	ret.conv = 0;
	ret.minus = 0;
	ret.plus = 0;
	ret.hash = 0;
	ret.zero = 0;
	ret.space = 0;
	ret.min_width = 0;
	ret.precision = -1;
	ret.hh = 0;
	ret.h = 0;
	ret.l = 0;
	ret.ll = 0;
	ret.j = 0;
	ret.z = 0;
	return (ret);
}

int		flag_is_number(t_flags flags)
{
	if (flags.conv == 'd' || flags.conv == 'u' || flags.conv == 'i'
		|| flags.conv == 'D' || flags.conv == 'O' || flags.conv == 'o'
		|| flags.conv == 'x' || flags.conv == 'X')
		return (1);
	else
		return (0);
}

int		flag_is_char(t_flags flags)
{
	if (flags.conv == 's' || flags.conv == 'S' || flags.conv == 'c'
		|| flags.conv == 'C' || flags.conv == '%')
		return (1);
	else
		return (0);
}
