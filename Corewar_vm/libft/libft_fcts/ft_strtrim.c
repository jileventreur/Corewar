/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/04 11:41:54 by cadam             #+#    #+#             */
/*   Updated: 2015/04/04 11:51:21 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_start(char const *s)
{
	int	i;
	int	start;

	i = 0;
	start = -1;
	while (s[i] && start == -1)
	{
		if (!(s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			start = i;
		i++;
	}
	if (start == -1)
		start = 0;
	return (start);
}

static int	ft_end(char const *s, int start)
{
	int	end;
	int	len;

	end = -1;
	len = ft_strlen(s) - 1;
	while (s[len] && end == -1)
	{
		if (!(s[len] == ' ' || s[len] == '\n' || s[len] == '\t'))
			end = len;
		len--;
	}
	if (end == -1)
		end = ft_strlen(s) - start - 1;
	return (end);
}

static int	ft_just_spaces(char const *s)
{
	int	i;
	int	stop;

	i = 0;
	stop = -1;
	while (s[i] && stop == -1)
	{
		if (!(s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			stop = i;
		i++;
	}
	if (stop == -1)
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*ret;
	int		start;
	int		end;
	int		len;

	if (s == NULL)
		return (NULL);
	start = ft_start(s);
	end = ft_end(s, start);
	len = end - start + 1;
	if (!ft_just_spaces(s))
	{
		ret = ft_strsub(s, start, len);
		ret[len] = '\0';
		return (ret);
	}
	return (ft_strnew(0));
}
