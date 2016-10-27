/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsupchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 20:20:57 by cadam             #+#    #+#             */
/*   Updated: 2015/04/11 20:20:59 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countchar(char *str, char c)
{
	int i;
	int cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (str[i] == c)
			cpt++;
		i++;
	}
	return (cpt);
}

char		*ft_strsupchar(char *str, char c)
{
	int		i;
	int		j;
	char	*newstr;

	newstr = (char *)malloc(sizeof(char) * (ft_strlen(str) -\
		ft_countchar(str, c) + 1));
	if (newstr == NULL)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			newstr[j] = str[i];
			i++;
			j++;
		}
	}
	newstr[j] = '\0';
	return (newstr);
}
