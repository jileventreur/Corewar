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

int					to_label_octet(t_content *list, int j, int count)
{
	int sum;

	sum = 0;
	while (list && count != j)
	{
		sum = sum - nb_octet(list);
		list = list->next;
		++count;
	}
	return (sum);
}

int					in_a_array(char *str, char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(str, tab[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}

int					to_label(t_content *list, char *label)
{
	int sum;

	sum = 0;
	while (list && (!list->label || in_a_array(label, list->label) != 1))
	{
		sum = sum + nb_octet(list);
		list = list->next;
	}
	if (!list)
		return (exit_with_message("Unknown Label"));
	return (sum);
}

int					looking_for(t_content **list, int i,\
					t_content *start, int j)
{
	int count;
	int total;

	total = 0;
	count = 0;
	while (start)
	{
		if (start->label &&\
		in_a_array((*list)->label_octet[i], start->label) == 1)
			return (to_label_octet(start, j, count));
		else if (j == count)
			return (to_label(start, start->label_octet[i]));
		total = total - nb_octet(*list);
		start = start->next;
		++count;
	}
	return (0);
}

int					label_replace(t_content **list, t_content *begin)
{
	t_content	*start;
	int			i;
	int			j;

	j = 0;
	if (!*list)
		exit_with_message("Empty file.");
	start = begin;
	while (*list)
	{
		i = 0;
		while (i < 3 && (*list)->type[i])
		{
			if ((*list)->label_octet[i])
				(*list)->arg[i] = looking_for(list, i, start, j);
			++i;
		}
		++j;
		*list = (*list)->next;
	}
	*list = begin;
	return (1);
}
