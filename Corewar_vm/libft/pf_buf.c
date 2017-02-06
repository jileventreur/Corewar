/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_buf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 07:52:46 by cadam             #+#    #+#             */
/*   Updated: 2016/12/11 07:52:49 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putbuf(void)
{
	extern t_buf	g_buf;

	if (g_buf.len)
	{
		write(g_buf.fd, g_buf.buf, g_buf.len);
		g_buf.len = 0;
	}
}

void	pf_putchar_buf(char c)
{
	extern t_buf	g_buf;

	if (g_buf.len == BUF_SIZE)
	{
		write(g_buf.fd, g_buf.buf, g_buf.len);
		g_buf.len = 0;
	}
	g_buf.buf[(g_buf.len)++] = c;
}

void	pf_putstr_buf(char *str)
{
	extern t_buf	g_buf;
	int				str_len;
	int				cut;

	str_len = ft_strlen(str);
	if (g_buf.len + str_len > BUF_SIZE)
	{
		cut = BUF_SIZE - g_buf.len;
		ft_memcpy(g_buf.buf + g_buf.len, str, cut);
		write(g_buf.fd, g_buf.buf, BUF_SIZE);
		g_buf.len = 0;
		str += cut;
		str_len -= cut;
	}
	while (str_len > BUF_SIZE)
	{
		write(1, str, BUF_SIZE);
		str += BUF_SIZE;
		str_len -= BUF_SIZE;
	}
	ft_memcpy(g_buf.buf + g_buf.len, str, str_len);
	g_buf.len += str_len;
}
