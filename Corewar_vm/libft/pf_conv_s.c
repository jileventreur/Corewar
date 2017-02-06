/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:09:55 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:09:57 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_conv_s_inside(t_flags flags, char *str, int len, int *ret)
{
	int	i;

	if (flags.precision > -1)
	{
		i = 0;
		while (str[i] && i < flags.precision)
		{
			PUTCHAR(str[i]);
			i++;
		}
		(*ret) += i;
	}
	else
	{
		PUTSTR(str);
		(*ret) += len;
	}
}

int			pf_conv_s(va_list *args, t_flags flags)
{
	char	*str;
	int		ret;
	int		len;

	if (flags.l)
		return (pf_conv_majs(args, flags));
	ret = 0;
	str = va_arg(*args, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	pf_flag_min_width(flags, len, &ret, 0);
	pf_conv_s_inside(flags, str, len, &ret);
	pf_flag_min_width(flags, len, &ret, 1);
	return (ret);
}
