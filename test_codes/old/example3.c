#include<stdio.h>

int main() {

    int a, b, sum, i,j;

    a = 1;
    b = 3;

    sum = 0;

    i = 0;

    for(i=0; i<40; i++) {
        for(j=0; j<40; j++) {
            sum = sum + a;
            a = sum - 10;
        }
    }

    printf("Value of sum = %d\n", sum);


    return sum;

}
