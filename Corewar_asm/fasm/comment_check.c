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

char		*another_loop_comment(char **str, char **line, int fd)
{
	if (get_next_line(fd, line) <= 0)
		exit_with_message("Comment problem");
	*str = realloc(*str, (3 + ft_strlen(*line) +\
	ft_strlen(*str)) * sizeof(char));
	ft_strcat(*str, "\n");
	ft_strcat(*str, *line);
	free(*line);
	return (check_the_comment(str, 0, 0, fd));
}

char		*check_the_comment(char **str, int i, int j, int fd)
{
	char *cmp;
	char *line;

	cmp = COMMENT_CMD_STRING;
	starting_cmp(*str, cmp, &i, &j);
	if (!cmp[j] && (*str)[i])
	{
		while ((*str)[i] == ' ' || (*str)[i] == '\t')
			++i;
		if ((*str)[i++] == '\"')
		{
			while ((*str)[i] && (*str)[i] != '\"')
				++i;
			if (!(*str)[i])
			{
				return (another_loop_comment(str, &line, fd));
			}
			if (good_len(*str, COMMENT_LENGTH, 2))
				return (*str);
		}
	}
	return (NULL);
}
