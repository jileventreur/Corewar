/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <darabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 16:27:49 by darabi            #+#    #+#             */
/*   Updated: 2016/02/10 14:55:26 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strdup_after(char *cpy, char *source)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (source[j] && source[j] != '\n')
		j++;
	free(cpy);
	cpy = NULL;
	if (!source[j])
		return (NULL);
	++j;
	cpy = ft_strnew(ft_strlen(source) - j + 1);
	while (source[j])
	{
		cpy[i] = source[j];
		i++;
		j++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static int		ft_strdup_to(char **cpy, char **source, int i, int const fd)
{
	int j;

	j = 0;
	free(*cpy);
	if (!source[fd])
		return (-1);
	if (*source[fd] == '\0')
		return (0);
	if (!(*cpy = (char *)malloc((ft_strlen(source[fd]) + 1) * sizeof(char))))
		return (0);
	while (source[fd][++i] != '\n' && source[fd][i] != '\0')
		cpy[0][i] = source[fd][i];
	cpy[0][i] = '\0';
	if (source[fd][i] == '\0')
	{
		free(source[fd]);
		source[fd] = NULL;
		return (0);
	}
	i++;
	while (source[fd][i])
		source[fd][j++] = source[fd][i++];
	source[fd][j] = '\0';
	return (1);
}

static int		ft_get_next_add(char **cpy, char *str, size_t i, size_t j)
{
	char	*temp;

	if (*cpy)
	{
		temp = ft_strnew(ft_strlen(str) + ft_strlen(*cpy) + 1);
		ft_strcpy(temp, *cpy);
		ft_memdel((void **)cpy);
		*cpy = temp;
		j = ft_strlen(temp);
	}
	else
		*cpy = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!*cpy)
		return (0);
	while (str[++i] && str[i] != '\n')
		cpy[0][j++] = str[i];
	cpy[0][j] = '\0';
	if (str[i] == '\n')
		return (1);
	return (0);
}

static int		second_part_gnl(int const fd, char **line, char *buf, int ret)
{
	static char	*ending[256];

	if (!ending[fd])
		ending[fd] = ft_strnew(BUFF_SIZE + 1);
	else if (ending[fd] && ending[fd][0] == '\0')
	{
		free(ending[fd]);
		ending[fd] = NULL;
	}
	else if (ft_strdup_to(line, ending, -1, fd) == 1)
		return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		ft_get_next_add(line, buf, -1, 0);
		if ((ending[fd] = ft_strdup_after(ending[fd], buf)))
			break ;
	}
	if (ret < 0)
		return (-1);
	if (ret == 0 && !*line)
		return (0);
	return (1);
}

int				get_next_line(int const fd, char **line)
{
	char		*buf;
	int			ret;

	ret = 0;
	if (fd < 0 || !line || BUFF_SIZE <= 0 || fd > 256)
		return (-1);
	buf = ft_strnew(BUFF_SIZE + 1);
	if (!buf)
		return (-1);
	*line = NULL;
	ret = second_part_gnl(fd, line, buf, ret);
	free(buf);
	return (ret);
}
