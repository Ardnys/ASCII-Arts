#pragma once
#include "intmatrix.h";

void mat_multiply(IntMatrix* mat1, IntMatrix* mat2, IntMatrix* res);
int dot_prod(int* vec1, int* vec2, int len);
void prontVec(int* vec, int len, const char* name);
