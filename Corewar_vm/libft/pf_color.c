/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:08:12 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:21:22 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_color	g_color[COLOR] =
{
	{ "0", "eoc" },
	{ "1", "bold" },
	{ "4", "underline" },
	{ "5", "blink" },
	{ "7", "highlight" },
	{ "30", "black" },
	{ "31", "red" },
	{ "32", "green" },
	{ "33", "yellow" },
	{ "34", "blue" },
	{ "35", "pink" },
	{ "36", "cyan" },
	{ "37", "grey" },
	{ "37", "gray" },
	{ "40", "bgblack" },
	{ "41", "bgred" },
	{ "42", "bggreen" },
	{ "43", "bgyellow" },
	{ "44", "bgblue" },
	{ "45", "bgpink" },
	{ "46", "bgcyan" },
	{ "47", "bggrey" },
	{ "47", "bggray" }
};

int		pf_is_color(char *color, int *ret)
{
	int	i;

	i = 0;
	while (g_color[i].name)
	{
		if (!ft_strcmp(g_color[i].name, color))
		{
			pf_putstr("\033[", ret);
			pf_putstr(g_color[i].id, ret);
			pf_putstr("m", ret);
			return (1);
		}
		i++;
	}
	return (0);
}

int		pf_color(const char *format, int *pos, int *ret)
{
	int		i;
	int		len;
	char	*color;

	i = *pos;
	len = 0;
	color = NULL;
	while (format[i] && !color)
	{
		if (format[i] == '}')
		{
			color = ft_strsub(format, *pos, len);
		}
		len++;
		i++;
	}
	if (color && pf_is_color(color, ret))
	{
		*pos += len - 1;
		free(color);
		return (1);
	}
	else
		(*pos)--;
	return (0);
}
