/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 19:39:50 by darabi            #+#    #+#             */
/*   Updated: 2016/02/22 19:41:02 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static wchar_t			*hashtag_octal_conv(wchar_t **arg)
{
	wchar_t *cpy;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if ((*arg)[0] == '0')
		return (*arg);
	cpy = (wchar_t *)malloc((ft_strlen_null(*arg, 0) + 2) * sizeof(wchar_t));
	cpy[i] = '0';
	i++;
	while ((*arg)[j])
		cpy[i++] = (*arg)[j++];
	cpy[i] = '\0';
	free(*arg);
	return (cpy);
}

wchar_t					*hashtag_conversion(wchar_t **arg, char letter)
{
	int		i;
	int		j;
	wchar_t *cpy;

	i = 0;
	j = 0;
	if (letter == 'o' || letter == 'O')
		return (hashtag_octal_conv(arg));
	else if (letter == 'x' || letter == 'X' || letter == 'p')
	{
		if (ft_watoi(*arg) == 0 && letter != 'p')
			return (*arg);
		cpy = malloc((ft_strlen_null(*arg, 0) + 3) * sizeof(wchar_t));
		cpy[i++] = '0';
		if (letter == 'x' || letter == 'p')
			cpy[i++] = 'x';
		else
			cpy[i++] = 'X';
		while ((*arg)[j])
			cpy[i++] = (*arg)[j++];
		cpy[i] = '\0';
		free(*arg);
		return (cpy);
	}
	return (*arg);
}
