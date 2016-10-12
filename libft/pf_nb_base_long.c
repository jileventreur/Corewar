/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nb_base_long.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:20:55 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:20:56 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_base_long(unsigned long nb, unsigned int base, unsigned int opt)
{
	if (bit_isactiv(opt, 1) && (long)nb < 0)
		nb = (unsigned long)((long)(nb * -1));
	if (nb < base)
	{
		ft_putbasechar(nb, opt);
		return ;
	}
	print_base_long(nb / base, base, opt);
	nb = nb % base;
	ft_putbasechar(nb, opt);
	return ;
}

int		len_base_long(unsigned long nb, unsigned int base, int cpt,
	unsigned int opt)
{
	if (bit_isactiv(opt, 1) && (long)nb < 0)
		nb = (unsigned long)((long)(nb * -1));
	if (nb < base)
		return (cpt + 1);
	cpt = len_base_long(nb / base, base, cpt, opt);
	return (cpt + 1);
}
