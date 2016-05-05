#include <stdio.h>

int add(int a, int b) {
	return a + b;
}

int main() {
	int a = 4, b = 3;
	int sum1, sum2;
	sum1 = add(a, b);
	sum2 = add(b, 7);
	printf("sum1 = %d, sum2 = %d\n", sum1, sum2);
	return 0;	
}
