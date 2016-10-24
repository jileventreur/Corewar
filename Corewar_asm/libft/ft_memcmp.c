/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:11:06 by darabi            #+#    #+#             */
/*   Updated: 2015/12/06 14:22:40 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && ((unsigned char*)s1)[i] == ((unsigned char*)s2)[i])
	{
		i++;
	}
	if (i == n)
		return (((unsigned char *)s1)[n - 1] - ((unsigned char *)s2)[n - 1]);
	return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}
