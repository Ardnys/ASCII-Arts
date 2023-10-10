//
// Created by Emre on 10/7/2023.
//

#ifndef SPINNING_IMAGE_CLI_MAFS_H
#define SPINNING_IMAGE_CLI_MAFS_H

#include "matrix.h"

void mat_multiply(Matrix* mat1, Matrix* mat2, Matrix* res);
double dot_prod(const double* vec1, const double* vec2, int len);
void prontVec(double* vec, int len, const char* name);
double* linspace(double start, double stop, size_t size);

#endif //SPINNING_IMAGE_CLI_MAFS_H
