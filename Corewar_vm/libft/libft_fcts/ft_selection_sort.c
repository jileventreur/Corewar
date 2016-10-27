/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_selection_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/01 15:50:36 by cadam             #+#    #+#             */
/*   Updated: 2015/09/01 15:50:38 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_switch(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int			findmin(int *tab, int len)
{
	int		i;
	int		min;

	i = 0;
	min = 0;
	while (i < len)
	{
		if (tab[i] < tab[min])
			min = i;
		i++;
	}
	return (min);
}

void				ft_selection_sort(int **tab, int len)
{
	int		i;
	int		min;

	if (tab == NULL || (*tab) == NULL || len < 1)
		return ;
	i = 0;
	while (i < len)
	{
		min = findmin((&(*tab)[i]), len - i) + i;
		ft_switch((&(*tab)[i]), (&(*tab)[min]));
		i++;
	}
}
