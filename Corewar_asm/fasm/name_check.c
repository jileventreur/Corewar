#include "asm.h"
int good_len(char *str, int len)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '"')
		++i;
	++i;
	while (str[i] != '"')
	{
		++i;
		++count;
	}
	if (count <= len)
		return (1);
	return (0);
}

t_content *check_the_comment (char *str)
{	
	char *cmp;
	int i;

	i = 0;
	cmp = COMMENT_CMD_STRING;
	while (cmp[i] == str[i] && str[i])
		++i;
	if (!cmp[i] && str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			++i;
		if (str[i] == '\"')
		{
			while (str[i])
				++i;
			if (good_len(str, COMMENT_LENGTH))
				return (new_content(str, 2));
		}
	}
	exit_with_message("bad comment");
	return (NULL);
}


//Verifier la longueur ?
t_content	*check_the_name (char *str)
{
	char *cmp;
	int i;

	i = 0;
	cmp = NAME_CMD_STRING;
	while (cmp[i] == str[i] && str[i])
		++i;
	if (!cmp[i] && str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			++i;
		if (str[i] == '\"')
		{
		while (str[i])
			++i;
		if (good_len(str, PROG_NAME_LENGTH) == 1)
			return (new_content(str, 1));
		}
	}
	exit_with_message("bad title");
	return (NULL);
}


//Verifie si la ligne est vide OU si c'est un commentaire - decremente count pour le title  et commentaire
int 	check_blank_line(char *str, int *count)
{
	int i;

	i = 0;
	if (str[0] == COMMENT_CHAR)
	{
		--*count;
		return (1);
	}
	while (str[i] == '\t' || str[i] == ' ')
		++i;
	if (!str[i])
	{
		--*count;
		return (1);
	}
	return (0);
}
