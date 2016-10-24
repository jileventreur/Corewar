/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 13:56:04 by darabi            #+#    #+#             */
/*   Updated: 2015/12/11 19:13:04 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_size(char const *s)
{
	int i;
	int j;
	int count;

	j = 0;
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (s[i])
	{
		if (s[i - 1] != ' ' && s[i - 1] != '\n' && s[i - 1] != '\t')
			count = j;
		i++;
		j++;
	}
	return (count);
}

char			*ft_strtrim(char const *s)
{
	char	*cpy;
	int		i;
	int		i2;
	int		temp;

	temp = 0;
	i = 0;
	i2 = 0;
	cpy = (char *)malloc((ft_size(s) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while ((s[i2] == ' ' || s[i2] == '\n' || s[i2] == '\t') && s[i2])
		i2++;
	while (s[i2])
	{
		cpy[i] = s[i2];
		i2++;
		i++;
		if (s[i2 - 1] != '\n' && s[i2 - 1] != ' ' && s[i2 - 1] != '\t')
			temp = i;
	}
	cpy[temp] = '\0';
	return (cpy);
}
