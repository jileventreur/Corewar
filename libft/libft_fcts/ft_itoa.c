/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 11:34:47 by cadam             #+#    #+#             */
/*   Updated: 2015/04/04 11:49:13 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	l(int n, long int *res)
{
	int			len;
	long int	tmp;

	len = 0;
	*res = n;
	tmp = n;
	if (n < 0)
	{
		*res = *res * -1;
		tmp = -tmp;
		len = 1;
	}
	while (tmp / 10 >= 1)
	{
		tmp = tmp / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int			i;
	char		*ret;
	int			len;
	long int	res;

	len = l(n, &res);
	ret = (char *)malloc(sizeof(ret) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = (n < 0) ? 1 : 0;
	ret[0] = '-';
	while (len - i >= 0)
	{
		ret[i] = '0' + (res / ft_pow(10, len - i));
		res = res % ft_pow(10, len - i);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
