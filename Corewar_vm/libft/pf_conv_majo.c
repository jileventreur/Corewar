/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_majo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:08:47 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:08:49 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		min_width(t_flags flags, t_len lens, int *ret, unsigned long nb)
{
	int		i;
	char	c;

	i = flags.min_width - lens.len;
	if (flags.hash && (lens.len == lens.old_len || lens.len == 0)
		&& (nb != 0 || (nb == 0 && flags.precision == 0)))
		i--;
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

static int		len_prec(t_flags flags, int *nb_len, unsigned long nb)
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

static void		precision(t_flags flags, int len, unsigned long nb, int *ret)
{
	int i;

	if (flags.precision > -1)
	{
		i = flags.precision - len - ((nb != 0) ? flags.hash : 0);
		while (i > 0)
		{
			PUTCHAR('0');
			++(*ret);
			i--;
		}
	}
}

int				pf_conv_majo(va_list *args, t_flags flags)
{
	int				len;
	int				len_prc;
	int				ret;
	unsigned long	nb;
	t_len			lens;

	nb = va_arg(*args, unsigned long);
	len = len_base_long(nb, 8, 0, 0);
	lens.old_len = len;
	len_prc = len_prec(flags, &len, nb);
	lens.len = len_prc;
	ret = 0;
	if (!flags.minus)
		min_width(flags, lens, &ret, nb);
	precision(flags, len, nb, &ret);
	if (flags.hash && (nb != 0 || (nb == 0 && flags.precision == 0)))
	{
		PUTCHAR('0');
		++(ret);
	}
	if (len)
		print_base_long(nb, 8, 0);
	if (flags.minus)
		min_width(flags, lens, &ret, nb);
	return (ret += len);
}
