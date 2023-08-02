#include <stdlib.h>
#include <stdio.h>

#include "intmatrix.h"

void initIntMatrix(IntMatrix *matrix, int r, int c, int *vals, int size)
{
	matrix->rows = r;
	matrix->cols = c;
	size_t s = (long long)r * (long long)c;
	matrix->values = (int *)calloc(s, sizeof(int));

	if (matrix->values == NULL)
	{
		printf("oof malloc didn't work\n");
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			matrix->values[i] = vals[i];
		}
	}
}

int get(IntMatrix *matrix, int i, int j)
{
	if (i < 0 || j < 0)
	{
		fprintf(stderr, "can't access negative array index!\n");
		return -1;
	}
	else if (i >= matrix->rows || j >= matrix->cols)
	{
		fprintf(stderr, "can't access out of bounds array index!\n");
		return -1;
	}
	else
	{
		return matrix->values[i * matrix->rows + j];
	}
}
int *getRow(IntMatrix *matrix, int *row, int i)
{
}

int *getCol(IntMatrix *matrix, int *col, int j)
{
}

void freeValues(IntMatrix *matrix)
{
	free(matrix->values);
}

void print(IntMatrix *matrix)
{
	if (matrix->values == NULL)
	{
		printf("matrix uninitialized\n");
		return;
	}
	else
	{
		for (int i = 0; i < matrix->rows * matrix->cols; i++)
		{
			printf("%d ", matrix->values[i]);
		}
	}
}