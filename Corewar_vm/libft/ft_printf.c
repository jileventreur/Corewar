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

int			ft_printf(const char *format, ...)
{
	va_list	args;

	g_buf = (t_buf){1, {0}, 0};
	g_char = &pf_putchar_buf;
	g_str = &pf_putstr_buf;
	g_end = &pf_putbuf;
	va_start(args, format);
	return (ft_general_print(format, &args));
}
