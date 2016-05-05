#include <stdio.h>

int main()
{
	int i, j, k;
	int a, b, c, d;

	a = 3;
	for(i = 0; i < 10; i++)
	{
		b = a + 5;
		for(j = 0; j < 10; j++)
		{
			c = b + 7;
			for(k = 0; k < 10; k++)
			{
				d = c + 11;
			}
		}

	}
	printf("Value of d = %d\n", d);
}
