/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:09:59 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:10:01 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_conv_u(va_list *args, t_flags flags)
{
	int	len;
	int	ret;
	int	nb;

	if (flags.l || flags.j || flags.z)
		return (pf_conv_maju(args, flags));
	nb = va_arg(*args, unsigned int);
	if (flags.hh)
		nb = (unsigned char)nb;
	if (flags.h)
		nb = (unsigned short int)nb;
	len = (flags.precision != 0 || nb) ? len_base_int(nb, 10, 0, 0) : 0;
	ret = 0;
	pf_flag_min_width(flags, len, &ret, 0);
	pf_flag_precision(flags, len, nb, &ret);
	if (flags.precision != 0 || nb)
		print_base_int(nb, 10, 0);
	ret += len;
	pf_flag_min_width(flags, len, &ret, 1);
	return (ret);
}
