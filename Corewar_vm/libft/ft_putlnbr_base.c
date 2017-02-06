/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 07:49:11 by cadam             #+#    #+#             */
/*   Updated: 2016/12/11 07:49:16 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	decimal(unsigned long int nb, char *str)
{
	long int	snb;
	int			i;

	i = 0;
	if (nb > LONG_MAX)
	{
		str[i++] = '0' + (nb % 10);
		snb = nb / 10;
	}
	else
		snb = nb;
	while (snb)
	{
		str[i++] = '0' + (snb % 10);
		snb /= 10;
	}
	return (i);
}

static int	octal(unsigned long int nb, char *str)
{
	int i;

	i = 0;
	while (nb)
	{
		str[i++] = '0' + (nb & 7);
		nb >>= 3;
	}
	return (i);
}

static int	binary(unsigned long int nb, char *str)
{
	int i;

	i = 0;
	while (nb)
	{
		str[i++] = '0' + (nb & 1);
		nb >>= 1;
	}
	return (i);
}

static int	hexadecimal(unsigned long int nb, char *str, const char *digits)
{
	int i;

	i = 0;
	while (nb)
	{
		str[i++] = digits[(nb & 15)];
		nb >>= 4;
	}
	return (i);
}

void		ft_putlnbr_base(unsigned long int nb,
			const unsigned int base, const char *digits)
{
	char			str[sizeof(long int) * 8 + 1];
	int				i;

	if (nb < 10)
	{
		PUTCHAR('0' + (char)nb);
		return ;
	}
	if (base == 10)
		i = decimal(nb, str);
	else if (base == 16)
		i = hexadecimal(nb, str, digits);
	else if (base == 2)
		i = binary(nb, str);
	else if (base == 8)
		i = octal(nb, str);
	else
		return ;
	while (i > 0)
	{
		PUTCHAR(str[--i]);
	}
}
