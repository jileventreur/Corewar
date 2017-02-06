/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 07:41:02 by cadam             #+#    #+#             */
/*   Updated: 2016/12/11 07:41:03 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "libft.h"
# include <stdio.h>

# define CONV 18
# define COLOR 23
# define BUF_SIZE (256)
# define LOWER_HEX_DIGITS "0123456789abcdef"
# define UPPER_HEX_DIGITS "0123456789ABCDEF"
# define STR_CONV "sSpdDioOuUxXcC%bB"
# define CONV 18

# define PUTCHAR(c)	(*g_char)(c);
# define PUTSTR(str) (*g_str)(str);
# define END (*g_end)();

typedef struct	s_buf
{
	int			fd;
	char		buf[BUF_SIZE];
	size_t		len;
}				t_buf;

typedef struct	s_flags
{
	int			conv;
	int			nb_opt;
	int			minus;
	int			plus;
	int			hash;
	int			zero;
	int			space;
	int			min_width;
	int			precision;
	int			hh;
	int			h;
	int			l;
	int			ll;
	int			j;
	int			z;
}				t_flags;

typedef struct	s_conv
{
	char		c;
	int			(*pf_conv_exec)(va_list *, t_flags);
}				t_conv;

typedef struct	s_color
{
	char		*id;
	char		*name;
}				t_color;

typedef struct	s_len
{
	int			len;
	int			old_len;
}				t_len;

void			(*g_char) (char);
void			(*g_str) (char *);
void			(*g_end) (void);
int				g_fd;
char			*g_ret;
t_buf			g_buf;
t_conv			g_conv[CONV];
t_color			g_color[COLOR];

int				ft_general_print(const char *format, va_list *args);

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_asprintf(char **ret, const char *format, ...);

void			pf_putbuf(void);
void			pf_putchar_buf(char c);
void			pf_putstr_buf(char *str);

void			pf_malloc_put(void);
void			pf_malloc_char(char c);
void			pf_malloc_str(char *str);

int				pf_is_conv(char c);
int				pf_conv(va_list *args, const char *format, int *pos);

int				pf_conv_b(va_list *args, t_flags flags);
int				pf_conv_majb(va_list *args, t_flags flags);
int				pf_conv_c(va_list *args, t_flags flags);
int				pf_conv_d(va_list *args, t_flags flags);
int				pf_conv_invalid(t_flags flags, char c);
int				nb_bits(unsigned int nb);
int				two_oct(unsigned int a);
int				three_oct(unsigned int a);
int				four_oct(unsigned int a);
int				pf_conv_majc(va_list *args, t_flags flags);
int				pf_conv_majd(va_list *args, t_flags flags);
int				pf_conv_majo(va_list *args, t_flags flags);
int				size_wchar(unsigned int a);
int				ft_wstrlen_flag(t_flags flags, wchar_t *str);
int				bits_to_otc(int bits);
int				write_wchar(t_flags flags, int *cpt, unsigned int a);
int				pf_conv_majs(va_list *args, t_flags flags);
int				pf_conv_maju(va_list *args, t_flags flags);
int				pf_conv_majx(va_list *args, t_flags flags);
int				pf_conv_majxl(va_list *args, t_flags flags);
int				pf_conv_n(va_list *args, char c, int *n, int ret);
int				pf_conv_o(va_list *args, t_flags flags);
int				pf_conv_p(va_list *args, t_flags flags);
int				pf_conv_percent(va_list *args, t_flags flags);
int				pf_conv_s(va_list *args, t_flags flags);
int				pf_conv_u(va_list *args, t_flags flags);
int				pf_conv_x(va_list *args, t_flags flags);
int				pf_conv_xl(va_list *args, t_flags flags);

int				pf_flag_hash(t_flags flags, int *ret, int nb);
void			pf_flag_min_width(t_flags flags, int len, int *ret, int write);
void			pf_flag_plus_len(t_flags flags, int *len, long nb);
void			pf_flag_plus(t_flags flags, int *ret, long nb);
int				pf_flag_precision_zero(t_flags flags);
void			pf_flag_precision(t_flags flags, int len, int nb, int *ret);
void			pf_flag_space(t_flags flags, int *ret);

t_flags			pf_flags_init(void);
int				flag_is_number(t_flags flags);
int				flag_is_char(t_flags flags);

int				pf_is_flag(char c);
int				pf_flags_check_min_width(t_flags *flags, const char *format,
				int *pos);
int				pf_flags_check_precision(t_flags *flags, const char *format,
				int *pos);
int				pf_flags_check_wildcard(t_flags *flags, const char *format,
				int *pos, va_list *args);
int				pf_flags_check(va_list *args, t_flags *flags,
				const char *format, int *pos);

int				ft_isanyof(char c, char *str);
int				ft_wstrlen(wchar_t *str);

/*
**	+------------ BITS OPT ------------+
**	|                                  |
**	|  - bit 0 = uppercase             |
**	|  - bit 1 = signed or unsigned    |
**	|  - bit 2 = positive or negative  |
**	|                                  |
**	+----------------------------------+
*/
void			print_base_int(unsigned int nb, const unsigned int base,
				unsigned int opt);
int				len_base_int(unsigned int nb, const unsigned int base, int cpt,
				unsigned int opt);
void			print_base_long(unsigned long nb, const unsigned int base,
				unsigned int opt);
int				len_base_long(unsigned long nb,
				const unsigned int base, int cpt, unsigned int opt);

void			ft_putbasechar(char nb, unsigned int opt);

void			ft_putlnbr_base(unsigned long int nb, const unsigned int base,
				const char *digits);
void			ft_putnbr_base(unsigned int nb, const unsigned int base,
				const char *digits);
#endif
