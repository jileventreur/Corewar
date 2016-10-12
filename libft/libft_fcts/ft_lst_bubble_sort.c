/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstbbsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 20:20:35 by cadam             #+#    #+#             */
/*   Updated: 2015/10/12 19:58:46 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_structswap(t_list *prev, t_list *current)
{
	t_list	*next;

	next = current->next;
	if (prev)
		prev->next = next;
	current->next = next->next;
	next->next = current;
}

t_list			*ft_lst_bubble_sort(t_list *begin, t_cmp cmp)
{
	t_list	*prev;
	t_list	*current;

	if (!begin || !begin->next)
		return (begin);
	prev = NULL;
	current = begin;
	while (current->next)
	{
		if (cmp(current, current->next))
		{
			if (current == begin)
				begin = current->next;
			ft_structswap(prev, current);
			prev = NULL;
			current = begin;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return (begin);
}
