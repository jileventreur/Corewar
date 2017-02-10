/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 20:24:34 by cadam             #+#    #+#             */
/*   Updated: 2017/01/31 20:43:54 by cadam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	delete_proc(t_vm *vm, t_list **lst, t_list **prev, t_list **cur)
{
	t_proc	*p;
	t_list	*tmp;

	p = (*cur)->content;
	++vm->procs_death_nb;
	--vm->c[p->player_num - 1].procs;
	if (!vm->opt.g && ISACTIV(vm->opt.v, 3))
		ft_printf("Process %u hasn't lived for %lld cycles (CTD %lld)\n",
		p->proc_num, vm->total_cycle - p->last_live, vm->ctd);
	tmp = (*cur)->next;
	free((*cur)->content);
	(*cur)->content = NULL;
	free(*cur);
	*cur = tmp;
	if (!(*prev))
		*lst = tmp;
	else
		(*prev)->next = *cur;
}

static void	epur_procs(t_vm *vm, t_list **lst)
{
	t_list	*prev;
	t_list	*cur;

	cur = *lst;
	prev = NULL;
	while (cur)
	{
		if (((t_proc *)cur->content)->life & 0b1)
		{
			((t_proc *)cur->content)->life ^= 0b1;
			prev = cur;
			cur = cur->next;
		}
		else
		{
			delete_proc(vm, lst, &prev, &cur);
		}
	}
}

void		checks_and_destroy(t_vm *vm)
{
	if (--vm->next_live_check > 0)
		return ;
	epur_procs(vm, &vm->plst);
	if (vm->live_num >= NBR_LIVE || vm->last_ctd_dec == MAX_CHECKS)
	{
		vm->ctd -= CYCLE_DELTA;
		vm->last_ctd_dec = 1;
		if (!vm->opt.g && ISACTIV(vm->opt.v, 1))
			ft_printf("Cycle to die is now %lld\n", vm->ctd);
	}
	else
		++vm->last_ctd_dec;
	vm->next_live_check = vm->ctd;
	vm->live_num = 0;
}
