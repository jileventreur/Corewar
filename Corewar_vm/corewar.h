/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadam <cadam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include "window.h"


#define BSWAP_32(num) (((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000))
#define BSWAP_16(num) ((num>>8) | (num<<8))

#define DIR_SIZE				2
#define REG_SIZE				4
#define IND_SIZE				4

typedef enum					e_type_code
{
								NULL_CODE,
								REG_CODE,
								DIR_CODE,
								IND_CODE
}								t_type_code;

#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024) // 4096
#define IDX_MOD					(MEM_SIZE / 8) // 512
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
#define INSTR_NUMBER			16

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

#define BYTE_LINE_NB			64 // must be 32 for main part
#define PC_BIT					0b100 

#define REG(num) 				(*(int *)(proc->reg[num - 1]))

/*
**
*/

typedef char					t_arg_type;

typedef long long int			lint;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define CLEAR_SCREEN			"\e[1;1H\e[2J"

/*
**
*/

enum 							e_instruction 
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

#define	OPTION			"adsv"

typedef struct					s_opt
{
	char						a;
	int							d;
	int							s;
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
}								t_champion;

typedef	struct					s_proc
{
	char						reg[REG_NUMBER][REG_SIZE];
	int							pc;
	unsigned char				carry;
	unsigned char				life;
	lint						last_live;
	unsigned int				player_num;
	unsigned int				proc_num;
	unsigned int				cycle_to_wait;
	unsigned char				inst;
}								t_proc;

typedef	struct					s_vm
{
	t_opt						opt;
	unsigned char				mem[MEM_SIZE];
	unsigned char				proc_mem[MEM_SIZE];
	unsigned int				list_len;
	t_list						*plst;
	t_champion					c[MAX_PLAYERS];
	lint						ctd;
	unsigned int				procs_death_nb; // UPDATE FOR GRAPHICS: to see how many procs are dead
	unsigned int				last_live;
	unsigned int				live_num;
	int							next_live_check;
	unsigned int				last_ctd_dec;
	unsigned char				max_arg_size[17][MAX_ARGS_NUMBER + 1];
	lint						total_cycle;
}								t_vm;

/*
 *     afficher couleur du joueur
 *     pourcentage de processus par joueur
 *     afficher total_cycle
 *     aff next_live_check (barre chargement)
 *     accelerer/ralentir (exec_vm.c l70)
 */

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
	void						(*f)(t_vm *, t_proc *, t_arg[MAX_ARGS_NUMBER]);
}								t_op;

t_list							*ft_lstnew(void const *content, size_t content_size);

void							ft_lstadd(t_list **alst, t_list *new);

int								ft_strisuint(char *arg);
int								ft_strisint(char *arg);

int								ft_memisset(void *p, size_t n, char c);

int								get_players(char **argv, int argc, t_champion *tab);

void							vm_init(t_vm *vm, int argc, char **argv);

void							ft_error_exit(const char *exit_message);
void							get_proc_cycle(t_proc *proc, unsigned char *mem);

void							print_memory(unsigned char *mem, unsigned int size);
void							print_champions(t_champion *tab);
void							print_bits(unsigned int x);
void							print_args(t_arg args[MAX_ARGS_NUMBER],
								unsigned int arg_number, unsigned char long_inst,
								unsigned					 char dest);
void							print_procs(t_vm *vm, t_list *lst, unsigned char print_reg);


void							null_instr(t_vm *vm, t_proc *, t_arg args[MAX_ARGS_NUMBER]);

void							moove_pc(t_vm *vm, t_proc *proc, unsigned int value);
void							my_live(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_ld(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_st(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_add(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_sub(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_and(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_or(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_xor(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_zjmp(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_ldi(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_sti(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_fork(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_lld(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_lldi(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_lfork(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);
void							my_aff(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER]);

void							write_var(t_vm *vm, t_proc *proc, unsigned char *var, lint beg);

void							checks_and_destroy(t_vm *vm);

int								get_args(t_vm *vm, t_proc *proc, t_arg args[MAX_ARGS_NUMBER], t_op *inst);
lint							get_arg_data(unsigned char mem[MEM_SIZE], int beg, unsigned int len);

void							print_vm(t_vm *vm);

void							exec_vm(t_vm *vm);

#endif
