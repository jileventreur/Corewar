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

int			good_len(char *str, int len, int ind)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '"')
		++i;
	++i;
	while (str[i] != '"')
	{
		++i;
		++count;
	}
	++i;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] && str[i] != COMMENT_CHAR && str[i] != AFTER_COMMENT)
		exit_with_message("Bad header");
	if (count <= len)
		return (1);
	if (ind == 1)
		exit_with_message("Bad name's length");
	else
		exit_with_message("Bad comment's length");
	return (0);
}

int			check_blank_line(char *str)
{
	int i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		++i;
	if (!str[i] || str[i] == COMMENT_CHAR || str[i] == AFTER_COMMENT)
		return (1);
	return (0);
}

void		starting_cmp(char *str, char *cmp, int *i, int *j)
{
	while (str[*i] && ft_isspace(str[*i]))
		++*i;
	while (cmp[*j] == str[*i] && str[*i])
	{
		++*j;
		++*i;
	}
}

char		*another_loop_name(char **str, char **line, int fd)
{
	if (nget_next_line(fd, line, MAX_LINE_SIZE) != 1)
		exit_with_message("Name problem");
	*str = realloc(*str, (3 + ft_strlen(*line) +\
	ft_strlen(*str)) * sizeof(char));
	ft_strcat(*str, "\n");
	ft_strcat(*str, *line);
	free(*line);
	return (check_the_name(str, 0, 0, fd));
}

char		*check_the_name(char **str, int i, int j, int fd)
{
	char *cmp;
	char *line;

	cmp = NAME_CMD_STRING;
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
				return (another_loop_name(str, &line, fd));
			if (good_len(*str, PROG_NAME_LENGTH, 1) == 1)
				return (*str);
		}
	}
	return (NULL);
}
