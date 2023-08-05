#pragma once

typedef struct {
	int rows;
	int cols;
	double* values;
} Matrix;

void initMatrix(Matrix* matrix, int r, int c, double* vals, int size);
int get(Matrix* matrix, int i, int j);
void freeValues(Matrix* matrix);
void print(Matrix* matrix);

// i don't need these functions now but i might implement them just for fun later
// int* getRow(Matrix* matrix, int* row, int i);
// int* getCol(Matrix* matrix, int* col, int j);