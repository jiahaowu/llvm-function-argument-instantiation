#include <stdio.h>

int multiply(int x, int y, int z) {
	return x*y*z;
}

int sub(int x, int y) {
	return x - y;
}

int main( ) {
	int a = 10, b = 20, c = 30;
	int diff1, diff2, diff3;
	int prod1, prod2, prod3, prod4;
	prod1 = multiply(a, b, c);
	prod2 = multiply(100, b, c);
	diff1 = sub(prod1, prod2);
	diff2  = sub(100, diff1);
	prod3 = multiply(15, diff2, 25);
	prod4 = multiply(2, 3, 4);
	printf("prod1 = %d, prod2 = %d, prod3 = %d, prod4 = %d\n", prod1, prod2, prod3, prod4); 
}
