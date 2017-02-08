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

void	free_tab(char ***tab)
{
	int i;

	i = 0;
	while (*tab && (*tab)[i])
	{
		free((*tab)[i]);
		++i;
	}
	free(*tab);
}

void	free_label_octet(char **tab, char *type)
{
	int i;

	i = 0;
	while (type[i])
	{
		free(tab[i]);
		++i;
	}
}

void	free_it(t_content **list)
{
	t_content *next;

	while (*list)
	{
		free((*list)->name);
		free_tab(&((*list)->label));
		free_label_octet((*list)->label_octet, (*list)->type);
		next = (*list)->next;
		free(*list);
		*list = next;
	}
	free(*list);
}
