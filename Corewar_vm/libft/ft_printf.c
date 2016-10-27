/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:07:16 by cadam             #+#    #+#             */
/*   Updated: 2015/10/09 17:52:27 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_inside(const char *format, int *i, int *ret)
{
	if (format[*i] == '{')
	{
		(*i)++;
		if (!format[*i])
		{
			pf_putchar('{', ret);
			return (1);
		}
		else if (!pf_color(format, i, ret))
			pf_putchar('{', ret);
	}
	else
		pf_putchar(format[*i], ret);
	return (0);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		ret;
	int		*n;

	va_start(args, format);
	ret = 0;
	i = 0;
	n = NULL;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!format[i])
				return (ret);
			if (!pf_conv_n(&args, format[i], n, ret))
				ret += pf_conv(&args, format, &i);
		}
		else if (ft_printf_inside(format, &i, &ret))
			return (ret);
		i++;
	}
	va_end(args);
	return (ret);
}
