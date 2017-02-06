/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_fn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:20:44 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:20:46 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_isanyof(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_wstrlen(wchar_t *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		ret += size_wchar(str[i]);
		i++;
	}
	return (ret);
}
