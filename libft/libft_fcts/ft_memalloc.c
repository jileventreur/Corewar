/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 11:36:10 by cadam             #+#    #+#             */
/*   Updated: 2015/04/04 11:49:49 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*ret;

	ret = (void *)malloc(size);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		((char *)ret)[i] = '\0';
		i++;
	}
	return ((void *)ret);
}
