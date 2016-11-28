/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:43:59 by darabi            #+#    #+#             */
/*   Updated: 2015/12/04 14:22:14 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_putwchar(wchar_t c)
{
	int		i;
	wchar_t	*str;

	str = ft_itoa_unsigned_ll(c, 2, 0);
	i = ft_strlen_null(str, 0);
	free(str);
	if (i <= 7)
		return (write(1, &c, 1));
	else if (i <= 11)
		return (mask_unicode_2(c));
	else if (i <= 16)
		return (mask_unicode_3(c));
	else if (i <= 21)
		return (mask_unicode_4(c));
	return (write(1, &c, 1));
}

int			ft_putwstr(wchar_t **str, int count)
{
	size_t	i;
	size_t	j;
	int		ret;

	i = 0;
	ret = 0;
	j = ft_strlen_null(*str, count);
	while (i < j)
	{
		ret = ft_putwchar((*str)[i]) + ret;
		i++;
	}
	free(*str);
	return (ret);
}

int			ft_strlen_null(wchar_t *str, int count)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (count >= j)
	{
		if (!str[i])
			j++;
		i++;
	}
	i--;
	return (i);
}

void		ft_strcpy_null(wchar_t **dst, wchar_t *src, int count)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (count >= j)
	{
		if (!src[i])
			j++;
		(*dst)[i] = src[i];
		i++;
	}
	i--;
	(*dst)[i] = '\0';
}
