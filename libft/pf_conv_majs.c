/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_majs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:08:52 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:08:55 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	size_wchar(unsigned int a)
{
	int bits;
	int ret;

	bits = nb_bits(a);
	ret = 0;
	if (bits <= 7)
		ret = 1;
	else if (bits <= 11)
		ret = 2;
	else if (bits > 11 && bits <= 16)
		ret = 3;
	else if (bits > 16 && bits <= 21)
		ret = 4;
	return (ret);
}

int	ft_wstrlen_flag(t_flags flags, wchar_t *str)
{
	int i;
	int ret;
	int size;

	i = 0;
	ret = 0;
	size = 0;
	while (str[i])
	{
		size = size_wchar(str[i]);
		if (flags.precision > -1 && ret + size > flags.precision)
			return (ret);
		ret += size;
		i++;
	}
	return (ret);
}

int	bits_to_otc(int bits)
{
	int ret;

	if (bits <= 7)
		ret = 1;
	else if (bits <= 11)
		ret = 2;
	else if (bits > 11 && bits <= 16)
		ret = 3;
	else if (bits > 16 && bits <= 21)
		ret = 4;
	else
		return (-1);
	return (ret);
}

int	write_wchar(t_flags flags, int *cpt, unsigned int a)
{
	int bits;
	int oct;

	bits = nb_bits(a);
	if ((oct = bits_to_otc(bits)) == -1)
		return (-2);
	if (flags.precision > -1 && flags.precision < *cpt + oct)
		return (-1);
	if (bits <= 7)
		*cpt += write(1, &a, 1);
	else if (bits <= 11)
		*cpt += two_oct(a);
	else if (bits > 11 && bits <= 16)
		*cpt += three_oct(a);
	else if (bits > 16 && bits <= 21)
		cpt += four_oct(a);
	else
		return (-2);
	return (0);
}

int	pf_conv_majs(va_list *args, t_flags flags)
{
	wchar_t			*str;
	int				ret;
	int				len;
	int				i;
	int				cpt;

	str = va_arg(*args, wchar_t *);
	if (!str)
		str = L"(null)";
	ret = 0;
	i = 0;
	cpt = 0;
	len = ft_wstrlen_flag(flags, str);
	pf_flag_min_width(flags, len, &ret, 0);
	while (str[i] != 0 && str != NULL && write_wchar(flags, &cpt, str[i]) != -1)
		i++;
	ret += cpt;
	pf_flag_min_width(flags, len, &ret, 1);
	return (ret);
}
