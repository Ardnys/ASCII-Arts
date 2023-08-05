#pragma once

typedef struct {
	int rows;
	int cols;
	int* values;
} IntMatrix;

void initIntMatrix(IntMatrix* matrix, int r, int c, int* vals, int size);
int get(IntMatrix* matrix, int i, int j);
void freeValues(IntMatrix* matrix);
void print(IntMatrix* matrix);

// i don't need these functions now but i might implement them just for fun later
// int* getRow(IntMatrix* matrix, int* row, int i);
// int* getCol(IntMatrix* matrix, int* col, int j);