#include "corewar.h"

static void			epur_proc(t_list **lst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*tmp;
	
	cur = *lst;
	prev = NULL;
	while (cur)
		if (((t_proc *)cur->content)->life & 0b1)
		{
			((t_proc *)cur->content)->life |= 0b0;
			prev = cur;
			cur = cur->next;
		}
		else
		{
			printf("proc %d has been destroy\n", ((t_proc *)cur->content)->num);
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

void	checks_and_destroy(t_vm *vm)
{
	++vm->total_cycle;
	if (vm->next_live_check--)		
		return ;
	if (vm->live_num >= NBR_LIVE || vm->last_ctd_dec == MAX_CHECKS)
	{
		vm->ctd -= CYCLE_DELTA;
		vm->last_ctd_dec = 0;
	}
	else
		++vm->last_ctd_dec;
	vm->next_live_check = vm->ctd;
	vm->live_num = 0;
	epur_proc(&vm->plst);
}