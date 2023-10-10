//
// Created by Emre on 10/7/2023.
//

#ifndef SPINNING_IMAGE_CLI_MATRIX_H
#define SPINNING_IMAGE_CLI_MATRIX_H

typedef struct {
    int rows;
    int cols;
    double* values;
} Matrix;

void initMatrix(Matrix* matrix, int r, int c, const double* values, int size);
double get(Matrix* matrix, int i, int j);
void freeMatrix(Matrix* matrix);
void print(Matrix* matrix);

#endif //SPINNING_IMAGE_CLI_MATRIX_H
