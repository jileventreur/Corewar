/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <errno.h>
# include "../op.h"
# include "../libft/libft.h"

# define AFTER_COMMENT			';'
# define BSWAP_16(num) ((num>>8) | (num<<8))

typedef struct			s_content
{
	char				*name;
	int					instruct;
	int					ocp;
	int					arg[3];
	int					nb_octet;
	char				type[4];
	char				*label_octet[4];
	char				**label;
	struct s_content	*next;
}						t_content;

int						exit_with_message(char *str);
void					checking_file (char *file, int fd);
char					*check_label(char *str, int *i);
void					print_bits(unsigned int nb, int i, int fd);
t_content				*check_instruct(char *str, int nb, int i);
void					print_all(t_content *list, int fd, t_header *header);
unsigned int			nb_octet(t_content *list);
void					free_tab(char ***tab);
char					*check_the_comment (char **str, int i, int j, int fd);
char					*check_the_name (char **str, int i, int j, int fd);
t_content				*new_content(char *str, int nb);
t_content				*only_label(char ***tab, int *count);
int						check_blank_line(char *str);
int						ft_isspace(char c);
int						one_of(char c);
void					free_it(t_content **list);
int						label_replace(t_content **list, t_content *begin);
void					rmvchar(char *str);
int						ft_strisuint(char *arg);
int						ft_strisint(char *arg);
int						reg_check(char c, char *value);
int						check_arg(char *str, int *i, t_content **list,
						int count);
void					copy_label(t_content **list, char **label);
unsigned int			total_octet(t_content *list);
int						header_initialize(t_header *header, int *i, int fd);
char					*allocate_new(char *str, int nb);
void					new_file(char *file, t_content *list, t_header *header);
int						check_file_name(char *file);
t_content				*check_this_line(char *str, int i);
int						good_check_redirect(char *str, t_op tab,
						int *i, t_content **list);
int						is_it_good(char c, int mask);
char					update_octet(unsigned char octet, int j,
						char c, t_content **list);
void					correction(t_content **list, t_op tab);
void					starting_cmp(char *str, char *cmp, int *i, int *j);
int						check_arg_hexa(int j, char **cpy,
						t_content **list, int count);
int						good_len(char *str, int len, int ind);
void					list_modif(t_content **list);
#endif
