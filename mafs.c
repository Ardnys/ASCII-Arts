#include <stdio.h>
#include <stdlib.h>

#include "mafs.h"

void mat_multiply(Matrix* mat1, Matrix* mat2, Matrix* res) {
	// mat1 rows, mat2 cols
	double *v1, *v2, *resVal;

	v1 = (double*)malloc(sizeof(v1) * mat1->cols);
	v2 = (double*)malloc(sizeof(v2) * mat2->rows);
	resVal = (double*)malloc(sizeof(res) * mat1->rows * mat2->cols);

	print(mat1);
	print(mat2);

	if (v1 == NULL || v2 == NULL || resVal == NULL) {
		fprintf(stderr, "either v1 or v2 or result couldn't be allocated\n");
		return;
	}

	double sum = 0;
	int ctr = 0;

	//printf("mat1col: %d\n", mat1->cols);

	for (int i = 0; i < mat1->rows; i++) {
		for (int j = 0; j < mat1->cols; j++) {
			double v1val = mat1->values[i * mat1->cols + j];
			// printf("idx: %d\n", i * mat1->cols + j);
			v1[j] = v1val;
		}
		printf("------ v1 now ------\n");
		prontVec(v1, mat1->cols, "v1");
		for (int k = 0; k < mat2->cols; k++) {
			for (int l = 0; l < mat2->rows; l++) {
				double v2val = mat2->values[l * mat2->cols + k];
				v2[l] = v2val;
				// printf("v1[%d] -> %d\nv2[%d] -> %d\n", l, mat1->values[k * mat1->cols + l], l, v2val);
			}
			printf("--- v1 x v2 ---\n");
			prontVec(v1, mat1->cols, "v1");
			prontVec(v2, mat2->rows, "v2");
			printf("\n");
			sum = dot_prod(v1, v2, mat1->cols);
			printf("sum: %lf\n", sum);
			resVal[ctr++] = sum;
		}
	}
	initMatrix(res, mat1->rows, mat2->cols, resVal, mat1->rows * mat2->cols);
	print(res);
}

double dot_prod(double* vec1, double *vec2, int len) {
	double sum = 0;
	for (int i = 0; i < len; ++i) {
		sum += vec1[i] * vec2[i];
	}
	return sum;
}

void prontVec(double* vec, int len, const char* name) {
	for (int i = 0; i < len; i++) {
		printf("%s[%d]: %.4lf\n", name, i, vec[i]);
	}
	printf("\n");
}