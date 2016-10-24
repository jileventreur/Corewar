/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 14:08:15 by darabi            #+#    #+#             */
/*   Updated: 2015/12/04 13:21:09 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(char const *s, char c, int start)
{
	int i;

	i = 0;
	while (s[start] && s[start] != c)
	{
		start++;
		i++;
	}
	return (i);
}

static int		ft_count_word(char const *s, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	if (s[i] != c && s[i])
		count++;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
	}
	return (count);
}

static char		*ft_partial_strcpy(char *s2, const char *s, int *i, char c)
{
	int j;

	j = 0;
	while (s[*i] != c && s[*i])
	{
		s2[j] = s[*i];
		(*i)++;
		j++;
	}
	s2[j] = '\0';
	return (s2);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		num;

	num = 0;
	i = 0;
	tab = (char **)malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (num < ft_count_word(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		tab[num] = (char *)malloc((ft_count(s, c, i) + 1) * sizeof(char));
		if (!tab[num])
			return (NULL);
		if (s[i] && s[i] != c)
			ft_strcpy(tab[num], ft_partial_strcpy(tab[num], s, &i, c));
		num++;
	}
	tab[num] = NULL;
	return (tab);
}
