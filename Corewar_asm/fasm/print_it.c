#include "asm.h"

void print_bits(unsigned int nb, int i, int fd)
{
	if (!i)
		return ;
	print_bits(nb >> 1, i - 1, fd);
	printf("%c%c", nb % 2 ? '1' : '0', i == sizeof(int) * 8 ? '\n' : 0);
	if (i%8 == 0)
		printf(" ");
}

void print_ocp(t_content *list, int *nb, int fd)
{
	if (list->instruct == 12 || list->instruct == 9 || list->instruct == 1)
		return ;
	print_bits(list->ocp, 8, fd);
	write(fd, &list->ocp, 1);
	++*nb;
}

uint32_t _bswap32(uint32_t a, int nb, int fd)
{
	if (nb == 2)
{
  a = ((a & 0x00FF) << 8) | ((a & 0xFF00) >> 8);
}
else if (nb == 4)
{
  a = ((a & 0x000000FF) << 24) |
      ((a & 0x0000FF00) <<  8) |
      ((a & 0x00FF0000) >>  8) |
      ((a & 0xFF000000) >> 24);
}
     write(fd, &a, nb);
  return a;
}

void print_content(t_content *list, int fd)
{
	int i;
	int nb;

	nb = 1;
	i = 0;
	//ft_printf("{red}%b{eoc} ", list->instruct);
	//ft_printf("{red}%b{eoc} ", list->ocp);
	print_bits(list->instruct, 8, fd);
	write(fd, &list->instruct, 1);
	print_ocp(list, &nb, fd);
	while (list->type[i] && i != 3)
	{
		if (i == 0)
			printf("\033[1;31m");
		if (i == 1)
			printf("\033[1;32m");
		if (i == 2)
			printf("\033[1;35m");
		_bswap32(list->arg[i], list->type[i] - '0', fd);
		//write(fd, _bswap32(list->arg[i]), list->type[i] - '0');
		print_bits(list->arg[i], (list->type[i] - '0') * 8, fd);
		nb = nb + list->type[i] - '0';
		//printf("label = %s\n", list->label_octet[i]);
		++i;
	}
	printf("\033[0;m\n");
				//printf("label = %s\n", list->label);
	//printf("%d octets\n", nb);
}

int 	total_octet(t_content *list)
{
	int nb;

	nb = 0;
	list = list->next;
	while (list)
	{
		nb = nb + nb_octet(list);
		printf("%s %d\n", list->name, nb);
		list = list->next;
	}
	return (nb);
}

void print_all(t_content *list, int fd)
{
	_bswap32(COREWAR_EXEC_MAGIC, 4, fd);
	write(fd, list->name, PROG_NAME_LENGTH);
	printf("%s\n", list->name);
	list = list->next;
	_bswap32(total_octet(list), 2, fd);
	write(fd, list->name, COMMENT_LENGTH);
	printf("%s\n", list->name);
	list = list->next;
	while (list && ft_strcmp(list->name, "instruc") == 0)
	{
		print_content(list, fd);
		list = list->next;
	}
}