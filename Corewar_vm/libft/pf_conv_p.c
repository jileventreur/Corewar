/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:09:26 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:09:28 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	min_width(t_flags flags, int len, int *ret)
{
	int		i;
	char	c;

	i = flags.min_width - (len + 2);
	if (flags.zero && !flags.minus && flags.precision == -1)
		c = '0';
	else
		c = ' ';
	while (i > 0)
	{
		PUTCHAR(c);
		++(*ret);
		i--;
	}
}

static int	len_prec(t_flags flags, int *nb_len, unsigned long nb)
{
	if (flags.precision == 0 && nb == 0)
	{
		*nb_len = 0;
		return (0);
	}
	if (flags.precision <= *nb_len)
		return (*nb_len);
	return (flags.precision);
}

static void	precision(t_flags flags, int len, int *ret)
{
	int i;

	if (flags.precision > -1)
	{
		i = flags.precision - len;
		while (i > 0)
		{
			PUTCHAR('0');
			++(*ret);
			i--;
		}
	}
}

static void	spec_putstr(char *str, int *ret)
{
	PUTSTR(str);
	*ret += 2;
}

int			pf_conv_p(va_list *args, t_flags flags)
{
	int				len;
	int				len_prc;
	int				ret;
	unsigned long	nb;

	nb = va_arg(*args, unsigned long);
	len = len_base_long(nb, 16, 0, 0);
	len_prc = len_prec(flags, &len, nb);
	ret = 0;
	if (flags.zero && !flags.minus && flags.precision == -1)
		spec_putstr("0x", &ret);
	if (!flags.minus)
		min_width(flags, len_prc, &ret);
	if (!(flags.zero && !flags.minus && flags.precision == -1))
		spec_putstr("0x", &ret);
	precision(flags, len, &ret);
	if (len)
		print_base_long(nb, 16, 0);
	ret += len;
	if (flags.minus)
		min_width(flags, len_prc, &ret);
	return (ret);
}
