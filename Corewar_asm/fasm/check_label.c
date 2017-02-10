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

void			copy_label(t_content **list, char **label)
{
	int i;

	i = 0;
	if (!label || !(label[0]) || !(label[0][0]))
	{
		(*list)->label = NULL;
		return ;
	}
	while (label[i])
		++i;
	(*list)->label = malloc((i + 1) * sizeof(char *));
	if (!((*list)->label))
		exit_with_message("Malloc error.");
	i = 0;
	while (label[i])
	{
		(*list)->label[i] = ft_strdup(label[i]);
		++i;
	}
	(*list)->label[i] = NULL;
}

t_content		*only_label(char ***tab, int *count)
{
	t_content *new_c;

	*count = 0;
	if (!*tab)
		return (NULL);
	new_c = malloc(sizeof(t_content));
	if (!new_c)
		exit_with_message("Malloc error.");
	new_c->type[0] = 0;
	new_c->name = ft_strdup("label");
	new_c->label_octet[0] = NULL;
	new_c->label_octet[1] = NULL;
	new_c->label_octet[2] = NULL;
	copy_label(&new_c, *tab);
	free_tab(tab);
	*tab = NULL;
	new_c->next = NULL;
	new_c->type[0] = 0;
	return (new_c);
}

char			*add_label(char *str, int i)
{
	int		j;
	char	*label;

	label = malloc((1 + ft_strlen(str)) * sizeof(char));
	if (!label)
		exit_with_message("Malloc error.");
	j = 0;
	while (j < (i - 1))
	{
		label[j] = str[j];
		++j;
	}
	label[j] = '\0';
	return (label);
}

int				one_of(char c)
{
	int i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (1);
		++i;
	}
	return (0);
}

char			*check_label(char *str, int *i)
{
	while (one_of(str[*i]))
		++*i;
	if (str[*i] == LABEL_CHAR)
	{
		++*i;
		return (add_label(str, *i));
	}
	else
	{
		*i = 0;
		return (NULL);
	}
}
