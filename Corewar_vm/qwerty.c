#include <stdio.h>

int main()
{
    int i; 
        for(i=(sizeof(int)*8)-1; i>=0; i--)
        {
        	printf("(1u<<%d) == %u\n",i, (1u<<i));
            // (x&(1u<<i))?putchar('1'):putchar('0');
        }
}