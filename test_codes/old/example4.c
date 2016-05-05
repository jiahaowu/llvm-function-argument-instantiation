#include<stdio.h>

int main() {

    int a, b, c, d, e, f, sum, i,j,k;

    b = 3;

    sum = 0;

    f = 0;

    a = b+5;
    
    c = a+4;

    for(i=0; i<40; i++) {
        d = c+3;
        for(j=0; j<40; j++) {
            if(j%2 == 0) {
                f = f + d;
            }
            e = a+d;
            for (k=0; k < 10; k++) {
                sum = f + e;  
            }
        }
    }

    printf("Value of sum = %d\n", sum);

    return sum;

}
