/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_bonus_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:08:19 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:21:26 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_conv_b(va_list *args, t_flags flags)
{
	int	len;
	int	ret;
	int	nb;

	if (flags.l || flags.j || flags.z)
		return (pf_conv_majb(args, flags));
	nb = va_arg(*args, unsigned int);
	if (flags.precision > -1 && !flags.min_width && nb == 0)
		return (0);
	if (flags.hh)
		nb = (unsigned char)nb;
	len = len_base_int(nb, 2, 0, 0);
	ret = 0;
	print_base_int(nb, 2, 2);
	ret += len;
	return (ret);
}

int		pf_conv_majb(va_list *args, t_flags flags)
{
	int	len;
	int	ret;
	int	nb;

	nb = va_arg(*args, unsigned long);
	if (flags.precision > -1 && !flags.min_width && nb == 0)
		return (0);
	if (flags.hh)
		nb = (unsigned char)nb;
	len = len_base_long(nb, 2, 0, 0);
	ret = 0;
	print_base_long(nb, 2, 0);
	ret += len;
	return (ret);
}
