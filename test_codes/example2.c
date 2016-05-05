#include <stdio.h>

int sub(int x, int y) {
	return x - y;
}

int main( ) {
	int a = 5; int b = 10;
	int diff1, diff2, diff3;
	diff1 = sub(a,b);
	diff2 = sub(100, b);
	diff3 = sub(24, 25);
	printf("diff1 = %d, diff2 = %d, diff3 = %d\n", diff1, diff2, diff3);
	return 0;
}
