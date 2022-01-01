// matrix-multiplication <Project2.cpp>
// EE 312 Project 2 submission by
// Anvit Raju
// ar68234
// Slip days used: 0 (Used 0 for this project, Used 1 in total on Project 1)
// Fall 2021

#include <stdio.h>
#include <stdint.h>
#include <cstdlib>
#include "MatrixMultiply.h"

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]) {

    for (int i=0; i<a_rows; i++){
        for (int j=0; j<b_cols; j++){
            c[i*b_cols + j] = 0;
            for (int k=0; k<a_cols; k++){
                c[i*b_cols + j] += (a[(i * a_cols + k)] * b[(k * b_cols) + j]);
            }
        }
    }
}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {

    double** c = (double**)malloc(a_rows*sizeof(double*));

    for (int i=0; i< a_rows; i++){
        double *p = (double*)malloc(b_cols*sizeof(double));
        c[i] = p;
    }

    for (int i=0; i<a_rows; i++){
        for (int j=0; j<b_cols; j++){
            c[i][j] = 0;
            for (int k=0; k<a_cols; k++){
                c[i][j] += (a[i][k] * b[k][j]);
            }
        }
    }
    return c;
}

// https://en.wikipedia.org/wiki/Transpose
double** transposeMatrix(
        //Flip matrix over its diagonal

        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols) {

    // allocate space for c matrix which will contain transposed matrix
    double **c = (double**)malloc(a_cols*sizeof(double));

    for (int i=0; i<a_cols; i++){
        double* p = (double*)malloc(a_rows*sizeof(double));
        c[i] = p;
    }

    for (int i=0; i<a_rows; i++){
        for (int j=0; j<a_cols; j++){
            c[j][i] = a[i][j]; //Switch row and column indexes
        }
    }
    return c;
}