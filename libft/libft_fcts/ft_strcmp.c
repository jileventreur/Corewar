/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 11:39:13 by cadam             #+#    #+#             */
/*   Updated: 2015/04/04 11:50:38 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (((unsigned char *)s1)[i] && ((unsigned char *)s2)[i] &&
			((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
		return (-1);
	else if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
		return (1);
	else
		return (0);
}
