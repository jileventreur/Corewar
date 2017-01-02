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

void	print_bits(unsigned int x)
{
	int	i;
	for(i=(sizeof(int)*8)-1; i>=0; i--)
		(x&(1u<<i))?putchar('1'):putchar('0');
	printf("\n");
}

void	print_procs(t_vm *vm, t_list *lst, unsigned char print_reg)
{
	extern t_op			op_tab[INSTR_NUMBER + 1];

	t_proc	*p;
	int		i;

	printf("-------------------- PROCS -----------------------\n");
	while (lst)
	{
		p = lst->content;
		i = 0;
		printf("\t----- Proc %.2d (Player %d) -----\n", p->proc_num, p->player_num);
		while (print_reg && i < REG_NUMBER)
		{
			printf("\t\treg[%d] = %d (%#x)\n", i + 1, i, *(int *)p->reg[i]);
			++i;
		}
		printf("\t\tpc -> 0x%.4x [%.2x]\n", p->pc, vm->mem[p->pc]);
		printf("\t\tnext inst in %d cycle is %s\n", p->cycle_to_wait, (p->inst < INSTR_NUMBER ) ? op_tab[p->inst].name : "NULL");
		printf("\t\tcarry %s\n",  p->carry ? "ON" : "OFF");
		printf("\t\tlife is %s\n", p->life ? "OK" : "DEAD");
		printf("\t\tlast life is %lld\n", p->last_live);
		printf("\t------------------------------\n");
		lst = lst->next;
	}
	printf("--------------------------------------------------\n");
}

void	print_vm(t_vm *vm)
{
	unsigned int 	i;
	unsigned char	c;

	i = 0;
	while (i < MEM_SIZE)
	{
		c = vm->mem[i];
		if (i % BYTE_LINE_NB == 0)
			printf("0x%.4x : ", i);
			printf("%2.2x ", c);
		if (((i + 1) % BYTE_LINE_NB) == 0 || i == (MEM_SIZE - 1))
			printf("\n");
		++i;
	}
}

void	my_print_vm(t_vm *vm)
{
	unsigned int 	i;
	unsigned char	c;
	char	color[10];

	i = 0;
	ft_strcpy(color, "\033[30;40m");
	while (i < MEM_SIZE)
	{
		c = vm->mem[i];
	if (ISACTIV(vm->proc_mem[i], 2))
	{
		color[6] = '0' + (0b11 & vm->proc_mem[i]);
		color[3] = '0';
	}
	else
	{
		color[3] = '0' + (0b11 & vm->proc_mem[i]);
		color[6] = '0';		
	}
		printf("%s%2.2x\033[0m%c%c", vm->proc_mem[i] == 0 ? "" : color, c,
		(i + 1) % 2 == 0 ? ' ' : 0, ((i + 1) % BYTE_LINE_NB) == 0 || i == (MEM_SIZE - 1) ? '\n' : 0);
		++i;
	}
}

// void	print_procs(t_list *lst)
// {
// 	int	i;
// 	t_proc *tmp;

// 	printf("----- PROCS -----\n");
// 	if (!lst)
// 		printf("NO PROCS\n-----------------\n");
// 	while (lst)
// 	{
// 		printf("%p\n", lst->next);
// 		tmp = (t_proc *)lst->content;
		
// 		i = 0;
// 		while (i < REG_NUMBER)
// 		{
// 			printf("REG[%d]: %d\n", i, *(int *)tmp->reg[i]);
// 			++i;
// 		}
// 		printf("PC = %d\n", tmp->pc);
// 		printf("CARRY = %d\n", (int)tmp->carry);
// 		printf("CYCLE TO WAIT = %u\n", (int)tmp->cycle_to_wait);
// 		lst = lst->next;
// 		printf("-----------------\n");
// 	}
// }