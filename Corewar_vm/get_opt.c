/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 21:33:27 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 21:33:28 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		get_opt_d(t_opt *opt, char ***argv, int argc, int i)
{
	unsigned int	tmp;

	if (i + 1 >= argc)
		ft_error_exit("Error: no argument after -d\n");
	++*argv;
	if (!ft_strisuint(**argv))
		ft_error_exit("Error: argument after -d is not an unsigned number\n");
	tmp = ft_atou(**argv);
	opt->d = tmp;
	if (opt->d != tmp)
		ft_error_exit("Error: argument after -d is not an unsigned number\n");
}

static void		get_opt_s(t_opt *opt, char ***argv, int argc, int i)
{
	if (i + 1 >= argc)
		ft_error_exit("Error: no argument after -s\n");
	++*argv;
	if (!ft_strisuint(**argv))
		ft_error_exit("Error: argument after -s is not an unsigned number\n");
	if ((opt->s = ft_atou(**argv)) == 0)
		ft_error_exit("Error: argument after -s can't be zero\n");
}

static void		get_opt_v(t_opt *opt, char ***argv, int argc, int i)
{
	unsigned int v;

	if (i + 1 >= argc)
		ft_error_exit("Error: no argument after -v\n");
	++*argv;
	if (!ft_strisuint(**argv))
		ft_error_exit("Error: argument after -v is not an unsigned number\n");
	if ((v = ft_atou(**argv)) > 31)
		ft_error_exit("Error: argument after -v is bigger than 31\n");
	opt->v = ft_atou(**argv);
}

static void		switch_opt(t_opt *opt, char ***argv, int argc, int *i)
{
	if (*(**argv + 1) == 'h' && (*(**argv + 2)) == '\0' && opt->h++ == 0)
		print_usage();
	else if (*(**argv + 1) == 'a' && (*(**argv + 2)) == '\0')
		opt->a = 1;
	else if (*(**argv + 1) == 'g' && (*(**argv + 2)) == '\0')
		opt->g = 1;
	else if ((*(**argv + 1) == 'd' &&
	(*(**argv + 2)) == '\0') || !ft_strcmp("-dump", **argv))
	{
		get_opt_d(opt, argv, argc, *i);
		++(*i);
	}
	else if (*(**argv + 1) == 's' && (*(**argv + 2)) == '\0')
	{
		get_opt_s(opt, argv, argc, *i);
		++(*i);
	}
	else if (*(**argv + 1) == 'v' && (*(**argv + 2)) == '\0')
	{
		get_opt_v(opt, argv, argc, *i);
		++(*i);
	}
	else
		ft_error_exit("Error: multiple option not allowed\n");
}

void			get_opt(char ***argv_source, int *argc, t_opt *opt)
{
	int		i;
	char	**argv;

	i = 0;
	argv = *argv_source;
	opt->d = -1;
	while (i < *argc && **argv == '-')
	{
		if (ft_strlen(*argv) < 2)
			ft_error_exit("Error: no option after -\n");
		if (*(*argv + 1) == 'n')
			break ;
		if (!ft_isanyof(*(*argv + 1), OPTION))
			ft_error_exit("Error: incompatible option\n");
		switch_opt(opt, &argv, *argc, &i);
		++argv;
		++i;
	}
	*argv_source = argv;
	*argc -= i;
}
