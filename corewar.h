/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/
#ifndef COREWAR_H
#define COREWAR_H

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BSWAP_32(num) (((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000))

#define DIR_SIZE				2
#define REG_SIZE				4
#define IND_SIZE				4


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8) // 512
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6) 

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

/*
**
*/

typedef char	t_arg_type;

typedef long long int	lint;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

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

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

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
	unsigned int				pc;
	unsigned char				carry;
	unsigned char				life;
	unsigned int				cycle_to_wait;
}								t_proc;

typedef	struct					s_vm
{
	unsigned char				mem[MEM_SIZE];
	t_list						*plst;
	t_champion					c[MAX_PLAYERS];
	unsigned int				ctd;
	unsigned int				live_num;
	unsigned int				next_live_check;
	unsigned int				last_ctd_dec;
	unsigned char				max_arg_size[17][MAX_ARGS_NUMBER + 1];
}								t_vm;

typedef struct					s_op
{
	char						*name;
	unsigned int				param_number;
	unsigned char				param_mask[MAX_ARGS_NUMBER];
	unsigned char				opcode;
	unsigned int				cycle;
	char						*desc;
	unsigned char				activ_carry;
	unsigned char				direct_adr;
	void						(*f)(t_vm *, t_proc *, unsigned char [MAX_ARGS_NUMBER]);
}								t_op;

t_list		*ft_lstnew(void const *content, size_t content_size);

void		ft_lstadd(t_list **alst, t_list *new);

int			ft_strisuint(char *arg);

int			ft_memisset(void *p, size_t n, char c);

void		get_players(char **argv, int argc, t_champion *tab);

void		vm_init(t_vm *vm, int argc, char **argv);

void		ft_error_exit(const char *exit_message);
void		get_proc_cycle(t_proc *proc, unsigned char *mem);

void		print_memory(unsigned char *mem, unsigned int size);
void		print_champions(t_champion *tab);
void		print_procs(t_list *lst);

void		null_instr(t_vm *vm, t_proc *, unsigned char args_type[MAX_ARGS_NUMBER]);
void		sti(t_vm *vm, t_proc *proc, unsigned char args_type[MAX_ARGS_NUMBER]);

void		checks_and_destroy(t_vm *vm);

#endif