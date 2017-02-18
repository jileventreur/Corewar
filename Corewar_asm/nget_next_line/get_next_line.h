/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilano <jilano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 14:39:49 by cadam             #+#    #+#             */
/*   Updated: 2017/02/18 18:22:39 by jilano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 255

# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

typedef struct		s_gnl
{
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	char			**line;
}					t_gnl;

int	get_next_line(int const fd, char **line);
int	nget_next_line(int const fd, char **line, size_t n);

#endif
