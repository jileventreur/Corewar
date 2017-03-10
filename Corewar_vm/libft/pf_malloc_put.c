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

static void	malloc_error(void)
{
	if (g_ret)
		free(g_ret);
	g_ret = NULL;
	return ;
}

void		pf_malloc_put(void)
{
	extern t_buf	g_buf;
	char			*tmp;
	int				ret_len;

	if (g_buf.len)
	{
		ret_len = g_ret ? ft_strlen(g_ret) : 0;
		if ((tmp = malloc(ret_len + g_buf.len + 1)) == NULL)
		{
			malloc_error();
			return ;
		}
		ft_bzero(tmp, ret_len + g_buf.len + 1);
		if (g_ret)
			ft_memcpy(tmp, g_ret, ret_len);
		ft_memcpy(tmp + ret_len, g_buf.buf, g_buf.len);
		tmp[ret_len + g_buf.len] = 0;
		free(g_ret);
		g_ret = tmp;
		g_buf.len = 0;
	}
}

void		pf_malloc_char(char c)
{
	extern t_buf	g_buf;

	if (g_buf.len == BUF_SIZE)
	{
		pf_malloc_put();
	}
	g_buf.buf[(g_buf.len)++] = c;
}

void		pf_malloc_str(char *str)
{
	extern t_buf	g_buf;
	int				str_len;
	int				ret_len;
	char			*tmp;

	str_len = ft_strlen(str);
	if (g_buf.len + str_len > BUF_SIZE)
	{
		ret_len = ft_strlen(g_ret);
		if ((tmp = malloc(str_len + ret_len + g_buf.len + 1)) == NULL)
			return (malloc_error());
		ft_bzero(tmp, str_len + ret_len + g_buf.len + 1);
		ft_memcpy(tmp, g_ret, ret_len);
		ft_memcpy(tmp + ret_len, g_buf.buf, g_buf.len);
		ft_memcpy(tmp + ret_len + g_buf.len, str, str_len);
		tmp[ret_len + g_buf.len + str_len] = 0;
		free(g_ret);
		g_ret = tmp;
		g_buf.len = 0;
	}
	else
	{
		ft_memcpy(g_buf.buf + g_buf.len, str, str_len);
		g_buf.len += str_len;
	}
}
