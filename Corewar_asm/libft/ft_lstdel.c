/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 14:54:08 by darabi            #+#    #+#             */
/*   Updated: 2015/12/11 17:15:24 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		**new;
	t_list		**test;

	if (!alst)
		return ;
	new = alst;
	while (*new)
	{
		test = new;
		del((*new)->content, (*new)->content_size);
		free(*test);
		*new = (*new)->next;
	}
	ft_memdel((void **)alst);
}
