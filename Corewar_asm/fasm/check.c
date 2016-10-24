#include "asm.h"

void RemoveChar(char *str)
{
	int i;

	i = 1;
	while (str[i - 1])
	{
		str[i - 1] = str[i];
		++i;
	}
}

char 		*allocate_new(char *str, int nb)
{
	char *new_str;
	int i;
	int j;

	i = 0;
	j = 0;
	if (nb == 1)
		new_str = ft_strnew(PROG_NAME_LENGTH);
	else
		new_str = ft_strnew(COMMENT_LENGTH);
	while (str[i] && str[i] != '\"')
		++i;
	++i;
	while (str[i] && str[i] != '\"')
	{
		new_str[j] = str[i];
		++i;
		++j;
	}
	printf("%s\n", new_str);
	return(new_str);
}

t_content	*new_content(char *str, int nb)
{
	t_content *new_c;

	new_c = malloc(sizeof(t_content));
	new_c->type[0] = 0;
	new_c->label = NULL;
	new_c->label_octet[0] = NULL;
	new_c->label_octet[1] = NULL;
	new_c->label_octet[2] = NULL;

	new_c->name = allocate_new(str, nb);
	new_c->next = NULL;
	return (new_c);
}

t_content	*check_this_line(char *str, int *count, int i)
{
	if (check_blank_line(str, count))
		return (NULL);
	if (*count == 1)
		return(check_the_name(str));
	else if (*count == 2)
		return(check_the_comment(str));
	return(check_instruct(str, i));
	return (NULL);
}

void	next_to(t_content **list, t_content *next)
{
	t_content *begin;

	if (!next)
		return ;
	if (!*list)
	 {
		*list = next;
		next->next = NULL;
	 }
	 else
	 {
	 	begin = *list;
	 	while ((*list)->next)
	 		*list = (*list)->next;
	 	(*list)->next = next;
	 	*list = begin;
	 }
}

char 	*file_name(char *file)
{
	char *cpy;
	int i;

	i = 0;
	cpy = ft_strnew(ft_strlen(file) + 3);
	while (file[i])
	{
		cpy[i] = file[i];
		++i;
	}
	cpy[i - 1] = 'c';
	cpy[i] = 'o';
	cpy[i + 1] = 'r';
	return (cpy);
}

int 	check_file_name(char *file)
{
	int i;

	i = 0;
	while (file[i])
		++i;
	if (i >= 3 && file[i - 1] == 's' && file[i - 2] == '.')
		return (1);
	return (-1);
}


void	new_file(char *file, t_content *list)
{
	int new_fd;
	char *str;

	str = file_name(file);
	new_fd = open(str, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	print_all(list, new_fd);
	free(str);
	close(new_fd);
}

int	checking_file (char *file, int fd)
{
	t_content *list;
	char *line;
	int i;

	i = 0;
	list = NULL;
	if (check_file_name(file) == -1)
		exit_with_message("Not a .s");
	while (get_next_line(fd, &line) > 0)
	{
		++i;
		next_to(&list, check_this_line(line, &i, 1));
		free(line);
	}
	if (i < 3)
		exit_with_message("Not enough lines");
	next_to(&list, check_instruct(NULL, 1));
	label_replace(&list, list);
	new_file(file, list);
	free_it(&list);
	return (1);
}