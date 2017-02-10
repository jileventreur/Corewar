/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2016/12/03 13:42:17 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op	g_op_tab[INSTR_NUMBER + 1] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 0, &my_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 0, 0, 1, &my_ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 0, 0, 1, &my_st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 0, 0, 1, &my_add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 0, 0, 1, &my_sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r11, &r2 -> r3", 0, 0, 1, &my_and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 0, 0, 1, &my_or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 0, 0, 1, &my_xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 1, 0, 0, &my_zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 0, 1, &my_ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 0, 1, &my_sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 1, 0, 0, &my_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 0, 1, 1, &my_lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 1, &my_lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 1, 1, 0, &my_lfork},
	{"aff", 1, {T_REG}, 16, 2, "aff", 0, 0, 1, &my_aff},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0, NULL}
};
