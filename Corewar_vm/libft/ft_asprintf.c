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

int			ft_asprintf(char **ret, const char *format, ...)
{
	extern t_buf	g_buf;
	va_list			args;
	int				ret_value;

	g_buf = (t_buf){0, {0}, 0};
	g_char = &pf_malloc_char;
	g_str = &pf_malloc_str;
	g_end = &pf_malloc_put;
	g_ret = ft_strdup("");
	va_start(args, format);
	ret_value = ft_general_print(format, &args);
	*ret = g_ret;
	if (g_ret)
		return (ret_value);
	return (-1);
}
