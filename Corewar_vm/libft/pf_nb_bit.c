/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nb_bit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:20:59 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:21:01 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	activ_bit(unsigned int *data, unsigned int bit)
{
	if (bit <= sizeof(data) * 8)
		*data = *data | (unsigned int)(1 * ft_pow(2, bit));
}

void	desactiv_bit(unsigned int *data, unsigned int bit)
{
	if (bit <= sizeof(data) * 8)
	{
		activ_bit(data, bit);
		*data = *data ^ (unsigned int)(1 * ft_pow(2, bit));
	}
}

int		bit_isactiv(unsigned int data, unsigned int bit)
{
	if (((data >> bit) & 1) == 1)
		return (1);
	return (0);
}

void	ft_putbasechar(char nb, unsigned int opt)
{
	if (nb <= 9)
		ft_putchar(nb + '0');
	else if (bit_isactiv(opt, 0))
		ft_putchar(nb - 10 + 'A');
	else
		ft_putchar(nb - 10 + 'a');
}
