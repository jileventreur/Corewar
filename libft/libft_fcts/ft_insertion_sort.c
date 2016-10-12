/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/01 17:22:51 by cadam             #+#    #+#             */
/*   Updated: 2015/09/01 17:22:54 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_selection_sort(int **tab, int len)
{
	int		i;
	int		j;
	int		key;

	i = 1;
	while (i < len)
	{
		key = (*tab)[i];
		j = i - 1;
		while (j >= 0 && (*tab)[j] > key)
		{
			(*tab)[j + 1] = (*tab)[j];
			j--;
		}
		(*tab)[j + 1] = key;
		i++;
	}
}
