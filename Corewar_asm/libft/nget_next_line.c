/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nget_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilano <jilano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 14:37:56 by cadam             #+#    #+#             */
/*   Updated: 2017/02/18 18:27:01 by jilano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	eob_find_line(char **eob, char **line, size_t n)
{
	size_t	i;
	char	*tmp;
	char	is_end_of_line;

	tmp = *eob;
	i = 0;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '\n' || n == i)
		{
			is_end_of_line = (tmp[i] == '\n');
			*line = ft_strsub(tmp, 0, i);
			*eob = ft_strdup(tmp + i + is_end_of_line);
			ft_strdel(&tmp);
			return (1 + !is_end_of_line);
		}
		i++;
	}
	return (0);
}

int	last_line(t_gnl *gnl, char **eob)
{
	if (gnl->tmp)
	{
		*gnl->line = ft_strjoin(*eob, gnl->tmp);
		ft_strdel(eob);
		free(gnl->tmp);
		return (1);
	}
	if (*eob)
	{
		*gnl->line = ft_strdup(*eob);
		ft_strdel(eob);
		return (1);
	}
	return (0);
}

int	check_newline(t_gnl *gnl, char **eob, size_t n, size_t ret)
{
	size_t		i;
	char		*tmp_free;
	char		*tmp_str;

	i = 0;
	while (i < ret)
	{
		if (gnl->buf[i] == '\n' || i == n)
		{
			tmp_free = gnl->tmp;
			tmp_str = ft_strsub(gnl->buf, 0, i);
			gnl->tmp = ft_strjoin(gnl->tmp, tmp_str);
			free(tmp_free);
			free(tmp_str);
			*gnl->line = ft_strjoin(*eob, gnl->tmp);
			free(gnl->tmp);
			tmp_free = *eob;
			*eob = ft_strdup(gnl->buf + i + (gnl->buf[i] == '\n'));
			ft_strdel(&tmp_free);
			return (1 + !(gnl->buf[i] == '\n'));
		}
		i++;
	}
	return (0);
}

int	nget_next_line(int const fd, char **line, size_t n)
{
	static char	*eob = NULL;
	t_gnl		gnl;
	int			ret;
	char		*tmp_free;

	gnl.tmp = NULL;
	gnl.line = line;
	if (fd == -1 || line == NULL)
		return (-1);
	if ((ret = eob_find_line(&eob, gnl.line, n)))
		return (ret);
	while ((ret = read(fd, gnl.buf, BUFF_SIZE)))
	{
		gnl.buf[ret] = '\0';
		if (ret == -1)
			return (-1);
		if ((ret = check_newline(&gnl, &eob, n, ret)))
			return (ret);
		tmp_free = gnl.tmp;
		gnl.tmp = ft_strjoin(gnl.tmp, gnl.buf);
		free(tmp_free);
	}
	if (last_line(&gnl, &eob))
		return (1);
	return (0);
}
