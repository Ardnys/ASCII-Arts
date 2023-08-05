#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

void initMatrix(Matrix* matrix, int r, int c, double* vals, int size) {
	matrix->rows = r;
	matrix->cols = c;
	size_t s = (long long)r * (long long)c;
	matrix->values = (double*)calloc(s, sizeof(double));

	if (matrix->values == NULL) {
		printf("oof malloc didn't work\n");
	}
	else {
		for (size_t i = 0; i < size; i++) {
			matrix->values[i] = vals[i];
		}
	}
}

int get(Matrix* matrix, int i, int j) {
	if (i < 0 || j < 0) {
		fprintf(stderr, "can't access negative array index!\n");
		return -1;
	}
	else if (i >= matrix->rows || j >= matrix->cols) {
		fprintf(stderr, "can't access out of bounds array index!\n");
		return -1;
	}
	else {
		return matrix->values[i * matrix->rows + j];
	}

}

void freeValues(Matrix* matrix) {
	free(matrix->values);
}

void print(Matrix* matrix) {
	if (matrix->values == NULL) {
		printf("matrix uninitialized\n");
		return;
	}
	else {
		for (int i = 0; i < matrix->rows; i++)
		{
			for (int j = 0; j < matrix->cols; j++) {
				printf("%.4lf ", matrix->values[i * matrix->cols + j]);
			}
			printf("\n");
			
		}
	}
	printf("\n");
}