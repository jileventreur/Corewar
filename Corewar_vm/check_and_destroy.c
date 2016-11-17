#include "corewar.h"

static void			epur_proc(t_vm *vm, t_list **lst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*tmp;
	t_proc	*p;
	
	cur = *lst;
	prev = NULL;
	while (cur)
	{
		p = cur->content;
		if (p->life & 0b1)
		{
			// ft_printf("life == %d\n", p->life); 
			p->life ^= 0b1;
			prev = cur;
			cur = cur->next;
			// ft_printf("life == %d\n", p->life); 
			// ft_printf("Process %u is reinit\n", p->proc_num); 
		}
		else
		{
			if (ISACTIV(vm->opt.v, 3))
				ft_printf("Process %u hasn't lived for %lld cycles (CTD %lld)\n", p->proc_num, 
				vm->total_cycle - p->last_live, vm->ctd);
			tmp = cur->next;
			free(cur->content);
			cur->content = NULL;
			free(cur);
			cur = tmp;
			if (!prev)
				*lst = tmp;
			else
				prev->next = cur;
			--vm->list_len;
		}
	}
}

void	checks_and_destroy(t_vm *vm)
{
	++vm->total_cycle;
	if (vm->next_live_check-- > 0)		
		return ;
	// ft_printf("next_live_check = %u\n", vm->next_live_check);
	if (vm->live_num >= NBR_LIVE || vm->last_ctd_dec == MAX_CHECKS)
	{
	 	vm->ctd -= CYCLE_DELTA;
		vm->last_ctd_dec = 0;
	}
	else
		++vm->last_ctd_dec;
	if (ISACTIV(vm->opt.v, 1))
		ft_printf("Cycle to die is now %lld\n", vm->ctd);
	vm->next_live_check = vm->ctd;
	vm->live_num = 0;
	epur_proc(vm, &vm->plst);
	// exit(1);
	
}