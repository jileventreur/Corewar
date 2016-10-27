#include "asm.h"

char 	*check_arg_second_part(char *str, int *j, int *i)
{
	char *cpy;

	*j = 0;
	cpy = ft_strnew(ft_strlen(str) + 1);
	if (str[*i] == DIRECT_CHAR || str[*i] == 'r')
		++*i;
	while (str[*i] && str[*i] != SEPARATOR_CHAR && str[*i] != AFTER_COMMENT)
	{
		if (ft_isspace(str[*i]) == 0)
		{
			cpy[*j] = str[*i];
			++*j;
		}
		++*i;
	}
	if (str[*i] == SEPARATOR_CHAR)
		++*i;
	return (cpy);
}

int 	check_arg(char *str, int *i, t_content **list, int count)
{
	char *cpy;
	int j;

	cpy = check_arg_second_part(str, &j, i);
	if (cpy[0] == LABEL_CHAR)
	{
		RemoveChar(cpy);
		j = 0;
		while (one_of(cpy[j]))
			++j;
		(*list)->label_octet[count] = ft_strdup(cpy);
		free(cpy);
		return (0);
	}
	(*list)->label_octet[count] = NULL;
	if ((ft_strisuint(cpy) == 1 || ft_strisint(cpy) == 1) && reg_check((*list)->type[count], cpy) == 1)
	{
		j = ft_atoi(cpy);
		free(cpy);
		return (j);
	}
	ft_printf("%s\n", cpy);
	exit_with_message("ERROR WITH VALUE");
	return (-1);
}