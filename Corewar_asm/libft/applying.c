/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   applying.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 19:39:50 by darabi            #+#    #+#             */
/*   Updated: 2016/02/22 19:41:02 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static wchar_t	*plus_conversion(wchar_t **arg, char letter)
{
	int		i;
	int		j;
	wchar_t *cpy;

	i = 0;
	j = 0;
	if (letter != 'd' && letter != 'i')
		return (*arg);
	if ((*arg)[i] != '-')
	{
		cpy = malloc((ft_strlen_null(*arg, 0) + 2) * sizeof(wchar_t));
		if (!cpy)
			exit(0);
		cpy[i] = '+';
		i++;
		while ((*arg)[j])
			cpy[i++] = (*arg)[j++];
		cpy[i] = '\0';
		free(*arg);
		return (cpy);
	}
	return (*arg);
}

static wchar_t	*space_conversion(wchar_t **arg, char letter)
{
	int		i;
	int		j;
	wchar_t	*cpy;

	i = 0;
	j = 0;
	if (letter != 'd' && letter != 'i')
		return (*arg);
	if ((*arg)[i] != '-')
	{
		cpy = malloc((ft_strlen_null(*arg, 0) + 2) * sizeof(wchar_t));
		if (!cpy)
			exit(0);
		cpy[i] = ' ';
		i++;
		while ((*arg)[j])
			cpy[i++] = (*arg)[j++];
		cpy[i] = '\0';
		free(*arg);
		return (cpy);
	}
	return (*arg);
}

static wchar_t	*minus_wchar(wchar_t **arg, int width)
{
	int		i;
	int		j;
	wchar_t	*cpy;

	j = 0;
	i = 0;
	if (width <= wstr_len(*arg))
		return (*arg);
	cpy = (wchar_t *)malloc((width + 1) * sizeof(wchar_t));
	if (!cpy)
		exit(0);
	while ((*arg)[i])
	{
		cpy[i] = (*arg)[i];
		i++;
	}
	while ((wstr_len(*arg) + j) < width)
	{
		j++;
		cpy[i++] = ' ';
	}
	cpy[i] = '\0';
	free(*arg);
	return (cpy);
}

static wchar_t	*minus_conversion(wchar_t **arg, int width, char letter)
{
	int		i;
	wchar_t	*cpy;

	i = 0;
	if (!(*arg)[0] && (letter == 'c' || letter == 'C'))
		width--;
	if (letter == 'S')
		return (minus_wchar(arg, width));
	if (ft_strlen_null(*arg, i) >= width)
		return (*arg);
	cpy = (wchar_t *)malloc((width + 1) * sizeof(wchar_t));
	if (!cpy)
		exit(0);
	while ((*arg)[i])
	{
		cpy[i] = (*arg)[i];
		i++;
	}
	while (i < width)
		cpy[i++] = ' ';
	cpy[i] = '\0';
	free(*arg);
	return (cpy);
}

wchar_t			*applying_flags(wchar_t **arg, char *flags, \
				char letter, int width)
{
	int hash;

	if (((hash = checking_for_hashtag(flags)) == 1 &&\
	letter != 'c' && letter != 'C') || letter == 'p')
		*arg = hashtag_conversion(arg, letter);
	if (checking_for_plus(flags) == 1)
		*arg = plus_conversion(arg, letter);
	else if (checking_for_space(flags) == 1)
		*arg = space_conversion(arg, letter);
	if (checking_for_minus(flags, &width) == 1)
		*arg = minus_conversion(arg, width, letter);
	else if (checking_for_zero(flags) == 1)
	{
		*arg = zero_conversion(arg, width, letter, hash);
		if (checking_for_space(flags) == 1)
			*arg = space_conversion(arg, letter);
	}
	else
		*arg = minimal_width_applying(arg, width, letter);
	return (*arg);
}
