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

unsigned int	bitswap_32(unsigned int a)
{
	a = ((a & 0x000000FF) << 24) | ((a & 0x0000FF00) << 8)\
		| ((a & 0x00FF0000) >> 8) | ((a & 0xFF000000) >> 24);
	return (a);
}

void			next_to(t_content **list, t_content *next)
{
	t_content *begin;

	if (!next)
		return ;
	if (!*list)
	{
		*list = next;
		next->next = NULL;
	}
	else
	{
		begin = *list;
		while ((*list)->next)
			*list = (*list)->next;
		(*list)->next = next;
		*list = begin;
	}
}

int				checking_size(t_content *list, t_header *header)
{
	unsigned int i;

	if ((i = total_octet(list)) == 0)
		exit_with_message("Not enough line.");
	else if (i <= CHAMP_MAX_SIZE)
		(*header).prog_size = bitswap_32(i);
	else
		exit_with_message("Prog is too long.");
	return (1);
}

void			initialize_var(t_content **list, char **line, int *i)
{
	ft_bzero(list, sizeof(t_content *));
	*i = 0;
	*line = NULL;
}

void			checking_file(char *file, int fd)
{
	t_content		*list;
	t_header		header;
	char			*line;
	int				i;

	initialize_var(&list, &line, &i);
	if (check_file_name(file) == -1)
		exit_with_message("Not a .s");
	ft_bzero(&header, sizeof(header));
	header_initialize(&header, &i, fd);
	header.magic = bitswap_32(COREWAR_EXEC_MAGIC);
	while (nget_next_line(fd, &line, MAX_LINE_SIZE) == 1)
	{
		next_to(&list, check_this_line(line, 1));
		free(line);
		line = NULL;
	}
	next_to(&list, check_instruct(NULL, 1, 0));
	label_replace(&list, list);
	checking_size(list, &header);
	new_file(file, list, &header);
	free_it(&list);
}
