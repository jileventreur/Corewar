/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:43:59 by darabi            #+#    #+#             */
/*   Updated: 2015/12/04 14:22:14 by darabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static wchar_t		*second_letter_test_h(const char format, va_list ap)
{
	if (format == '%')
		return (to_str('%'));
	if (format == 'p')
		return (ft_itoa_unsigned_ll((unsigned long)va_arg(ap, void *), 16, 0));
	if (format == 'u')
		return (ft_itoa_unsigned_ll((unsigned short)va_arg(ap, int), 10, 0));
	if (format == 'U')
		return (ft_itoa_unsigned_ll(va_arg(ap, long), 10, 0));
	if (format == 'o')
		return (ft_itoa_unsigned_ll((unsigned short)va_arg(ap, int), 8, 0));
	if (format == 'O')
		return (ft_itoa_unsigned_ll(va_arg(ap, int), 8, 0));
	if (format == 'x')
		return (ft_itoa_unsigned_ll((unsigned short)va_arg(ap, int), 16, 0));
	if (format == 'X')
		return (ft_itoa_unsigned_ll((unsigned short)va_arg(ap, int), 16, 1));
	return (NULL);
}

wchar_t				*first_letter_test_h(const char format,\
					va_list ap, int *count)
{
	if (format == 'd' || format == 'i')
		return (ft_itoa_signed_ll((short)va_arg(ap, int), 10));
	if (format == 'D' || format == 'I')
		return (ft_itoa_signed_ll(va_arg(ap, long long), 10));
	if (format == 's')
		return (ft_strdup_wchar(va_arg(ap, char *)));
	if (format == 'S')
		return (ft_strdup_wchar_to_wchar(va_arg(ap, wchar_t *)));
	if (format == 'c')
		return (to_str((char)va_arg(ap, int)));
	if (format == 'C')
		return (to_str_w(va_arg(ap, wchar_t), count));
	if (format == 'b')
		return (ft_itoa_unsigned_ll((short)va_arg(ap, int), 2, 0));
	return (second_letter_test_h(format, ap));
}

static wchar_t		*second_letter_test_hh(const char format, va_list ap)
{
	if (format == '%')
		return (to_str('%'));
	if (format == 'p')
		return (ft_itoa_unsigned_ll((unsigned long)va_arg(ap, void *), 16, 0));
	if (format == 'u')
		return (ft_itoa_unsigned_ll((unsigned char)va_arg(ap, int), 10, 0));
	if (format == 'U')
		return (ft_itoa_unsigned_ll((unsigned short)va_arg(ap, int), 10, 0));
	if (format == 'o')
		return (ft_itoa_unsigned_ll((unsigned char)va_arg(ap, int), 8, 0));
	if (format == 'O')
		return (ft_itoa_unsigned_ll((unsigned short)va_arg(ap, int), 8, 0));
	if (format == 'x')
		return (ft_itoa_unsigned_ll((unsigned char)va_arg(ap, int), 16, 0));
	if (format == 'X')
		return (ft_itoa_unsigned_ll((unsigned char)va_arg(ap, int), 16, 1));
	return (NULL);
}

wchar_t				*first_letter_test_hh(const char format,\
				va_list ap, int *count)
{
	if (format == 'd' || format == 'i')
		return (ft_itoa_signed_ll((char)va_arg(ap, int), 10));
	if (format == 'D' || format == 'I')
		return (ft_itoa_signed_ll(va_arg(ap, long long), 10));
	if (format == 'S')
		return (ft_strdup_wchar_to_wchar(va_arg(ap, wchar_t *)));
	if (format == 's')
		return (ft_strdup_wchar(va_arg(ap, char *)));
	if (format == 'c')
		return (to_str((char)va_arg(ap, int)));
	if (format == 'C')
		return (to_str_w(va_arg(ap, wchar_t), count));
	if (format == 'b')
		return (ft_itoa_unsigned_ll((char)va_arg(ap, int), 2, 0));
	return (second_letter_test_hh(format, ap));
}
