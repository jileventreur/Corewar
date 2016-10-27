/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 14:25:20 by darabi            #+#    #+#             */
/*   Updated: 2015/12/04 19:04:54 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*test;

	test = (t_list *)malloc(1 * sizeof(t_list));
	if (!test)
		return (NULL);
	if (!content)
	{
		test->content = NULL;
		test->content_size = 0;
	}
	else
	{
		test->content = malloc(content_size * sizeof(char));
		if (!(test->content))
			return (NULL);
		ft_memmove(test->content, content, content_size);
	}
	test->next = NULL;
	return (test);
}
