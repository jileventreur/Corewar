/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_majd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:08:43 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:08:45 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	min_width(t_flags flags, int len, long nb, int *ret)
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

static int	len_prec(t_flags flags, int *nb_len, long nb)
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

static void	sign_or_space(t_flags flags, long nb, int *ret)
{
	char	c;

	c = 0;
	if (nb < 0)
		c = '-';
	else if (flags.plus)
		c = '+';
	else if (flags.space)
		c = ' ';
	else
		return ;
	PUTCHAR(c);
	++(*ret);
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

int			pf_conv_majd(va_list *args, t_flags flags)
{
	int		len;
	int		len_prc;
	int		ret;
	long	nb;

	nb = va_arg(*args, long);
	len = len_base_long(nb, 10, 0, 2);
	len_prc = len_prec(flags, &len, nb);
	ret = 0;
	if (flags.zero && !flags.minus && flags.precision == -1)
		sign_or_space(flags, nb, &ret);
	if (!flags.minus)
		min_width(flags, len_prc, nb, &ret);
	if (!(flags.zero && !flags.minus && flags.precision == -1))
		sign_or_space(flags, nb, &ret);
	precision(flags, len, &ret);
	if (len)
		print_base_long(nb, 10, 2);
	ret += len;
	if (flags.minus)
		min_width(flags, len_prc, nb, &ret);
	return (ret);
}
