#pragma once

typedef struct
{
	int rows;
	int cols;
	int *values;
} IntMatrix;

void initIntMatrix(IntMatrix *matrix, int r, int c, int *vals, int size);
int get(IntMatrix *matrix, int i, int j);
int *getRow(IntMatrix *matrix, int *row, int i);
int *getCol(IntMatrix *matrix, int *col, int j);
void freeValues(IntMatrix *matrix);
void print(IntMatrix *matrix);