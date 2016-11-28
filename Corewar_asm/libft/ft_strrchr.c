/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:22:32 by darabi            #+#    #+#             */
/*   Updated: 2015/11/27 16:17:25 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int i;
	int nb;

	i = 0;
	nb = -1;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			nb = i;
		i++;
	}
	if (str[i] == (unsigned char)c)
		nb = i;
	if (nb != -1)
		return ((char *)(str + nb));
	else
		return (NULL);
}
