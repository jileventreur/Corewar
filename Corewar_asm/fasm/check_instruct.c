#include "asm.h"
#include "op.c"


t_op *create_tab()
{
	return (op_tab);
}

int 	is_it_good(char c, int mask)
{
	if (mask == 0 || !c)
		return (0);
	if (c == 'r' && (mask == T_REG || mask == (T_REG | T_IND) || mask == (T_REG | T_DIR) || mask == (T_REG | T_IND | T_DIR)))
		return (REG_SIZE);
	if (c == '%' && (mask == T_DIR || mask == (T_DIR | T_IND) || mask == (T_REG | T_DIR) || mask == (T_REG | T_IND | T_DIR)))
		return (DIR_SIZE);
	if (c != 'r' && c != '%' && (mask == T_IND || mask == (T_REG | T_IND) || mask == (T_IND| T_DIR) || mask == (T_REG | T_IND | T_DIR)))
		return (IND_SIZE);
	return (-1);
}

char 		update_octet(unsigned char octet, int j, char c, t_content **list)
{
	if (j > 0)
		octet = octet << 2;
	if (c == '%')
	{
		octet = octet + DIR_CODE;
		(*list)->type[j] = '0' + DIR_SIZE;
	}
	else if (c == 'r')
	{
		octet = octet + REG_CODE;
		(*list)->type[j] = '0' + T_REG;
	}
	else
	{
		octet = octet + IND_CODE;
		(*list)->type[j] = '0' + IND_SIZE;
	}
	(*list)->type[j + 1] = 0;
	return (octet);
}

int 	reg_check(char c, char *value)
{
	if (c != '1')
		return (1);
	if (ft_atoi(value) >= 0 && ft_atoi(value) <= REG_NUMBER)
		return (1);
	return (0);
}

//modifie les size (4 et 2 octets)
void	correction(t_content **list, t_op tab)
{
	int i;

	i = 0;
	if (tab.direct_adr)
	{
		while ((*list)->type[i])
		{
			if ((*list)->type[i] == '0' + DIR_SIZE)
				(*list)->type[i] = '0' + IND_SIZE;
			++i;
		}
	}
}

void	param_initialize(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

int 	good_check_redirect_part2(char c, int mask, int size)
{
	size = is_it_good(c, mask);
	if (size == -1)
		exit(0);
	return (1);
}

void 	last_octet_update(int j, int octet, t_content **list)
{
	while (j <= 3)
	{
		octet = octet << 2;
		++j;
	}
	(*list)->ocp = octet;
}

int 	good_check_redirect(char *str, t_op tab, int *i, t_content **list)
{
	int j;
	int size;
	int octet;

	param_initialize(&j, &size, &octet);
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		++*i;
	while (j != 3 && (unsigned int)j != tab.param_number)
	{
		size = good_check_redirect_part2(str[*i], tab.param_mask[j], size);
		if (size == 0)
			break;
		octet = update_octet(octet, j, str[*i], list);
		correction(list, tab);
		(*list)->arg[j] = check_arg(str, i, list, j);
		while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			++*i;
		++j;
	}
	if ((unsigned int)j != tab.param_number)
		exit_with_message("WRONG PARAM\n");
	last_octet_update(j, octet, list);
	if (!str[*i] || str[*i] == AFTER_COMMENT)
		return (1);
	exit_with_message("Problem");
	return (-1);
}

//Verifie que l'instruction est dans le tableau defini dans op.c
int check_good_instruct(char *str, int *i, t_op *tab)
{
	int j;
	int nb;
	int save;

	j = 0;
	nb = 0;
	save = *i;
	while (tab[nb].name)
	{
		while (tab[nb].name[j] == str[*i] && str[*i])
		{
			++*i;
			++j;
		}
		if (!(tab[nb].name[j]) && (str[*i] == '\t' || str[*i] == ' '))
			return (nb);
		*i = save;
		j = 0;
		++nb;
	}
	ft_printf("{red}%s{eoc}\n", str);
	exit_with_message("Bad command");
	return (1);
}

int check_common_instruct(char *str, int *i, t_op *tab, t_content **list)
{
	int nb;

	nb = check_good_instruct(str, i, tab);
	(*list)->instruct = tab[nb].opcode;
	good_check_redirect(str, tab[nb], i, list);
	return (1);
}

t_content	*check_instruct(char *str, int nb)
{
	int i;
	t_content *list;
	static char **label_tab;
	static int count = 0;
	
	i = 0;
	if (!str)
		return(only_label(label_tab));
	label_tab = realloc(label_tab, (count + 2) * sizeof(char *));
	label_tab[count] = check_label(str, &i);
	label_tab[++count] = NULL;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		++i;
	if ((!str[i] || str[i] == AFTER_COMMENT) && nb == 1)
		return(NULL);
	count = 0;
	list = malloc(sizeof(t_content));
	copy_label(&list, label_tab);
	free_tab(label_tab);
	label_tab = NULL;
	check_common_instruct(str, &i, create_tab(), &list);
	list->next = NULL;
	list->name = ft_strdup("instruc");
	return (list);
}