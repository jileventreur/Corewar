/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 19:25:25 by darabi            #+#    #+#             */
/*   Updated: 2015/12/11 16:22:55 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		rmvchar(char *str)
{
	int i;

	i = 1;
	while (str[i - 1])
	{
		str[i - 1] = str[i];
		++i;
	}
}

char		*allocate_new(char *str, int nb)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (nb == 1)
		new_str = ft_strnew(PROG_NAME_LENGTH + 1);
	else
		new_str = ft_strnew(COMMENT_LENGTH + 1);
	while (str[i] && str[i] != '\"')
		++i;
	++i;
	while (str[i] && str[i] != '\"')
	{
		new_str[j] = str[i];
		++i;
		++j;
	}
	return (new_str);
}

t_content	*check_this_line(char *str, int i)
{
	if (check_blank_line(str))
		return (NULL);
	return (check_instruct(str, i, 0));
	return (NULL);
}
