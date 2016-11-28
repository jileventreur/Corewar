#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS			4
#define MEM_SIZE			(4*1024)
#define IDX_MOD				(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
typedef struct		header_s
{
	unsigned int		magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					header_t;

void	ft_create_code_corrupt(unsigned char *corrupt, unsigned char *code, unsigned int size)
{
	int i = 0;
	int base = 16;
	

	*corrupt = 0;
	while (i < size)
	{
		if (*code >= '9')
		{
			printf("j'ajoute %d\n", (*code - 'a' + 9));
			*corrupt += (*code - 'a' + 9) * base;
		}
		else
		{
			printf("j'ajoute %d\n", (*code - '0'));
			*corrupt += (*code - '0') * base;
		}
		base = base == 16 ? 1 : 16;
		++code;
		++i;
		if (!(i % 2) && i < size)
		{
			++corrupt;
			*corrupt = 0;
		}
	}
}

int main(int argc, char **argv)
{
	header_t header;
	int fd;

	if (argc != 4)
	{
		printf ("usage batard :	fichier.cor (le champion a corrompre si t\'as pas capter)l'address a corompre (donc un nombrele code a inserer)\n");
		return (0);
	}
	fd = open(*(argv + 1), O_RDONLY);
	if (fd == -1)
	{
		printf("tu te fous de ma gueule ??\n");
		return (0);
	}
	bzero(&header, sizeof(header_t));
	if ((read(fd, &header, sizeof(header_t)) == -1))
	{
		printf("J'arrive pas a lire le fichier batard\n");
		return (0);
	}
	header.magic =  ((header.magic << 24 & 0xFF000000) | (header.magic << 8 & 0xFF0000)          
			| (header.magic >> 8 & 0xFF00) | (header.magic >> 24 & 0xFF));
	int lalalala;
	lalalala =  ((header.prog_size << 24 & 0xFF000000) | (header.prog_size << 8 & 0xFF0000)          
			| (header.prog_size >> 8 & 0xFF00) | (header.prog_size >> 24 & 0xFF));
	if (header.magic != COREWAR_EXEC_MAGIC)
		printf("heu.., pas le bon magic number fdp\n");
	int size;

	header.magic =  ((header.magic << 24 & 0xFF000000) | (header.magic << 8 & 0xFF0000)          
			| (header.magic >> 8 & 0xFF00) | (header.magic >> 24 & 0xFF));
	size = atoi(*(argv + 2));
	if (size + strlen(*(argv + 3)) > lalalala)
	{

		printf("t'as envie que je segfault???\n");
		return (0);
	}	


	if (strlen(*(argv + 3)) % 2)
	{
		printf("code impair");
		return (0);
	}
	char buf[CHAMP_MAX_SIZE] = {0};
	char name[13] = {0};
	if (strlen(*(argv + 1)) > 1024)
		return 0;
	strcpy(name, "_corrupt.cor");
	
	if ((read(fd, buf, CHAMP_MAX_SIZE)) == -1)
	{
		printf("J'arrive pas a lire le fichier batard\n");
		return (0);
	}

	close (fd);
	printf("%s\n", name);
	fd = 0;
	fd = open(name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		printf("va te faire mettre par une chevre ??\n");
		return (0);
	}
	strcpy(header.prog_name, "Champion corrompu");
	strcpy(header.comment, "WAAAAAAAAAAAAAGGGGGGGGGGGGGGHHHHHHHHHHHHHHHHHHH");
	char code_corrompu[CHAMP_MAX_SIZE] = {0};

	memcpy(code_corrompu, buf, lalalala );
//	memcpy(code_corrompu + size, *(argv + 3), strlen(*(argv + 3)));
	ft_create_code_corrupt((unsigned char *)(code_corrompu + size), (unsigned char *)*(argv + 3), strlen(*(argv + 3)));
	write(fd, &header, sizeof(header_t));
	write(fd, code_corrompu, lalalala);
	
	close (fd);
	return (0);
}
