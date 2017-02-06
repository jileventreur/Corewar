/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:09:34 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:09:36 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_conv_percent(va_list *args, t_flags flags)
{
	int len;
	int ret;

	(void)args;
	len = 1;
	ret = 0;
	pf_flag_min_width(flags, len, &ret, 0);
	PUTCHAR('%');
	++ret;
	pf_flag_min_width(flags, len, &ret, 1);
	return (ret);
}
