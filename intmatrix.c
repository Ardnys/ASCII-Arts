#include <stdlib.h>
#include <stdio.h>

#include "intmatrix.h"

void initIntMatrix(IntMatrix* matrix, int r, int c, int* vals) {
	matrix->rows = r;
	matrix->cols = c;
	size_t s = (long long)r * (long long)c;
	matrix->values = (int*)calloc(s, sizeof(int));

	if (matrix->values == NULL) {
		printf("oof malloc didn't work\n");
	}
	else {
		size_t val_len = sizeof(vals) / 4;
		for (size_t i = 0; i < val_len; i++) {
			matrix->values[i] = vals[i];
		}
	}
}

int get(IntMatrix* matrix, int i, int j) {


}
int* getRow(IntMatrix* matrix, int i) {

}

int* getCol(IntMatrix* matrix, int j) {

}

void freeValues(IntMatrix* matrix) {

}

void print(IntMatrix* matrix) {
	if (matrix->values == NULL) {
		printf("matrix uninitialized\n");
		return;
	}
	else {
		for (int i = 0; i < matrix->rows * matrix->cols; i++)
		{
			printf("%d ", matrix->values[i]);
		}
	}
}