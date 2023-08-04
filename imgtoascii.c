#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "intmatrix.h"

FILE* file;

void mahmut(IntMatrix* mat1, IntMatrix* mat2, IntMatrix* res);
void prontVec(int* vec, int len, const char* naem);
int dot_prod(int* vec1, int* vec2, int len);

int main() {
	// let's assume we are only dealing with square images / matrices
	long long matrix_length = 50; // overkill but VS yells at me
	Point* pmat = (Point*)malloc(matrix_length * matrix_length * sizeof(Point));

	if (pmat == NULL) {
		printf("something went wrong with malloc\n");
		return 1;
	}

	for (int i = 0; i < matrix_length * matrix_length; i++)
	{
		pmat[i] = newPoint(' ', -1, -1, -1);
	}


	errno_t err;

	err = fopen_s(&file, "threat.txt", "r");
	if (err == 0) {
		// file opened
		int i = 0;
		int j = 0;
		int uh = 0;
		do {
			char c = fgetc(file);
			if (c == '\n') {
				uh = 0;
				continue;
			}
			if (feof(file)) {
				break;
			}
			Point p = newPoint(c, j, uh, matrix_length / 2);
			pmat[i] = p;
			i++;
			uh++;
			if (i % matrix_length == 0) {
				j++;
			}
		} while (1);
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				printf("%c", pmat[i * matrix_length + j].c);
			}
			printf("\n");
		}

	}
	else {
		// file couldn't be opened
	}

	if (file) {
		err = fclose(file);
		if (err == 0) {
			printf("file closed\n");
		}
		else {
			printf("file closedn't\n");
		}
	}
	free(pmat);
	int bar[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
	int baz[9] = { 3, 5, 7, 2, 1, 4, 6, 2, 4 };
	int arr[6] = { 1, 2, 3, 4, 5, 6 };
	int foo[6] = { 3, 5, 7, 2, 1, 4 };
	int one[2] = { 2, 4 };
	int two[2] = { 3, 5 };

	IntMatrix mat1, mat2, result;
	
	initIntMatrix(&mat1, 1, 2, one, 2);
	print(&mat1);
	
	initIntMatrix(&mat2, 2, 1, two, 2);
	print(&mat2);

	mahmut(&mat1, &mat2, &result);
	print(&result);


	/*int val = 0;
	val = get(&mat1, 0, 1);
	printf("mat1 (%d, %d): %d\n", 0, 1, val);*/

	/*const int arr1[3] = { 1, 2, 3 };
	const int arr2[3] = { 4, 5, 6 };

	int dp = dot_prod(arr1, arr2, 3);
	printf("dot prod: %d", dp);*/

	

	return 0;
}

void mahmut(IntMatrix* mat1, IntMatrix* mat2, IntMatrix* res) {
	// mat1 rows, mat2 cols
	int* v1, *v2, *resVal;
	v1 = (int*)malloc(sizeof(v1) * mat1->cols);
	v2 = (int*)malloc(sizeof(v2) * mat2->rows);
	resVal = (int*)malloc(sizeof(res) * mat1->rows * mat2->cols);

	if (v1 == NULL || v2 == NULL || resVal == NULL) {
		fprintf(stderr, "either v1 or v2 or result couldn't be allocated\n");
		return;
	}
	
	int sum = 0;
	int ctr = 0;

	printf("mat1row: %d\n", mat1->rows);

	for (int i = 0; i < mat1->rows; i++) {
		for (int j = 0; j < mat1->cols; j++) {
			int v1val = mat1->values[i * mat1->cols + j];
			printf("idx: %d\n", i * mat1->cols + j);
			v1[j] = v1val;
		} 
		printf("------ v1 now ------\n");
		prontVec(v1, mat1->cols, "v1");
		for (int k = 0; k < mat2->cols; k++) {
			for (int l = 0; l < mat2->rows; l++) {
				int v2val = mat2->values[l * mat2->cols + k];
				v2[l] = v2val;
				//printf("v1[%d] -> %d\nv2[%d] -> %d\n", l, mat1->values[k * mat1->cols + l], l, v2val);
			}
			printf("--- v1 x v2 ---\n");
			prontVec(v1, mat1->cols, "v1");
			prontVec(v2, mat2->rows, "v2");
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

void prontVec(int* vec, int len, const char* naem) {
	for (int i = 0; i < len; i++) {
		printf("%s[%d]: %d\n", naem, i, vec[i]);
	}
	printf("\n");
}