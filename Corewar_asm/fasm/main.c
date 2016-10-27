#include "asm.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;

	if (argc != 2)
		exit_with_message("Only one argument.");
	fd = open(argv[1], O_RDWR);
	if (fd <= 0)
		exit_with_message("Problème fd");
	checking_file(argv[1], fd);
	close(fd);
	return (0);
}