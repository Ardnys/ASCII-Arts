#pragma once

typedef struct {
	int rows;
	int cols;
	int* values;
} IntMatrix;

void initIntMatrix(IntMatrix* matrix);
int get(IntMatrix* matrix, int i, int j);
int* getRow(IntMatrix* matrix, int i);
int* getCol(IntMatrix* matrix, int j);
void freeValues(IntMatrix* matrix);
void print(IntMatrix* matrix);