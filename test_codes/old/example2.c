#include<stdio.h>

int main() {

    int a, b, sum, i,j;

    b = 3;

    sum = 0;

    i = 0;

    for(i=0; i<40; i++) {
        a = b+5;
        for(j=0; j<40; j++) {
            if(j%2 == 0)
                sum = sum + a;
        }
    }

    printf("Value of sum = %d\n", sum);


    return sum;

}
