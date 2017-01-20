/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 23:06:55 by nbelouni          #+#    #+#             */
/*   Updated: 2017/01/20 13:48:15 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
#define WINDOW_H
#include "corewar.h"

#define CELL_LEN	4
#define INFO_HEIGHT	10
#define INFO_WIDTH	150
#define PLAYER_COL	14

typedef struct s_vm t_vm;
WINDOW				*g_scr_infos;
//WINDOW				*g_scr_procs;

void			nprint_vm(t_vm *vm);
void			nprint_procs(t_vm *vm);
void			nprint_infos(t_vm * vm);

#endif
