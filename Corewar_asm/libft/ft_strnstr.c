/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:15:25 by darabi            #+#    #+#             */
/*   Updated: 2015/12/03 16:38:30 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i1;
	size_t	i2;

	i1 = 0;
	i2 = 0;
	if (!s2[0])
		return ((char *)s1);
	while (s1[i1] && i1 < n)
	{
		while (s1[i1 + i2] == s2[i2] && s2[i2] && s1[i1 + i2] && (i1 + i2) < n)
			i2++;
		if (!s2[i2])
			return ((char *)s1 + i1);
		i1++;
		i2 = 0;
	}
	return (NULL);
}
