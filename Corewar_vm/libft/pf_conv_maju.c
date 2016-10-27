/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_maju.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:08:58 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:09:00 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_conv_maju(va_list *args, t_flags flags)
{
	int		len;
	int		ret;
	long	nb;

	nb = va_arg(*args, long);
	len = len_base_long(nb, 10, 0, 0);
	ret = 0;
	pf_flag_min_width(flags, len, &ret, 0);
	print_base_long(nb, 10, 0);
	ret += len;
	pf_flag_min_width(flags, len, &ret, 1);
	return (ret);
}
