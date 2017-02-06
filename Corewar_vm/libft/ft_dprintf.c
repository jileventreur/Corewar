/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:07:16 by cadam             #+#    #+#             */
/*   Updated: 2015/10/09 17:52:27 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_dprintf(int fd, const char *format, ...)
{
	extern t_buf	g_buf;
	va_list			args;

	g_buf = (t_buf){0, {0}, 0};
	g_char = &pf_putchar_buf;
	g_str = &pf_putstr_buf;
	g_end = &pf_putbuf;
	g_buf.fd = fd;
	va_start(args, format);
	return (ft_general_print(format, &args));
}
