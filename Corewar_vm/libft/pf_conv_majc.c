/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_majc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:08:37 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:08:39 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	nb_bits(unsigned int nb)
{
	int cpt;

	cpt = 0;
	while (nb != 0)
	{
		nb = nb >> 1;
		cpt++;
	}
	return (cpt);
}

int	two_oct(unsigned int a)
{
	unsigned int tmp;

	tmp = ((a >> 6) + 192);
	PUTCHAR(tmp);
	tmp = (a ^ ((tmp - 192) << 6)) + 128;
	PUTCHAR(tmp);
	return (2);
}

int	three_oct(unsigned int a)
{
	unsigned int tmp;

	tmp = (a >> 12) + 224;
	PUTCHAR(tmp);
	a = a ^ ((tmp - 224) << 12);
	tmp = (a >> 6) + 128;
	PUTCHAR(tmp);
	tmp = (a ^ ((tmp - 128) << 6)) + 128;
	PUTCHAR(tmp);
	return (3);
}

int	four_oct(unsigned int a)
{
	unsigned int tmp;

	tmp = (a >> 18) + 240;
	PUTCHAR(tmp);
	a = a ^ ((tmp - 240) << 18);
	tmp = (a >> 12) + 128;
	PUTCHAR(tmp);
	a = a ^ ((tmp - 128) << 12);
	tmp = (a >> 6) + 128;
	PUTCHAR(tmp);
	tmp = (a ^ ((tmp - 128) << 6)) + 128;
	PUTCHAR(tmp);
	return (4);
}

int	pf_conv_majc(va_list *args, t_flags flags)
{
	unsigned int	a;
	int				bits;
	int				ret;

	a = va_arg(*args, unsigned int);
	bits = size_wchar(a);
	ret = 0;
	pf_flag_min_width(flags, bits, &ret, 0);
	if (bits == 1)
		ret += write(1, &a, 1);
	else if (bits == 2)
		ret += two_oct(a);
	else if (bits == 3)
		ret += three_oct(a);
	else if (bits == 4)
		ret += four_oct(a);
	else
		return (-1);
	pf_flag_min_width(flags, bits, &ret, 1);
	return (ret);
}
