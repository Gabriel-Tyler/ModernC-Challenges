/* using arrays, write functions that do...: 
 *  - dot product
 *  - vector-to-vector or matrix-vector products 
 *  - gaussian elimination 
 *  - iterative matrix inversion */

#include <stdio.h>
#include <stddef.h>

void dotProduct(size_t n, double const a[n], double const b[n], double res[n]) {
    while (n--) 
        *res++ = (*a++) * (*b++);
}

void matrixMultiply(size_t m, size_t n, size_t p, 
                    double const a[m][n], double const b[n][p], double res[m][p]) {
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < p; ++j) {
            res[i][j] = 0.0;
            for (size_t k = 0; k < n; ++k) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void printArr(size_t n, double a[n]) {
    while (n--)
        printf("%f ", *a);
    printf("\n");
}

void printMatrix(size_t m, size_t n, double a[m][n]) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%f ", a[i][j]);
        printf("\n");
    }
}

int main(void) {
    size_t const m = 2;
    size_t const n = 2;
    size_t const p = 2;

    double const a[m][n] = {{2, 0},{0, 2}};
    double const b[n][p] = {{1, 2},{3, 4}};
    double res[m][p];

    matrixMultiply(m, n, p, a, b, res);
    printMatrix(m, p, res);
}
