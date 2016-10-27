/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_conv_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 20:09:49 by cadam             #+#    #+#             */
/*   Updated: 2015/05/11 20:09:51 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pf_conv_r3(char c, int *ret)
{
	if (c == 22)
		pf_putstr("[syn]", ret);
	else if (c == 23)
		pf_putstr("[etb]", ret);
	else if (c == 24)
		pf_putstr("[can]", ret);
	else if (c == 25)
		pf_putstr("[em]", ret);
	else if (c == 26)
		pf_putstr("[sub]", ret);
	else if (c == 27)
		pf_putstr("[esc]", ret);
	else if (c == 28)
		pf_putstr("[fs]", ret);
	else if (c == 29)
		pf_putstr("[gs]", ret);
	else if (c == 30)
		pf_putstr("[rs]", ret);
	else if (c == 31)
		pf_putstr("[us]", ret);
	else if (c == 127)
		pf_putstr("[del]", ret);
	else
		pf_putstr("[?]", ret);
}

static void	pf_conv_r2(char c, int *ret)
{
	if (c == 11)
		pf_putstr("[vt]", ret);
	else if (c == 12)
		pf_putstr("[np]", ret);
	else if (c == 13)
		pf_putstr("[cr]", ret);
	else if (c == 14)
		pf_putstr("[so]", ret);
	else if (c == 15)
		pf_putstr("[si]", ret);
	else if (c == 16)
		pf_putstr("[dle]", ret);
	else if (c == 17)
		pf_putstr("[dc1]", ret);
	else if (c == 18)
		pf_putstr("[dc2]", ret);
	else if (c == 19)
		pf_putstr("[dc3]", ret);
	else if (c == 20)
		pf_putstr("[dc4]", ret);
	else if (c == 21)
		pf_putstr("[nak]", ret);
	else
		pf_conv_r3(c, ret);
}

static void	pf_conv_r1(char c, int *ret)
{
	if (ft_isprint(c))
		pf_putchar(c, ret);
	else if (c == 1)
		pf_putstr("[soh]", ret);
	else if (c == 2)
		pf_putstr("[stx]", ret);
	else if (c == 3)
		pf_putstr("[etx]", ret);
	else if (c == 4)
		pf_putstr("[eot]", ret);
	else if (c == 5)
		pf_putstr("[enq]", ret);
	else if (c == 6)
		pf_putstr("[ack]", ret);
	else if (c == 7)
		pf_putstr("[bel]", ret);
	else if (c == 8)
		pf_putstr("[bs]", ret);
	else if (c == 9)
		pf_putstr("[ht]", ret);
	else if (c == 10)
		pf_putstr("[nl]", ret);
	else
		pf_conv_r2(c, ret);
}

int			pf_conv_r(va_list *args, t_flags flags)
{
	int		i;
	int		ret;
	char	*str;

	(void)flags;
	ret = 0;
	str = va_arg(*args, char *);
	i = 0;
	while (str[i] != 0)
	{
		pf_conv_r1(str[i], &ret);
		i++;
	}
	return (ret);
}
