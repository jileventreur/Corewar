#include "corewar.h"

void	print_memory(unsigned char *mem, unsigned int size)
{
	// static unsigned char prec[MEM_SIZE] = {0};
	unsigned int 	i;
	unsigned char	c;

	i = 0;
	// printf("i == %d\n", i);
	while (i < size)
	{
	// printf("i == %d\n", i);
		c = mem[i];
		// ft_printf("c == %d\n", c);
		// ft_printf("mem[%u] == %d\n", i, mem[i]);
		ft_printf("%2.2x%c%c\033[0m", c, (i + 1) % 2 == 0 ? ' ' : 0,
		((i + 1) % 64) == 0 || i == (size - 1) ? '\n' : 0);
		++i;
	}
	// ft_memcpy(prec, mem, MEM_SIZE);
}


void	print_champions(t_champion *tab)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (!ft_memisset(&tab[i], sizeof(t_champion), 0))
		{
			printf("----- CHAMPION %d -----\n", i + 1);
			printf("NAME = %s\nCOMMENT = %s\n", tab[i].header.prog_name, tab[i].header.comment);
			printf("PROGRAMME:\n");
			print_memory(tab[i].prog, tab[i].header.prog_size);
			printf("-----------------------\n");
		}
		++i;
	}
}

void	print_procs(t_list *lst)
{
	int	i;
	t_proc *tmp;

	printf("----- PROCS -----\n");
	if (!lst)
		printf("NO PROCS\n-----------------\n");
	while (lst)
	{
		printf("%p\n", lst->next);
		tmp = (t_proc *)lst->content;
		
		i = 0;
		while (i < REG_NUMBER)
		{
			printf("REG[%d]: %d\n", i, *(int *)tmp->reg[i]);
			++i;
		}
		printf("PC = %d\n", tmp->pc);
		printf("CARRY = %d\n", (int)tmp->carry);
		printf("CYCLE TO WAIT = %u\n", (int)tmp->cycle_to_wait);
		lst = lst->next;
		printf("-----------------\n");
	}
}