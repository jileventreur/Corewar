#include "corewar.h"

static int		dont_overflow(char *arg)
{
	long int			nb;
	int					sign;

	sign = 1;
	nb = 0;
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '+' || *arg == '-')
		sign = (*(arg++) == '-') ? -1 : 1;
	while (*arg && nb * sign <= INT_MAX && nb * sign >= INT_MIN)
	{
		nb = nb * 10 + *arg - '0';
		arg++;
	}
	return (nb * sign <= INT_MAX && nb * sign >= INT_MIN);
}

int				ft_strisint(char *arg)
{
	int i;

	i = 0;
	if (!arg[i])
		return (0);
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (dont_overflow(arg));
}