#include<stdio.h>

int main() {

    int a, b, sum, i;

    b = 3;

    a = b + 3;

    sum = 0;

    i = 0;

    for(i=0; i<40; i++) {
        sum = sum + a;
    }

    printf("Value of sum = %d\n", sum);


    return sum;

}
