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

void		param_initialize(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int			good_check_redirect_part2(char c, int mask, int size, char *str)
{
	size = is_it_good(c, mask);
	if (size == -1)
	{
		ft_putendl_fd(str, 2);
		exit_with_message("Bad argument.");
	}
	return (1);
}

void		last_octet_update(int j, int octet, t_content **list)
{
	while (j <= 3)
	{
		octet = octet << 2;
		++j;
	}
	(*list)->ocp = octet;
}

void		good_check_redirect_bad(char *str, int j, t_op tab)
{
	if ((unsigned int)j != tab.param_number)
	{
		ft_putendl_fd(str, 2);
		exit_with_message("Wrong parameter.\n");
	}
}

int			good_check_redirect(char *str, t_op tab, int *i, t_content **list)
{
	int j;
	int size;
	int octet;

	param_initialize(&j, &size, &octet);
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		++*i;
	while (j != 3 && (unsigned int)j != tab.param_number)
	{
		size = good_check_redirect_part2(str[*i], tab.param_mask[j], size, str);
		if (size == 0)
			break ;
		octet = update_octet(octet, j, str[*i], list);
		correction(list, tab);
		(*list)->arg[j] = check_arg(str, i, list, j);
		while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			++*i;
		++j;
	}
	good_check_redirect_bad(str, j, tab);
	last_octet_update(j, octet, list);
	if (!str[*i] || str[*i] == AFTER_COMMENT || str[*i] == COMMENT_CHAR)
		return (1);
	ft_putendl_fd(str, 2);
	return (exit_with_message("Problem."));
}
