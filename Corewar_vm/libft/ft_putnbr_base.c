/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 07:47:07 by cadam             #+#    #+#             */
/*   Updated: 2016/12/11 07:47:08 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	decimal(unsigned int nb, char *str)
{
	int	snb;
	int	i;

	i = 0;
	if (nb > INT_MAX)
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

static int	octal(unsigned int nb, char *str)
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

static int	binary(unsigned int nb, char *str)
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

static int	hexadecimal(unsigned int nb, char *str, const char *digits)
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

void		ft_putnbr_base(unsigned int nb,
			const unsigned int base, const char *digits)
{
	char			str[sizeof(int) * 8 + 1];
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
