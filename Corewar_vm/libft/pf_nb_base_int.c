/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nb_base_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:20:49 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:20:51 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putbasechar(char nb, const unsigned int opt)
{
	if (nb <= 9)
	{
		PUTCHAR(nb + '0');
	}
	else if (ISACTIV(opt, 0))
	{
		PUTCHAR(nb - 10 + 'A');
	}
	else
	{
		PUTCHAR(nb - 10 + 'a');
	}
}

int		len_base_int(unsigned int nb, const unsigned int base, int cpt,
		const unsigned int opt)
{
	if (ISACTIV(opt, 1) && (int)nb < 0)
		nb = (unsigned int)((int)(nb * -1));
	if (nb < 9)
		return (1);
	cpt = 0;
	while (nb)
	{
		nb /= base;
		++cpt;
	}
	return (cpt);
}

void	print_base_int(unsigned int nb, const unsigned int base,
		const unsigned int opt)
{
	if (ISACTIV(opt, 1) && (int)nb < 0)
		nb = (unsigned int)((int)(nb * -1));
	if (base != 16)
		ft_putnbr_base(nb, base, NULL);
	else
		ft_putnbr_base(nb, base,
		ISACTIV(opt, 0) ? UPPER_HEX_DIGITS : LOWER_HEX_DIGITS);
	return ;
}

int		len_base_long(unsigned long nb, const unsigned int base, int cpt,
		const unsigned int opt)
{
	if (ISACTIV(opt, 1) && (long)nb < 0)
		nb = (unsigned long)((long)(nb * -1));
	if (nb < 9)
		return (1);
	cpt = 0;
	while (nb)
	{
		nb /= base;
		++cpt;
	}
	return (cpt);
}

void	print_base_long(unsigned long nb,
		const unsigned int base, const unsigned int opt)
{
	if (ISACTIV(opt, 1) && (long)nb < 0)
		nb = (unsigned long)((long)(nb * -1));
	if (base != 16)
		ft_putlnbr_base(nb, base, NULL);
	else
		ft_putlnbr_base(nb, base,
		ISACTIV(opt, 0) ? UPPER_HEX_DIGITS : LOWER_HEX_DIGITS);
	return ;
}
