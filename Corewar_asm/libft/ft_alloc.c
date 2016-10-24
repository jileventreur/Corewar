/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:43:59 by darabi            #+#    #+#             */
/*   Updated: 2015/12/04 14:22:14 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_strlen_to(const char *format, int *i)
{
	int j;

	j = *i;
	while (format[j] && format[j] != '%')
		j++;
	return (j - *i);
}

void			add_char(wchar_t **str, const char *format, int *i, int count)
{
	int j;
	int h;

	j = 0;
	h = 0;
	while (count >= h)
	{
		if (!(*str)[j])
			h++;
		j++;
	}
	j--;
	while (format[*i] != '%' && format[*i])
	{
		(*str)[j++] = format[*i];
		++*i;
	}
	(*str)[j] = '\0';
}

wchar_t			*changing_malloc(wchar_t **str, const char *format, \
				int *i, int count)
{
	wchar_t *cpy;
	int		j;

	j = 0;
	cpy = (wchar_t *)malloc((ft_strlen_null(*str, count) +\
		ft_strlen_to(format, i) + 1) * sizeof(wchar_t));
	if (!cpy)
		exit(0);
	while (j < ft_strlen_null(*str, count) +\
		ft_strlen_to(format, i) + 1)
		cpy[j++] = '\0';
	if (*str)
	{
		ft_strcpy_null(&cpy, *str, count);
		free(*str);
		*str = NULL;
	}
	add_char(&cpy, format, i, count);
	return (cpy);
}

wchar_t			*null_add_arg(wchar_t **str, wchar_t **arg, int count)
{
	int		j;
	int		h;
	wchar_t *cpy;

	cpy = (wchar_t *)malloc((ft_strlen_null(*str, count)\
		+ ft_strlen_null(*arg, 1) + 1) * sizeof(wchar_t));
	if (!cpy)
		exit(0);
	j = 0;
	h = 0;
	while (j <= count)
	{
		if ((*str)[h] == '\0')
			j++;
		cpy[h] = (*str)[h];
		h++;
	}
	j = 1;
	h--;
	while ((*arg)[j] != '\0')
		cpy[h++] = (*arg)[j++];
	cpy[h++] = '\0';
	cpy[h] = '\0';
	ft_del_str(str, arg);
	return (cpy);
}

wchar_t			*add_arg(wchar_t **str, wchar_t **arg, char a, int *count)
{
	wchar_t *cpy;
	int		h;
	int		j;
	int		c;

	initialize_three(&h, &j, &c);
	if (!*arg)
		return (*str);
	if (!(*arg)[0] && (a == 'c' || a == 'C'))
		return (null_add_arg(str, arg, (*count - 1)));
	cpy = (wchar_t *)malloc((ft_strlen_null(*str, *count)\
		+ ft_strlen_null(*arg, 0) + 1) * sizeof(wchar_t));
	while (c <= *count)
	{
		if ((*str)[h] == '\0')
			c++;
		cpy[h] = (*str)[h];
		h++;
	}
	h--;
	while ((*arg)[j] != '\0')
		cpy[h++] = (*arg)[j++];
	cpy[h] = '\0';
	ft_del_str(str, arg);
	return (cpy);
}
