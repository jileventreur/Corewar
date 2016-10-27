/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 14:37:56 by cadam             #+#    #+#             */
/*   Updated: 2015/04/24 14:29:59 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	eob_find_line(char **eob, char **line)
{
	int		i;
	char	*tmp;

	tmp = *eob;
	i = 0;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '\n')
		{
			*line = ft_strsub(tmp, 0, i);
			*eob = ft_strdup(tmp + i + 1);
			ft_strdel(&tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

int	last_line(char **tmp, char **eob, char **line)
{
	if (*tmp)
	{
		*line = ft_strjoin(*eob, *tmp);
		ft_strdel(eob);
		free(*tmp);
		return (0);
	}
	if (*eob)
	{
		*line = ft_strdup(*eob);
		ft_strdel(eob);
		return (0);
	}
	return (0);
}

int	check_newline(char *buf, char **tmp, char **eob, char **line)
{
	int			i;
	char		*tmp_free;
	char		*tmp_str;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			tmp_free = *tmp;
			tmp_str = ft_strsub(buf, 0, i);
			*tmp = ft_strjoin(*tmp, tmp_str);
			free(tmp_free);
			free(tmp_str);
			*line = ft_strjoin(*eob, *tmp);
			free(*tmp);
			tmp_free = *eob;
			*eob = ft_strdup(buf + i + 1);
			ft_strdel(&tmp_free);
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_next_line(int const fd, char **line)
{
	static char	*eob = NULL;
	int			ret;
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	char		*tmp_free;

	tmp = NULL;
	if (fd == -1 || line == NULL)
		return (-1);
	if (eob_find_line(&eob, line))
		return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (ret == -1)
			return (-1);
		if (check_newline(buf, &tmp, &eob, line))
			return (1);
		tmp_free = tmp;
		tmp = ft_strjoin(tmp, buf);
		free(tmp_free);
	}
	if (last_line(&tmp, &eob, line))
		return (1);
	return (0);
}
