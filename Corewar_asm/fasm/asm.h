#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../op.h"
#include "../libft/libft.h"

#define AFTER_COMMENT			';'

void	exit_with_message(char *str);
int	checking_file (char *file, int fd);
char *check_label(char *str, int *i);
void print_bits(unsigned int nb, int i, int fd);

typedef struct    s_content
{
	char *name;
	int instruct;
	int ocp;
	int arg[3];
	int nb_octet;
	char type[4];
	char *label_octet[4];
	char **label;
	struct s_content *next;
}					t_content;

t_content	*check_instruct(char *str, int nb);
void print_all(t_content *list, int fd);
int		nb_octet(t_content *list);
void	free_tab(char **tab);
t_content *check_the_comment (char *str);
t_content	*check_the_name (char *str);
t_content	*new_content(char *str, int nb);
t_content *only_label(char **tab);
int 	check_blank_line(char *str, int *count);
int 		ft_isspace(char c);
int one_of(char c);
void	free_it(t_content **list);
int		label_replace(t_content **list, t_content *begin);
void RemoveChar(char *str);
int	ft_strisuint(char *arg);
int				ft_strisint(char *arg);
int 	reg_check(char c, char *value);
int 	check_arg(char *str, int *i, t_content **list, int count);
void		copy_label(t_content **list, char **label);