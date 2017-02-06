/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:10:04 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:10:05 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	min_width(t_flags flags, int len, unsigned int nb, int *ret)
{
	int		i;
	char	c;

	i = flags.min_width - (len + ((flags.hash && nb > 0) ? 2 : 0));
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

static int	len_prec(t_flags flags, int *nb_len, unsigned int nb)
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

static void	before_precision(t_flags flags, int *ret, int len_prc,
	unsigned int nb)
{
	if (flags.zero && !flags.minus && flags.precision == -1 && flags.hash
		&& nb > 0)
	{
		PUTSTR("0x");
		*ret += 2;
	}
	if (!flags.minus)
		min_width(flags, len_prc, nb, ret);
	if (!(flags.zero && !flags.minus && flags.precision == -1) && flags.hash
		&& nb > 0)
	{
		PUTSTR("0x");
		*ret += 2;
	}
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

int			pf_conv_x(va_list *args, t_flags flags)
{
	int				len;
	int				len_prc;
	int				ret;
	unsigned int	nb;

	if (flags.l || flags.ll || flags.j || flags.z)
		return (pf_conv_xl(args, flags));
	nb = va_arg(*args, unsigned int);
	if (flags.hh)
		nb = (unsigned char)nb;
	if (flags.h)
		nb = (unsigned short int)nb;
	len = len_base_int(nb, 16, 0, 0);
	len_prc = len_prec(flags, &len, nb);
	ret = 0;
	before_precision(flags, &ret, len_prc, nb);
	precision(flags, len, &ret);
	if (len)
		print_base_int(nb, 16, 0);
	ret += len;
	if (flags.minus)
		min_width(flags, len_prc, nb, &ret);
	return (ret);
}
