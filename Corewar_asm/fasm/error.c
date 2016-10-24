#include "asm.h"

void	exit_with_message(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}