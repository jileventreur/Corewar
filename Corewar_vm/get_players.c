#include "corewar.h"

static void		get_champion(char *filename, t_champion *champ, int champ_num)
{
	int			fd;
	int			ret;
	char		buf[CHAMP_MAX_SIZE + sizeof(t_header) + 1];
	t_header	*p;

	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_error_exit("Error: unable to open\n");
	if ((ret = read(fd, buf, CHAMP_MAX_SIZE + sizeof(t_header))) == -1)
		ft_error_exit("Error unable to read file\n");
	if (read(fd, buf, CHAMP_MAX_SIZE + sizeof(t_header)) != 0)
		ft_error_exit("Error: file is too large\n");
	if ((unsigned long)ret < sizeof(t_header))
		ft_error_exit("Error: file is too small\n");
	buf[ret] = 0;
	p = (t_header *)buf;
	p->magic = BSWAP_32(p->magic);
	p->prog_size = BSWAP_32(p->prog_size);
	if (p->magic != COREWAR_EXEC_MAGIC)
		ft_error_exit("Error: bad magic number\n");
	if (p->prog_size != ret - sizeof(t_header))
		ft_error_exit("Error: bad program size\n");
	champ->header = *p;
	ft_memcpy(champ->prog, buf + sizeof(t_header), ret - sizeof(t_header));
	champ->num = champ_num + 1;
}

static int		create_champion(t_champion *tab, char **argv)
{
	int	num;

	if (ft_strcmp(*argv, "-n"))
	{
		num = 0;
		while (num < MAX_PLAYERS && !ft_memisset(&tab[num], sizeof(t_champion), 0))
			++num;
		if (num == MAX_PLAYERS)
			ft_error_exit("Error: Too much champions\n");
		get_champion(argv[0], &tab[num], num);
		return (1);
	}
	if (!ft_strisuint(argv[1]))
		ft_error_exit("Error: Argument after -n is not a unsigned number\n");
	if ((num = ft_atoi(argv[1]) -1) >= MAX_PLAYERS)
		ft_error_exit("Error: Argument after -n is greater than max players\n");
	if (num < 0)
		ft_error_exit("Error: Argument after -n is smaller than 1\n");
	if (!ft_memisset(&tab[num], sizeof(t_champion), 0))
		ft_error_exit("Error: Player number already taken\n");
	get_champion(argv[2], &tab[num], num);
	return (3);
}

int				get_players(char **argv, int argc, t_champion *tab)
{
	int			i;
	int			cpt;
	
	i = 0;
	cpt = 0;
	ft_bzero(tab, sizeof(t_champion) * MAX_PLAYERS);
	while (i < argc)
	{
		++cpt;
		i += create_champion(tab, argv + i);
	}
	return (cpt);
}
