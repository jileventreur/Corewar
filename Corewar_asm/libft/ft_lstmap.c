/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 15:11:52 by darabi            #+#    #+#             */
/*   Updated: 2015/12/11 18:01:02 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*prev;
	t_list	*begin;

	if (!(new = ft_lstnew((f(lst))->content, (f(lst))->content_size)))
		return (NULL);
	new = f(lst);
	lst = lst->next;
	prev = new;
	begin = NULL;
	while (lst)
	{
		if (!(new = ft_lstnew(f((lst))->content, f((lst))->content_size)))
			return (NULL);
		new = f(lst);
		prev->next = new;
		if (!begin)
			begin = prev;
		prev = new;
		lst = lst->next;
	}
	new->next = NULL;
	return (begin);
}
