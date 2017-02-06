/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:08:27 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:08:28 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	min_width(t_flags flags, int len, int nb, int *ret)
{
	int		i;
	char	c;

	i = flags.min_width - len;
	if (flags.space || flags.plus || nb < 0)
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

static int	len_prec(t_flags flags, int *nb_len, int nb)
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

static void	sign_or_space(t_flags flags, int nb, int *ret)
{
	char	c;

	c = 0;
	if (nb < 0)
		c = '-';
	else if (flags.plus)
		c = '+';
	else if (flags.space)
		c = ' ';
	if (c)
	{
		PUTCHAR(c);
		++(*ret);
	}
}

static void	precision_and_other(t_flags flags, t_len lens, int nb, int *ret)
{
	int	i;

	if (flags.zero && !flags.minus && flags.precision == -1)
		sign_or_space(flags, nb, ret);
	if (!flags.minus)
		min_width(flags, lens.len, nb, ret);
	if (!(flags.zero && !flags.minus && flags.precision == -1))
		sign_or_space(flags, nb, ret);
	if (flags.precision > -1)
	{
		i = flags.precision - lens.old_len;
		while (i > 0)
		{
			PUTCHAR('0');
			++(*ret);
			i--;
		}
	}
}

int			pf_conv_d(va_list *args, t_flags flags)
{
	int		len;
	int		len_prc;
	int		ret;
	int		nb;
	t_len	lens;

	if (flags.l || flags.ll || flags.j || flags.z)
		return (pf_conv_majd(args, flags));
	nb = va_arg(*args, int);
	if (flags.hh)
		nb = (char)nb;
	if (flags.h)
		nb = (short int)nb;
	len = len_base_int(nb, 10, 0, 2);
	lens.old_len = len;
	len_prc = len_prec(flags, &len, nb);
	lens.len = len_prc;
	ret = 0;
	precision_and_other(flags, lens, nb, &ret);
	if (len)
		print_base_int(nb, 10, 2);
	ret += len;
	if (flags.minus)
		min_width(flags, len_prc, nb, &ret);
	return (ret);
}
