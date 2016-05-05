#include <stdio.h>

int diff( int a, int b) {
	return a - b;
}

int randomStuff( int a, int b, int c, int d) {
	int temp1, temp2;
	temp1 = diff(10, a);
	temp2 = diff(b, c);
	return temp1*temp2*d;
}

int main( ) {
	int a = 11, b = 13, c = 17, d = 19;
	int rand1, rand2, rand3;
	rand1 = randomStuff(1, 3, c, d);
	rand2 = randomStuff(5, 6 , 7,  a);
	rand3 = randomStuff(a, b, c, d);
	printf("rand1 = %d, rand2 = %d, rand3 = %d\n", rand1, rand2, rand3);
	return 0; 
}
