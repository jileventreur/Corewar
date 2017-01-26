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
			p->life ^= 0b1;
			prev = cur;
			cur = cur->next;
		}
		else
		{
			++vm->procs_death_nb;
			--vm->c[p->player_num - 1].procs; // PROCS CPT UPDT
			// exit(1);
			if (ISACTIV(vm->opt.v, 3))
				printf("Process %u hasn't lived for %lld cycles (CTD %lld)\n", p->proc_num, 
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
		}
	}
}


void	checks_and_destroy(t_vm *vm)
{
	if (--vm->next_live_check > 0)
		return ;
	epur_proc(vm, &vm->plst);
	if (vm->live_num >= NBR_LIVE || vm->last_ctd_dec == MAX_CHECKS)
	{
	 	vm->ctd -= CYCLE_DELTA;
		vm->last_ctd_dec = 1;
		if (ISACTIV(vm->opt.v, 1))
			printf("Cycle to die is now %lld\n", vm->ctd);
	}
	else
		++vm->last_ctd_dec;
	vm->next_live_check = vm->ctd;
	vm->live_num = 0;
	
}