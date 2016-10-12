/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flags_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:20:39 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:20:42 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_is_flag(char c)
{
	int		i;

	if (!ft_isanyof(c, "#0-+ 123456789.hljz*"))
		return (0);
	i = 0;
	while (g_conv[i].c)
	{
		if (g_conv[i].c == c)
			return (0);
		i++;
	}
	return (1);
}

void	pf_flags_check_min_width(t_flags *flags, const char *format, int *pos)
{
	char	c;

	c = format[*pos];
	if (c >= '1' && c <= '9')
	{
		flags->min_width = ft_atoi(format + *pos);
		*pos += ft_intlen(flags->min_width) - 1;
	}
}

void	pf_flags_check_precision(t_flags *flags, const char *format, int *pos)
{
	char	c;

	c = format[*pos];
	if (c == '.')
	{
		flags->precision = ft_atoi(format + *pos + 1);
		*pos -= (!ft_isdigit(format[*pos + 1])) ? 1 : 0;
		*pos += ft_intlen(flags->precision);
	}
}

void	pf_flags_check_wildcard(t_flags *flags, const char *format,
	int *pos, va_list *args)
{
	char	c;
	int		wildcard;

	c = format[*pos];
	if (c == '*')
	{
		wildcard = va_arg(*args, int);
		if (*pos - 1 > -1 && format[*pos - 1] && format[*pos - 1] == '.')
		{
			if (wildcard > -1)
				flags->precision = wildcard;
			else
				flags->precision = -1;
		}
		else
		{
			if (wildcard < 0)
				flags->minus = 1;
			flags->min_width = (wildcard < 0) ? -wildcard : wildcard;
		}
	}
}

int		pf_flags_check(va_list *args, t_flags *flags, const char *format,
	int *pos)
{
	char	c;
	char	c1;

	c = format[*pos];
	c1 = (format[*pos + 1]) ? format[*pos + 1] : 0;
	if (!pf_is_flag(c))
		return (1);
	flags->minus = (flags->minus || c == '-') ? 1 : 0;
	flags->plus = (flags->plus || c == '+') ? 1 : 0;
	flags->hash = (flags->hash || c == '#') ? 1 : 0;
	flags->zero = (flags->zero || c == '0') ? 1 : 0;
	flags->space = (flags->space || c == ' ') ? 1 : 0;
	flags->hh = (flags->hh || (c == 'h' && c1 == 'h')) ? 1 : 0;
	flags->h = (flags->h || c == 'h') ? 1 : 0;
	flags->l = (flags->l || c == 'l') ? 1 : 0;
	flags->ll = (flags->ll || (c == 'l' && c1 == 'l')) ? 1 : 0;
	flags->j = (flags->j || c == 'j') ? 1 : 0;
	flags->z = (flags->z || c == 'z') ? 1 : 0;
	pf_flags_check_min_width(flags, format, pos);
	pf_flags_check_precision(flags, format, pos);
	pf_flags_check_wildcard(flags, format, pos, args);
	return (0);
}
