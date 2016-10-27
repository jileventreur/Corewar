/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:08:16 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:21:23 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conv	g_conv[CONV] =
{
	{ 's', &pf_conv_s },
	{ 'S', &pf_conv_majs },
	{ 'p', &pf_conv_p },
	{ 'd', &pf_conv_d },
	{ 'D', &pf_conv_majd },
	{ 'i', &pf_conv_d },
	{ 'o', &pf_conv_o },
	{ 'O', &pf_conv_majo },
	{ 'u', &pf_conv_u },
	{ 'U', &pf_conv_maju },
	{ 'x', &pf_conv_x },
	{ 'X', &pf_conv_majx },
	{ 'c', &pf_conv_c },
	{ 'C', &pf_conv_majc },
	{ '%', &pf_conv_percent },
	{ 'b', &pf_conv_b },
	{ 'B', &pf_conv_majb },
	{ 'r', &pf_conv_r }
};

int		pf_is_conv(char c)
{
	int	i;

	i = 0;
	while (g_conv[i].c)
	{
		if (g_conv[i].c == c)
			return (1);
		i++;
	}
	return (0);
}

int		pf_conv(va_list *args, const char *format, int *pos)
{
	int		i;
	char	c;
	int		ret;
	t_flags	flags;

	ret = 0;
	flags = pf_flags_init();
	while (format[*pos] && !pf_flags_check(args, &flags, format, pos))
		(*pos)++;
	c = format[*pos];
	if (!pf_is_conv(c))
		return (pf_conv_invalid(flags, c));
	flags.conv = c;
	i = 0;
	while (g_conv[i].c)
	{
		if (g_conv[i].c == c)
			ret += g_conv[i].pf_conv_exec(args, flags);
		i++;
	}
	return (ret);
}
