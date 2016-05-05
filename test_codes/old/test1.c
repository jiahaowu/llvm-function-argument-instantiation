#include <stdio.h>

int main()
{
int i, j, k; 
int a, b, c, d, e, f;

a = 3;

for(i = 0; i < 10; i++)
{
	if( i > 4)
		a = 6;
	b = a + 5;
	for(j = 0; j < 20; j++)
	{
		c = b + 7;
		for(k = 0; k < 30; k++)
		{
			if(k > 16)
				c = b + b;
			d = c + 11;
		}
	}
}
	printf("value of d = %d\n", d);
}
