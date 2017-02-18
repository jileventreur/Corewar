#include "get_next_line.h"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("NO FILENAME\n");
		return (1);
	}
	int fd;
	char *str;
	if ((fd = open(av[1	], O_RDONLY)) == -1)
	{
		printf("BAD FILENAME\n");
		return (1);
	}
	int ret;
	while ((ret = nget_next_line(fd, &str, 5)) != 0)
	{
		printf("ret = %d, str = [%s] (len = %lu)\n", ret, str, ft_strlen(str));
		free(str);
	}
	return (0);
}