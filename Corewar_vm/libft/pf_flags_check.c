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

int		pf_flags_check_min_width(t_flags *flags, const char *format, int *pos)
{
	char	c;

	c = format[*pos];
	if (c >= '1' && c <= '9')
	{
		flags->min_width = ft_atoi(format + *pos);
		*pos += ft_intlen(flags->min_width) - 1;
		return (1);
	}
	return (0);
}

int		pf_flags_check_precision(t_flags *flags, const char *format, int *pos)
{
	char	c;

	c = format[*pos];
	if (c == '.')
	{
		flags->precision = ft_atoi(format + *pos + 1);
		*pos -= (!ft_isdigit(format[*pos + 1])) ? 1 : 0;
		*pos += ft_intlen(flags->precision);
		return (1);
	}
	return (0);
}

int		pf_flags_check_wildcard(t_flags *flags, const char *format,
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
		return (1);
	}
	return (0);
}

int		pf_flags_inside(t_flags *flags, char c, char c1)
{
	if (c == '-')
		flags->minus = 1;
	else if (c == '+')
		flags->plus = 1;
	else if (c == '#')
		flags->hash = 1;
	else if (c == '0')
		flags->zero = 1;
	else if (c == ' ')
		flags->space = 1;
	else if (c == 'h')
		if (c1 == 'h')
			flags->hh = 1;
		else
			flags->h = 1;
	else if (c == 'h')
		flags->h = 1;
	else if (c == 'l')
		if (c1 == 'l')
			flags->ll = 1;
		else
			flags->l = 1;
	else
		return (0);
	return (1);
}

int		pf_flags_check(va_list *args, t_flags *flags, const char *format,
		int *pos)
{
	char	c;
	char	c1;

	c = format[*pos];
	c1 = (format[*pos + 1]) ? format[*pos + 1] : 0;
	if (pf_flags_inside(flags, c, c1))
		return (0);
	else if (c == 'j')
		flags->j = 1;
	else if (c == 'z')
		flags->z = 1;
	else if ((pf_flags_check_min_width(flags, format, pos) +
	pf_flags_check_precision(flags, format, pos) +
	pf_flags_check_wildcard(flags, format, pos, args)) == 0)
		return (1);
	return (0);
}
