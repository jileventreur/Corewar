/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_general_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 23:45:33 by cadam             #+#    #+#             */
/*   Updated: 2016/12/14 23:45:34 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_end(va_list *args, int ret)
{
	va_end(*args);
	END;
	return (ret);
}

int			ft_general_print(const char *format, va_list *args)
{
	int		i;
	int		ret;
	int		*n;

	ret = 0;
	i = -1;
	n = NULL;
	while (format[++i])
	{
		if (format[i] != '%')
		{
			PUTCHAR(format[i]);
			++(ret);
		}
		else
		{
			if (!format[++i])
				return (print_end(args, ret));
			if (!pf_conv_n(args, format[i], n, ret))
				ret += pf_conv(args, format, &i);
		}
	}
	return (print_end(args, ret));
}
