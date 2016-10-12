/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_nocase_cmp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:38:31 by cadam             #+#    #+#             */
/*   Updated: 2015/05/12 17:38:32 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_nocase_cmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (((unsigned char *)s1)[i] && ((unsigned char *)s2)[i] &&
			ft_tolower(((unsigned char *)s1)[i]) ==\
			ft_tolower(((unsigned char *)s2)[i]))
		i++;
	if (ft_tolower(((unsigned char *)s1)[i]) <\
	ft_tolower(((unsigned char *)s2)[i]))
		return (-1);
	else if (ft_tolower(((unsigned char *)s1)[i]) >\
	ft_tolower(((unsigned char *)s2)[i]))
		return (1);
	else
		return (0);
}
