/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/01 12:12:53 by cadam             #+#    #+#             */
/*   Updated: 2015/10/28 20:35:11 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int		*cpytab(long int *tab, long int len)
{
	long int	*cpy;
	long int	i;

	if (!(cpy = (long int *)malloc(sizeof(long int) * len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = tab[i];
		i++;
	}
	cpy[i] = (long int)(INT_MAX) + 1;
	return (cpy);
}

static void			merge(long int **tab, long int p, long int q, long int r)
{
	long int	i;
	long int	j;
	long int	k;
	long int	*tmp1;
	long int	*tmp2;

	i = 0;
	j = 0;
	k = p;
	tmp1 = cpytab(&((*tab)[p]), q - p + 1);
	tmp2 = cpytab(&((*tab)[q + 1]), r - q);
	while (k <= r)
	{
		if (tmp1[i] <= tmp2[j])
			(*tab)[k] = tmp1[i++];
		else
			(*tab)[k] = tmp2[j++];
		k++;
	}
}

static void			mergesort2(long int **tab, long int p, long int r)
{
	long int	q;

	if (p >= r)
		return ;
	q = (p + r) / 2;
	mergesort2(tab, p, q);
	mergesort2(tab, q + 1, r);
	merge(tab, p, q, r);
}

void				ft_merge_sort(int **tab, int len)
{
	int			i;
	long int	*cpy;

	if (tab == NULL || (*tab) == NULL || len < 1)
		return ;
	if (!(cpy = (long int *)malloc(sizeof(long int) * len)))
		return ;
	i = 0;
	while (i < len)
	{
		cpy[i] = (*tab)[i];
		i++;
	}
	mergesort2(&cpy, 0, len - 1);
	i = 0;
	while (i < len)
	{
		(*tab)[i] = (int)(cpy[i]);
		i++;
	}
}
