/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epurspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 14:08:19 by cadam             #+#    #+#             */
/*   Updated: 2015/10/09 14:08:21 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_letter(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			j++;
		while (ft_isspace(str[i]))
			i++;
		while (str[i] && !ft_isspace(str[i]))
		{
			j++;
			i++;
		}
	}
	return (j);
}

char			*ft_epurspace(char *str)
{
	char	*res;
	int		i;
	int		j;

	str = ft_strtrim(str);
	i = 0;
	j = 0;
	if (!(res = (char *)malloc(sizeof(char) * (count_letter(str) + 1))))
		return (NULL);
	while (str[i])
	{
		if (ft_isspace(str[i]))
			res[j++] = ' ';
		while (ft_isspace(str[i]))
			i++;
		while (str[i] && !ft_isspace(str[i]))
			res[j++] = str[i++];
	}
	res[j] = 0;
	free(str);
	return (res);
}
