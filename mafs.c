#include <stdio.h>

#include "mafs.h"

void mat_multiply(IntMatrix* mat1, IntMatrix* mat2, IntMatrix* res) {
	// mat1 rows, mat2 cols
	int* v1, * v2, * resVal;
	v1 = (int*)malloc(sizeof(v1) * mat1->cols);
	v2 = (int*)malloc(sizeof(v2) * mat2->rows);
	resVal = (int*)malloc(sizeof(res) * mat1->rows * mat2->cols);

	if (v1 == NULL || v2 == NULL || resVal == NULL) {
		fprintf(stderr, "either v1 or v2 or result couldn't be allocated\n");
		return;
	}

	int sum = 0;
	int ctr = 0;

	// printf("mat1row: %d\n", mat1->rows);

	for (int i = 0; i < mat1->rows; i++) {
		for (int j = 0; j < mat1->cols; j++) {
			int v1val = mat1->values[i * mat1->cols + j];
			// printf("idx: %d\n", i * mat1->cols + j);
			v1[j] = v1val;
		}
		// printf("------ v1 now ------\n");
		prontVec(v1, mat1->cols, "v1");
		for (int k = 0; k < mat2->cols; k++) {
			for (int l = 0; l < mat2->rows; l++) {
				int v2val = mat2->values[l * mat2->cols + k];
				v2[l] = v2val;
				//printf("v1[%d] -> %d\nv2[%d] -> %d\n", l, mat1->values[k * mat1->cols + l], l, v2val);
			}
			// printf("--- v1 x v2 ---\n");
			// prontVec(v1, mat1->cols, "v1");
			// prontVec(v2, mat2->rows, "v2");
			// printf("\n");
			sum = dot_prod(v1, v2, mat1->cols);
			resVal[ctr++] = sum;
		}
	}
	initIntMatrix(res, mat1->rows, mat2->cols, resVal, mat1->rows * mat2->cols);
}

int dot_prod(int* vec1, int* vec2, int len) {
	int sum = 0;
	for (int i = 0; i < len; ++i) {
		sum += vec1[i] * vec2[i];
	}
	return sum;
}

void prontVec(int* vec, int len, const char* name) {
	for (int i = 0; i < len; i++) {
		printf("%s[%d]: %d\n", name, i, vec[i]);
	}
	printf("\n");
}