#include <stdio.h>
#include <stdlib.h>

int num1, num2, i;
int result = 1;

int gdc(int x, int y){
    for (i=y; i>0; i--){
        if ((x%i==0)&&(y%i==0)) {
            result=i;
            return result;
        }
    }
}

int main()
{
    num1=48;
    num2=18;
    gdc(num1, num2);
	printf("GCD of %d and %d is: %d", num1, num2, result);
}