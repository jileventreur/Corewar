/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_invalid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:08:31 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:08:34 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_conv_invalid(t_flags flags, char c)
{
	int		ret;

	ret = 0;
	flags.conv = '%';
	pf_flag_min_width(flags, 1, &ret, 0);
	if (c)
	{
		PUTCHAR(c);
		++ret;
	}
	pf_flag_min_width(flags, 1, &ret, 1);
	return (ret);
}
