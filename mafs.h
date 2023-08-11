#pragma once
#include "matrix.h";

void mat_multiply(Matrix* mat1, Matrix* mat2, Matrix* res);
double dot_prod(double* vec1, double* vec2, int len);
void prontVec(double* vec, int len, const char* name);
double* linspace(double start, double stop, double size);
