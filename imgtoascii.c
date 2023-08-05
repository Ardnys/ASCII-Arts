#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "matrix.h"
#include "mafs.h"

FILE* file;

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
		fprintf(stderr, "file couldn't be opened\n");
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

	
	double bar[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
	double baz[9] = { 3, 5, 7, 2, 1, 4, 6, 2, 4 };
	double arr[6] = { 1, 2, 3, 4, 5, 6 };
	double foo[6] = { 3, 5, 7, 2, 1, 4 };
	double one[2] = { 2, 4 };
	double two[2] = { 3, 5 };

	Matrix mat1, mat2, result;
	
	initMatrix(&mat1, 2, 3, arr, 6);
	print(&mat1);
	
	initMatrix(&mat2, 3, 2, foo, 6);
	print(&mat2);

	mat_multiply(&mat1, &mat2, &result);
	print(&result);
	

	return 0;
}

