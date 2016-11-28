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

void			print_ocp(t_content *list, int *nb, int fd)
{
	if (list->instruct == 12 || list->instruct == 9 ||\
	list->instruct == 1 || list->instruct == 15)
		return ;
	write(fd, &list->ocp, 1);
	++*nb;
}

uint32_t		bswap(unsigned int a, int nb, int fd)
{
	if (nb == 2)
		a = ((a & 0x00FF) << 8) | ((a & 0xFF00) >> 8);
	else if (nb == 4)
	{
		a = ((a & 0x000000FF) << 24) | ((a & 0x0000FF00) << 8)\
		| ((a & 0x00FF0000) >> 8) | ((a & 0xFF000000) >> 24);
	}
	write(fd, &a, nb);
	return (a);
}

void			print_content(t_content *list, int fd)
{
	int i;
	int nb;

	nb = 1;
	i = 0;
	write(fd, &list->instruct, 1);
	print_ocp(list, &nb, fd);
	while (list->type[i] && i != 3)
	{
		bswap(list->arg[i], list->type[i] - '0', fd);
		nb = nb + list->type[i] - '0';
		++i;
	}
}

unsigned int	total_octet(t_content *list)
{
	unsigned int nb;

	nb = 0;
	while (list)
	{
		nb = nb + nb_octet(list);
		list = list->next;
	}
	return (nb);
}

void			print_all(t_content *list, int fd, t_header *header)
{
	write(fd, header, sizeof(t_header));
	while (list && ft_strcmp(list->name, "instruc") == 0)
	{
		print_content(list, fd);
		list = list->next;
	}
}
