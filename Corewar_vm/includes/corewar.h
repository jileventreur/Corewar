/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jilano <jilano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 22:40:53 by cadam             #+#    #+#             */
/*   Updated: 2017/02/13 14:56:03 by nbelouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <curses.h>
# include "window.h"

# define BS(num) (((num >> 8) & 0xff00) | ((num << 24) & 0xff000000))
# define BSWAP_32(n) (((n >> 24) & 0xff) | ((n << 8) & 0xff0000) | BS(n))
# define BSWAP_16(num) ((num >> 8) | (num << 8))

# define DIR_SIZE				2
# define REG_SIZE				4
# define IND_SIZE				4

typedef enum	e_type_code
{
	NULL_CODE,
	REG_CODE,
	DIR_CODE,
	IND_CODE
}				t_type_code;

# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE (4*1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)
# define INSTR_NUMBER (16)

# define COMMENT_CHAR '#'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','

# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"

# define REG_NUMBER (16)

# define CYCLE_TO_DIE (1536)
# define CYCLE_DELTA (50)
# define NBR_LIVE (21)
# define MAX_CHECKS (10)

# define BYTE_LINE_NB (32)
# define PC_INC (4u)

# define REG(num) (*(int *)(proc->reg[num - 1]))

# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8

# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC (0xea83f3)

# define CLEAR_SCREEN			"\e[1;1H\e[2J"

typedef char					t_arg_type;

typedef long long int			t_lint;

enum							e_instruction
{
	LIVE,
	LD,
	ST,
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	ZJMP,
	LDI,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF
};

# define OPTION "adghsv"

typedef struct					s_opt
{
	char						a;
	long int					d;
	char						g;
	char						h;
	unsigned int				s;
	char						v;
}								t_opt;

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

typedef struct					s_champion
{
	t_header					header;
	unsigned char				prog[CHAMP_MAX_SIZE + 1];
	unsigned int				num;
	unsigned int				procs;
}								t_champion;

typedef	struct					s_proc
{
	char						reg[REG_NUMBER][REG_SIZE];
	int							pc;
	unsigned char				carry;
	unsigned char				life;
	t_lint						last_live;
	unsigned int				player_num;
	unsigned int				proc_num;
	int							cycle_to_wait;
	unsigned char				inst;
}								t_proc;

typedef	struct					s_vm
{
	t_opt						opt;
	unsigned char				mem[MEM_SIZE];
	unsigned char				proc_mem[MEM_SIZE];
	unsigned int				list_len;
	t_list						*plst;
	unsigned int				n_players;
	t_champion					c[MAX_PLAYERS];
	t_lint						ctd;
	unsigned int				procs_death_nb;
	unsigned int				last_live;
	unsigned int				live_num;
	int							next_live_check;
	unsigned int				last_ctd_dec;
	t_lint						total_cycle;
}								t_vm;

typedef struct					s_arg
{
	t_type_code					type;
	unsigned int				size;
	int							data;
	int							value;
}								t_arg;

typedef struct					s_op
{
	char						*name;
	unsigned int				param_number;
	unsigned char				param_mask[MAX_ARGS_NUMBER];
	unsigned char				opcode;
	unsigned int				cycle;
	char						*desc;
	unsigned char				direct_adr;
	unsigned char				long_inst;
	unsigned char				ocp;
	void						(*f)(t_vm *, t_proc *, t_arg *);
}								t_op;

t_list							*ft_lstnew(void const *content,
								size_t content_size);

void							ft_lstadd(t_list **alst, t_list *new);

int								get_players(char **argv, int argc,
								t_champion *tab);

void							vm_init(t_vm *vm, int argc, char **argv);

void							get_proc_cycle(t_proc *proc,
								unsigned char *mem);

void							print_args(t_arg *args, unsigned int arg_number,
								unsigned char long_inst, unsigned char dest);
void							print_procs(t_vm *vm, t_list *lst,
								unsigned char print_reg);

void							moove_pc(t_vm *vm, t_proc *proc,
								unsigned int value);

void							my_live(t_vm *vm, t_proc *proc, t_arg *args);
void							my_ld(t_vm *vm, t_proc *proc, t_arg *args);
void							my_st(t_vm *vm, t_proc *proc, t_arg *args);
void							my_add(t_vm *vm, t_proc *proc, t_arg *args);
void							my_sub(t_vm *vm, t_proc *proc, t_arg *args);
void							my_and(t_vm *vm, t_proc *proc, t_arg *args);
void							my_or(t_vm *vm, t_proc *proc, t_arg *args);
void							my_xor(t_vm *vm, t_proc *proc, t_arg *args);
void							my_zjmp(t_vm *vm, t_proc *proc, t_arg *args);
void							my_ldi(t_vm *vm, t_proc *proc, t_arg *args);
void							my_sti(t_vm *vm, t_proc *proc, t_arg *args);
void							my_fork(t_vm *vm, t_proc *proc, t_arg *args);
void							my_lld(t_vm *vm, t_proc *proc, t_arg *args);
void							my_lldi(t_vm *vm, t_proc *proc, t_arg *args);
void							my_lfork(t_vm *vm, t_proc *proc, t_arg *args);
void							my_aff(t_vm *vm, t_proc *proc, t_arg *args);

void							print_usage();

void							checks_and_destroy(t_vm *vm);

int								get_args(t_vm *vm, t_proc *proc,
								t_arg *args, t_op *inst);
t_lint							get_arg_data(unsigned char *mem,
								int beg, unsigned int len);

void							get_opt(char ***argv_source,
								int *argc, t_opt *opt);

void							print_vm(t_vm *vm);

void							exec_vm(t_vm *vm);
void							is_end_corewar(int ch);
void							print_wait_end(t_vm *vm);

int								ft_round(double nb);

#endif
