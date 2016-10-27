#include "corewar.h"

int		ft_memisset(void *p, size_t n, char c)
{
	char	*tmp;
	int		i;
	
	tmp = p;
	i = n;
	while (--i >= 0)
		if (tmp[i] != c)
			return (0);
	return (1);
}
