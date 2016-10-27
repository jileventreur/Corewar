/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/08 19:31:03 by cadam             #+#    #+#             */
/*   Updated: 2015/04/11 20:20:50 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_sqrt(float s)
{
	int		x;
	float	tmp;

	if (s == 0)
		return (0);
	x = 0;
	tmp = s / 2;
	while (x < 15)
	{
		tmp = 0.5 * (tmp + s / tmp);
		x++;
	}
	return (tmp);
}