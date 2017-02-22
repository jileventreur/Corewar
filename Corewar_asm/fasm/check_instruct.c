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

int			reg_check(char c, char *value)
{
	if (c != '1')
		return (1);
	if (ft_atoi(value) >= 0 && ft_atoi(value) <= REG_NUMBER)
		return (1);
	return (0);
}

void		correction(t_content **list, t_op tab)
{
	int i;

	i = 0;
	if (tab.direct_adr)
	{
		while ((*list)->type[i])
		{
			if ((*list)->type[i] == '0' + DIR_SIZE)
				(*list)->type[i] = '0' + IND_SIZE;
			++i;
		}
	}
}

int			check_good_instruct(char *str, int *i, t_op *tab)
{
	int j;
	int nb;
	int save;

	j = 0;
	nb = 0;
	save = *i;
	while (tab[nb].name)
	{
		while (tab[nb].name[j] == str[*i] && str[*i])
		{
			++*i;
			++j;
		}
		if (!(tab[nb].name[j]) && (str[*i] == '\t' || str[*i] == ' '))
			return (nb);
		*i = save;
		j = 0;
		++nb;
	}
	ft_putendl_fd(str, 2);
	exit_with_message("Bad command.");
	return (1);
}

int			check_common_instruct(char *str,\
			int *i, t_op *tab, t_content **list)
{
	int nb;

	nb = check_good_instruct(str, i, tab);
	(*list)->instruct = tab[nb].opcode;
	good_check_redirect(str, tab[nb], i, list);
	return (1);
}

t_content	*check_instruct(char *str, int nb, int i)
{
	extern	t_op	g_op_tab[17];
	t_content		*list;
	static	char	**label_tab;
	static	int		count = 0;

	if (!str)
		return (only_label(&label_tab, &count));
	label_tab = realloc(label_tab, (count + 2) * sizeof(char *));
	label_tab[count] = check_label(str, &i);
	label_tab[++count] = NULL;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		++i;
	if ((!str[i] || str[i] == COMMENT_CHAR ||\
	str[i] == AFTER_COMMENT) && nb == 1)
		return (NULL);
	count = 0;
	list = malloc(sizeof(t_content));
	if (!list)
		exit_with_message("Malloc error.");
	copy_label(&list, label_tab);
	free_tab(&label_tab);
	label_tab = NULL;
	check_common_instruct(str, &i, g_op_tab, &list);
	list_modif(&list);
	return (list);
}
