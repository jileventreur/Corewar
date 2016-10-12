/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/01 18:13:31 by cadam             #+#    #+#             */
/*   Updated: 2015/09/01 18:13:33 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_switch(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int		partition(int **tab, int p, int r)
{
	int q;
	int u;

	q = p;
	u = p;
	while (u < r)
	{
		if ((*tab)[u] <= (*tab)[r])
		{
			ft_switch(&(*tab)[q], &(*tab)[u]);
			q++;
		}
		u++;
	}
	ft_switch(&(*tab)[q], &(*tab)[u]);
	return (q);
}

static void		qsort2(int **tab, int p, int r)
{
	int q;

	if (p >= r)
		return ;
	q = partition(tab, p, r);
	qsort2(tab, p, q - 1);
	qsort2(tab, q + 1, r);
}

void			ft_quick_sort(int **tab, int len)
{
	if (tab == NULL || (*tab) == NULL || len < 1)
		return ;
	qsort2(tab, 0, len - 1);
}
