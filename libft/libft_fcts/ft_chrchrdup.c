/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrchrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 14:07:41 by cadam             #+#    #+#             */
/*   Updated: 2015/10/09 14:07:42 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_chrchrdup(char **tab)
{
	int		i;
	char	**dup;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	if (!(dup = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	dup[i--] = NULL;
	while (i >= 0)
	{
		dup[i] = ft_strdup(tab[i]);
		i--;
	}
	return (dup);
}
