/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 11:41:13 by cadam             #+#    #+#             */
/*   Updated: 2015/04/04 11:51:12 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(s2);
	if (!s2[j])
		return ((char *)s1);
	while (s1[i] && j < len && i < (int)n)
	{
		if (s1[i] == s2[j])
			j++;
		i++;
	}
	if (j == len)
		return ((char *)s1 + i - j);
	return (NULL);
}
