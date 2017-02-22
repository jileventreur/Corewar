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

void	prog_name(t_header *header, char *line)
{
	char *str;

	str = allocate_new(line, 1);
	strncpy((*header).prog_name, str, PROG_NAME_LENGTH + 1);
	free(str);
}

void	comment_header(t_header *header, char *line)
{
	char *str;

	str = allocate_new(line, 2);
	strncpy((*header).comment, str, COMMENT_LENGTH + 1);
	free(str);
}

int		header_initialize(t_header *header, int *i, int fd)
{
	char *line;

	line = NULL;
	while (*i < 3 && nget_next_line(fd, &line, MAX_LINE_SIZE) == 1)
	{
		while (!check_blank_line(line))
		{
			if (*i != 1 && *i != 3 && (check_the_name(&line, 0, 0, fd)))
			{
				prog_name(header, line);
				++*i;
				break ;
			}
			if (*i != 2 && *i != 3 && check_the_comment(&line, 0, 0, fd))
			{
				comment_header(header, line);
				*i = *i + 2;
				break ;
			}
			exit_with_message("Bad header");
		}
		free(line);
		line = NULL;
	}
	return (1);
}
