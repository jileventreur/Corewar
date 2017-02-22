/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 16:37:50 by cadam             #+#    #+#             */
/*   Updated: 2015/12/16 14:18:57 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define DEC(bit) (1 << bit)
# define ACTIV_BIT(var, bit) (var |= DEC(bit))
# define DESACTIV_BIT(var, bit) (var &= ~(DEC(bit)))
# define ISACTIV(var, bit) (var & DEC(bit))

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef int			(*t_cmp)(t_list *, t_list *);

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isspace(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_strtolower(char *str);

void				ft_merge_sort(int **tab, int len);
void				ft_selection_sort(int **tab, int len);
void				ft_quick_sort(int **tab, int len);
void				ft_selection_sort(int **tab, int len);

t_list				*ft_lst_bubble_sort(t_list *begin, t_cmp cmp);
t_list				*ft_lst_merge_sort(t_list *lst, t_cmp cmp);

int					ft_pow(int n, int p);
int					ft_intlen(int n);
char				*ft_epurspace(char *str);
char				**ft_chrchrdup(char **tab);
void				ft_free_chrchr(char ***tab);
int					ft_stdrlstcount(t_list *lst);
int					ft_puterror(const char *str);
int					ft_str_nocase_cmp(const char *s1, const char *s2);
char				*ft_strpathjoin(const char *s1, const char *s2);
void				ft_strtoupper(char *str);
char				*ft_strsupchar(char *str, char c);
float				ft_sqrt(float s);
int					ft_int_div_round_up(int nb, int div);

int					ft_strisint(char *arg);
int					ft_strisuint(char *arg);
int					ft_memisset(void *p, size_t n, char c);
void				ft_error_exit(const char *exit_message);
int					ft_atou(const char *str);

#endif
