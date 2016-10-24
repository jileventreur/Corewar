#include "asm.h"

int		nb_octet(t_content *list)
{
	int i;
	int nb;

	i = 0;
	nb = 1;
	if (!list->type[0])
		return (0);
	if (list->instruct == 1)
		return (5);
	if (list->instruct == 12 || list->instruct == 9 || list->instruct == 1)
		;
	else
		++nb;
		while (list->type[i] && i != 3)
	{
		nb = nb + list->type[i] - '0';
		++i;
	}
	return (nb);
}

int		to_label_octet(t_content *list, int j, int count)
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

int 	in_a_array(char *str, char **tab)
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

int		to_label(t_content *list, char *label, int total)
{
	int sum;

	sum = 0;
	while (list && (!list->label || in_a_array(label, list->label) != 1))
	{
		sum = sum + nb_octet(list);
		list = list->next;
	}
	if (!list)
		return (total);
		//exit_with_message("Problème label inexistant");
	return (sum);
}

int		looking_for(t_content **list, int i, t_content *start, int j)
{
	int count;
	int total;

	total = 0;
	count = 0;
	printf("ON CHERCHE %s\n", (*list)->label_octet[i]);
	while (start)
	{
		if (start->label && in_a_array((*list)->label_octet[i], start->label) == 1)
			return (to_label_octet(start, j, count));
		else if (j == count)
			return(to_label(start, start->label_octet[i], total));
		total = total - nb_octet(*list);
		start = start->next;
		++count;
	}
	return (0);
}
int		label_replace(t_content **list, t_content *begin)
{
	int i;
	int j;

	j = 0;
	t_content *start;

	if (!*list)
		exit_with_message("Empty file");
	start = (begin->next)->next;
	while (*list)
	{
		i = 0;
		while (i < 3 && (*list)->type && (*list)->type[i])
		{
			if ((*list)->label_octet[i])
				(*list)->arg[i] = looking_for(list, i, start, j - 2);
			++i;
		}
		++j;
		*list = (*list)->next;
	}
	*list = begin;
	return (1);
}