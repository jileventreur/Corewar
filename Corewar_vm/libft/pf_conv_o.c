/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:09:21 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:09:23 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	min_width(t_flags flags, t_len lens, int *ret, unsigned int nb)
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

static void	precision(t_flags flags, int len, unsigned int nb, int *ret)
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

static void	and_other(t_flags flags, int *ret, t_len lens, unsigned int nb)
{
	if (!flags.minus)
		min_width(flags, lens, ret, nb);
	precision(flags, lens.old_len, nb, ret);
	if (flags.hash && (nb != 0 || (nb == 0 && flags.precision == 0)))
	{
		PUTCHAR('0');
		++(*ret);
	}
}

int			pf_conv_o(va_list *args, t_flags flags)
{
	int				len;
	int				len_prc;
	int				ret;
	unsigned int	nb;
	t_len			lens;

	if (flags.l || flags.ll || flags.j || flags.z)
		return (pf_conv_majo(args, flags));
	nb = va_arg(*args, unsigned int);
	if (flags.hh)
		nb = (unsigned char)nb;
	if (flags.h)
		nb = (unsigned short int)nb;
	len = len_base_int(nb, 8, 0, 0);
	lens.old_len = len;
	len_prc = len_prec(flags, &len, nb);
	lens.len = len_prc;
	ret = 0;
	and_other(flags, &ret, lens, nb);
	if (len)
		print_base_int(nb, 8, 0);
	ret += len;
	if (flags.minus)
		min_width(flags, lens, &ret, nb);
	return (ret);
}
