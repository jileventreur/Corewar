/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 14:39:49 by cadam             #+#    #+#             */
/*   Updated: 2015/01/23 14:39:51 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 42

# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"

int	get_next_line(int const fd, char **line);

#endif
