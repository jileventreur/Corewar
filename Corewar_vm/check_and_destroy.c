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
			--vm->list_len;
		}
	}
}

void	checks_and_destroy(t_vm *vm)
{
	if (--vm->next_live_check > 0)
		return ;
	// if (vm->total_cycle == 26494)
	// {
	// 	printf("next_live_check = %u\n", vm->next_live_check);
	// 	printf("live_num = %u\n", vm->live_num);
	// 	printf("last_ctd_dec == %u\n", vm->last_ctd_dec);
	// 	exit(1);
	// }
	if (vm->live_num >= NBR_LIVE || vm->last_ctd_dec == MAX_CHECKS)
	{
	 	vm->ctd -= CYCLE_DELTA;
		vm->last_ctd_dec = 1;
		// printf("HEY! vm->ctd = %lld\n", vm->ctd);
		// printf("Cycle = %lld\n", vm->total_cycle);
		// exit(1);
		if (ISACTIV(vm->opt.v, 1))
			printf("Cycle to die is now %lld\n", vm->ctd);
	}
	else
		++vm->last_ctd_dec;
	vm->next_live_check = vm->ctd;
	vm->live_num = 0;
	epur_proc(vm, &vm->plst);
	// printf("next_live_check = %u\n", vm->next_live_check);
	// exit(1);
	// exit(1);
	
}