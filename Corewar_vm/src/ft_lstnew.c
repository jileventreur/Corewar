/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbauguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 17:25:57 by vbauguen          #+#    #+#             */
/*   Updated: 2015/12/03 17:25:59 by vbauguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new;

	if ((new = (t_list *)malloc(sizeof(t_list))) == NULL)
	{
		ft_error_exit("Error: allocation error\n");
		return (NULL);
	}
	if (content)
	{
		if (!(new->content = malloc(content_size)))
		{
			free(new);
			ft_error_exit("Error: allocation error\n");
			return (NULL);
		}
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	new->next = NULL;
	return (new);
}
