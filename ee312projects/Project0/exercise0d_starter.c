#include <stdio.h>

void printMultTableInt(int n);
void printMultTableFrac(int n);

int main(void){

    // You can change this to test your code
    int size = 4;

    printMultTableInt(size);
    printf("\n\n");
    printMultTableFrac(size);

    return 0;

}

// Prints multiplication table of integers from 1 to n
void printMultTableInt(int n){

    for (int i=1; i<=n; i++){
        printf("\n");
        for (int j=1; j<=n; j++){
            printf("%d ",i*j);
        }
    }

}

// Prints multiplication table for fractions from 1, 1/2, 1/3 to 1/n
void printMultTableFrac(int n){
    for (int i=1; i<=n; i++){
        printf("\n");
        for (int j=1; j<=n; j++){
            double product = i*j;
            double frac = (double)(1/product);
            printf("%.2f ", frac);
        }
    }

}
