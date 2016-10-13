#include "corewar.h"

void	ft_error_exit(const char *exit_message)
{
	ft_puterror(exit_message);
	exit(1);
}

void	get_proc_cycle(t_proc *proc, unsigned char *mem)
{
	unsigned char	c;
	extern t_op		op_tab[17];

	c = mem[proc->pc] - 1;
	if (c > 16)
	{
		// 2f("%u (0x%x) n'est pas une instruction\n",c + 1,c + 1 );
		proc->cycle_to_wait = 1;
	}
	else
 	{
		proc->cycle_to_wait = op_tab[c].cycle;
 		// printf("ctw = %u\n", proc->cycle_to_wait);
		// printf("l'op code 0x%2.2x correspond a l'instruction %s\n", c, op_tab[c].name);
  	}
}

void	epur_proc(t_list **lst)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*tmp;
	
	cur = *lst;
	prev = NULL;
	while (cur)
		if (!((t_proc *)cur->content)->life)
		{
			tmp = cur->next;
			free(cur->content);
			free(cur);
			cur = tmp;
			if (!prev)
				*lst = tmp;
			else
				prev->next = cur;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
}

void	checks_and_destroy(t_vm *vm)
{
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
	// ((t_proc *)vm->plst->next->content)->life = 1;
		print_procs(vm->plst);
	epur_proc(&vm->plst);
	print_procs(vm->plst);
	// exit (1);
}

void		instruction_manager(t_vm *vm, t_proc *proc)
{
	(void)vm;
	(void)proc;
}

void	exec_procs(t_vm *vm)
{
	t_list	*tmp;
	t_proc	*p;
	
	tmp = vm->plst;
	while (tmp)
	{
		p = (t_proc *)tmp->content;
		if (p->cycle_to_wait == 0)
		{
			instruction_manager(vm, p);
			get_proc_cycle(p, vm->mem);
		}
		else
			--p->cycle_to_wait;
		tmp = tmp->next;
	}
}

void	main_loop(t_vm *vm)
{
	while (vm->plst)
	{
		// printf("yo\n");
		exec_procs(vm);
		checks_and_destroy(vm);
	}
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	if (argc == 1)
		ft_error_exit("Error: not enough args\n");
	// if (argc > MAX_PLAYERS + 1)
		// ft_error_exit("Error: too much args\n");
	--argc;
	++argv;
	vm_init(&vm, argc, argv);
	// get_champion(argv[1], &c);
	// print_champions(vm.c);
	// printf("\n");
	// print_procs(vm.plst);
	// print_memory(vm.mem, MEM_SIZE);
	main_loop(&vm);
	// lst = lst->next;
	// printf("la case contient: [%x]\n", mem[((t_proc *)lst->content)->pc]);
	return (0);
}