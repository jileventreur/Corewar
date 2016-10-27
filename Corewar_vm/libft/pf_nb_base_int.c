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

void	print_base_int(unsigned int nb, unsigned int base, unsigned int opt)
{
	if (bit_isactiv(opt, 1) && (int)nb < 0)
		nb = (unsigned int)((int)(nb * -1));
	if (nb < base)
	{
		ft_putbasechar(nb, opt);
		return ;
	}
	print_base_int(nb / base, base, opt);
	nb = nb % base;
	ft_putbasechar(nb, opt);
	return ;
}

int		len_base_int(unsigned int nb, unsigned int base, int cpt,
	unsigned int opt)
{
	if (bit_isactiv(opt, 1) && (int)nb < 0)
		nb = (unsigned int)((int)(nb * -1));
	if (nb < base)
		return (cpt + 1);
	cpt = len_base_int(nb / base, base, cpt, opt);
	return (cpt + 1);
}
