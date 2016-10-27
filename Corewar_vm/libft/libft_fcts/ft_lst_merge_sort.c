/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_merge_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/15 14:05:44 by cadam             #+#    #+#             */
/*   Updated: 2015/10/15 15:51:19 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*sorted_merge(t_list *a, t_list *b, t_cmp cmp)
{
	if (!a && !b)
		return (NULL);
	if (!a || !b)
		return ((a) ? a : b);
	if ((*cmp)(a, b))
	{
		a->next = sorted_merge(a->next, b, cmp);
		return (a);
	}
	b->next = sorted_merge(a, b->next, cmp);
	return (b);
}

static void		ft_lsthalfsplit(t_list *source, t_list **part1, t_list **part2)
{
	t_list	*slow;
	t_list	*fast;

	*part1 = (!source) ? NULL : source;
	if (!source || !source->next)
	{
		*part2 = NULL;
		return ;
	}
	fast = source->next;
	slow = source;
	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	*part2 = slow->next;
	slow->next = NULL;
}

t_list			*ft_lst_merge_sort(t_list *lst, t_cmp cmp)
{
	t_list *a;
	t_list *b;

	if (!lst || !lst->next)
		return (lst);
	ft_lsthalfsplit(lst, &a, &b);
	a = ft_lst_merge_sort(a, cmp);
	b = ft_lst_merge_sort(b, cmp);
	return (sorted_merge(a, b, cmp));
}
