/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 23:06:55 by nbelouni          #+#    #+#             */
/*   Updated: 2017/01/02 23:13:40 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
#define WINDOW_H
#include "corewar.h"

#define CELL_LEN	4

typedef struct s_vm t_vm;

void           nprint_vm(t_vm *vm);
void           nprint_procs(t_vm *vm);


#endif
