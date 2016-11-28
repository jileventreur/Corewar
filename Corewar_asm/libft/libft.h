/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 12:05:02 by darabi            #+#    #+#             */
/*   Updated: 2015/12/12 17:00:46 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
# include <inttypes.h>

# define BUFF_SIZE 1

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_issign(char c);
int					get_next_line(int const fd, char **line);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_del(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *str);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *str1, const char *str2);
char				*ft_strncat(char *str1, const char *str2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
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

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_striter(char *s, void (*f)(char *));
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

void				ft_swap(int *a, int *b);
t_list				*ft_list_last(t_list *begin_list);
char				*ft_strrev(char *str);
int					ft_int_size(int n);
int					ft_recursive_power(int nb, int power);
void				ft_puttab(char **tab);

int					ft_printf(const char *format, ...);

wchar_t				*first_test(const char format, va_list ap, int *count);
wchar_t				*first_letter_test_l(const char format,\
					va_list ap, int *count);
wchar_t				*first_letter_test_h(const char format,\
					va_list ap, int *count);
wchar_t				*first_letter_test_ll(const char format,\
					va_list ap, int *count);
wchar_t				*first_letter_test_hh(const char format,\
					va_list ap, int *count);
wchar_t				*first_letter_test_j(const char format,\
					va_list ap, int *count);
wchar_t				*first_letter_test_z(const char format,\
					va_list ap, int *count);
char				*get_color(const char *format);
wchar_t				*ft_strdup_wchar_to_wchar(wchar_t *str);
void				ft_del_str(wchar_t **str, wchar_t **arg);

void				n_func(va_list ap, wchar_t *str, wchar_t **arg);
int					checking_for_minus(char *flags, int *width);
int					checking_for_hashtag(char *flags);
int					checking_for_plus(char *flags);
int					checking_for_zero(char *flags);
int					checking_for_space(char *flags);

int					minimal_width(const char *str, int *i, va_list ap);
wchar_t				*minimal_width_applying(wchar_t **arg, int width,\
					char letter);
wchar_t				*applying_precision(wchar_t **arg, int p,\
					const char letter);
wchar_t				*applying_flags(wchar_t **arg, char *flags,\
					char letter, int width);
wchar_t				*zero_conversion(wchar_t **arg, int width,\
							char letter, int hashtag);
wchar_t				*hashtag_conversion(wchar_t **arg, char letter);

char				*check_same_flags(const char *format, int *i,\
					int zero, int hashtag);
int					precision(const char *str, int *i, va_list ap);
wchar_t				*check_conv_flags(const char *format, va_list ap,\
					int *i, int *conv);

int					ft_strlen_to(const char *format, int *i);
wchar_t				*changing_malloc(wchar_t **str, const char *format,\
					int *i, int count);
void				add_char(wchar_t **str, const char *format,\
					int *i, int count);
wchar_t				*add_arg(wchar_t **str, wchar_t **arg, char a, int *count);
wchar_t				*to_str(char c);
wchar_t				*to_str_c(char c, int *count);
wchar_t				*ft_add_p(wchar_t *str);
wchar_t				*to_str_p(char c);
wchar_t				*ft_strncpy_wchar(wchar_t *dst,\
					const wchar_t *src, size_t n);

wchar_t				*ft_itoa_unsigned_ll(unsigned long long n, int base, int x);
wchar_t				*ft_itoa_signed_ll(long long n, int base);

wchar_t				*ft_strdup_wchar(const char *str);
int					ft_strlen_null(wchar_t *str, int count);
void				ft_strcpy_null(wchar_t **dst, wchar_t *src, int count);

char				*add_color(char **str, char *arg);
char				*changing_malloc_color(char **str,\
					const char *format, int *i);
int					ft_putwstr(wchar_t **str, int count);
int					mask_unicode_2(unsigned int v);
int					mask_unicode_3(unsigned int v);
int					mask_unicode_4(unsigned int v);
void				reverse(wchar_t **str);
wchar_t				*to_str_w(wchar_t c, int *count);
int					wstr_len(wchar_t *str);
int					wchar_len(wchar_t wc);
long				ft_watoi(const wchar_t *str);
void				initialize_three(int *a, int *b, int *c);
int					valid_letter(const char letter);
wchar_t				*ft_wcharnew(wchar_t *str, int i);
char				*ft_strdup_color(char *color, char **arg);

#endif
