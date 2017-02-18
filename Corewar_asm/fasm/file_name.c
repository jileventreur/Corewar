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

char	*file_name(char *file)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = ft_strnew(ft_strlen(file) + 3);
	while (file[i])
	{
		cpy[i] = file[i];
		++i;
	}
	cpy[i - 1] = 'c';
	cpy[i] = 'o';
	cpy[i + 1] = 'r';
	return (cpy);
}

int		check_file_name(char *file)
{
	int i;

	i = 0;
	while (file[i])
		++i;
	if (i >= 3 && file[i - 1] == 's' && file[i - 2] == '.')
		return (1);
	return (-1);
}

void	new_file(char *file, t_content *list, t_header *header)
{
	int		new_fd;
	char	*str;

	str = file_name(file);
	new_fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR |\
	S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (new_fd == -1)
	{
		ft_putendl_fd(str, 2);
		free(str);
		return ;
	}
	print_all(list, new_fd, header);
	ft_printf("Writing a %s file\n", str);
	free(str);
	close(new_fd);
}
