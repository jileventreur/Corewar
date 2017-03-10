/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 23:06:55 by nbelouni          #+#    #+#             */
/*   Updated: 2017/01/31 18:03:36 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H
# define CELL_LEN		4
# define INFO_HEIGHT	18
# define INFO_WIDTH		150
# define PLAYER_COL		14
# include "corewar.h"

typedef struct s_vm		t_vm;
WINDOW					*g_scr_infos;

void					nprint_vm(t_vm *vm);
void					nprint_procs(t_vm *vm);
void					nprint_infos(t_vm *vm, int fps);
void					get_input_and_fsp(int *ch, int *refresh_speed);
void					print_all(t_vm *vm, int refresh_speed);
int						valid_infos_window(int *line);
int						get_prog_max_len(t_vm *vm);
void					print_players(t_vm *vm, int all_procs, int *p);
void					print_wait_end(t_vm *vm);

#endif
