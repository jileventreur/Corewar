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
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int fd;
	int i;

	i = 1;
	if (argc == 1)
		exit_with_message("We need .s files.");
	while (i < argc)
	{
		fd = open(argv[i], O_RDWR);
		if (fd <= 0)
			exit_with_message("Filedescriptor problem");
		checking_file(argv[i], fd);
		close(fd);
		++i;
	}
	return (1);
}
