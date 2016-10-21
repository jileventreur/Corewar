#include <stdio.h>


// void print_bits(unsigned int nb, int i)
// {
// 	if (!i)
// 		return ;
// 	print_bits(nb >> 1, i - 1);
// 	printf("%c%c", nb % 2 ? '1' : '0', i == sizeof(int) * 8 ? '\n' : 0);
// }

int main()
{
	unsigned int tmp = 0x01020304;
	unsigned char *p;


	p = ((unsigned char *)&tmp);
	printf("int tmp = %x\n", tmp);
	for (int i = 0; i < 4; ++i)
	{
		unsigned char res;

		res = p[i];
		printf("p[%d] = %0.2x\n", i, res);
	}
}
	// printf("%c", tmp % 2 ? '1' : '0');
	// print_bits(tmp, sizeof(int) * 8);
	// print_bits(2, sizeof(int) * 8);
	// print_bits(tmp + 2, sizeof(int) * 8);