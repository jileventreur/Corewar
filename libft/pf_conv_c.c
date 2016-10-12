/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:23:06 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:23:08 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_conv_c(va_list *args, t_flags flags)
{
	int		len;
	int		ret;
	char	c;

	if (flags.l)
		return (pf_conv_majc(args, flags));
	c = va_arg(*args, int);
	len = 1;
	ret = 0;
	pf_flag_min_width(flags, len, &ret, 0);
	ft_putchar(c);
	ret += len;
	pf_flag_min_width(flags, len, &ret, 1);
	return (ret);
}
