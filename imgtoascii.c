#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "intmatrix.h"

FILE *file;

int main()
{
	// let's assume we are only dealing with square images / matrices
	long long matrix_length = 50; // overkill but VS yells at me
	Point *pmat = (Point *)malloc(matrix_length * matrix_length * sizeof(Point));

	if (pmat == NULL)
	{
		printf("something went wrong with malloc\n");
		return 1;
	}

	for (int i = 0; i < matrix_length * matrix_length; i++)
	{
		pmat[i] = newPoint(' ', -1, -1, -1);
	}

	errno_t err;

	err = fopen_s(&file, "threat.txt", "r");
	if (err == 0)
	{
		// file opened
		int i = 0;
		int j = 0;
		int uh = 0;
		do
		{
			char c = fgetc(file);
			if (c == '\n')
			{
				uh = 0;
				continue;
			}
			if (feof(file))
			{
				break;
			}
			Point p = newPoint(c, j, uh, matrix_length / 2);
			pmat[i] = p;
			i++;
			uh++;
			if (i % matrix_length == 0)
			{
				j++;
			}
		} while (1);
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				printf("%c", pmat[i * matrix_length + j].c);
			}
			printf("\n");
		}
	}
	else
	{
		// file couldn't be opened
	}

	if (file)
	{
		err = fclose(file);
		if (err == 0)
		{
			printf("file closed\n");
		}
		else
		{
			printf("file closedn't\n");
		}
	}
	free(pmat);

	IntMatrix matrix;
	int arr[6] = {1, 2, 3, 4, 5, 6};
	initIntMatrix(&matrix, 2, 3, arr, 6);
	print(&matrix);

	int val = 0;
	val = get(&matrix, 0, 1);
	printf("matrix (%d, %d): %d\n", 0, 1, val);

	const int arr1[3] = {1, 2, 3};
	const int arr2[3] = {4, 5, 6};

	int dp = dot_prod(arr1, arr2, 3);
	printf("dot prod: %d", dp);

	return 0;
}

void mahmut(IntMatrix *mat1, IntMatrix *mat2, IntMatrix *res)
{
	// mat1 rows, mat2 cols
	int *v1, *v2;
	v1 = (int *)malloc(sizeof(v1) * mat1->cols);
	v2 = (int *)malloc(sizeof(v2) * mat2->rows);

	for (int i = 0; i < mat1->cols; ++i)
	{
		for (int j = 0; j < mat2->rows; ++i)
		{
			v1[i] = mat1->values[i * mat1->cols + j];
			v2[j] = mat2->values[j * mat2->rows + i];
		}
		// i'll come back to this
	}
}

int dot_prod(int *vec1, int *vec2, int len)
{
	int sum = 0;
	for (int i = 0; i < len; ++i)
	{
		sum += vec1[i] * vec2[i];
	}
	return sum;
}