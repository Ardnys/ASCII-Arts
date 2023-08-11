#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "point.h"
#include "matrix.h"
#include "mafs.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))

double PI = 3.14159265;
long long len = 50;

FILE* file;

void printImage(Point* points);
void rotateThemPoints(Point* points);

int getImg() {
	// let's assume we are only dealing with square images / matrices
	long long len = 50; // overkill but VS yells at me
	Point* pmat = (Point*)malloc(len * len * sizeof(Point));

	if (pmat == NULL) {
		printf("something went wrong with malloc\n");
		return 1;
	}

	for (int i = 0; i < len * len; i++)
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
			Point p = newPoint(c, j, uh, len / 2);
			pmat[i] = p;
			i++;
			uh++;
			if (i % len == 0) {
				j++;
			}
		} while (1);
		printImage(pmat);
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
	int rotations = 72;
	double* angles = linspace(0, 2 * PI, rotations);
	for (int i = 0; i < rotations; i++) {
		// printf("%lf\n", angles[i]);
		clear();
		rotateThemPoints(pmat, angles[i]);
		Sleep(1/24);
	}
	free(angles);

	// double angle = PI / 4;
	// clear();
	// rotateThemPoints(pmat, angle);
	// printImage(pmat);
	 

	/*Point p = pmat[78];
	prontPoint(&p);
	
	rotate(&p, angle);
	prontPoint(&p);*/

	free(pmat);
}

/*
void uh(Point* points) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {

		}
	}
}

*/

void rotateThemPoints(Point* points, double angle) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			rotate(&points[i * len + j], angle);
			calculate_index(&points[i * len + j], len / 2);
			gotoxy(points[i * len + j].idx_x, points[i * len + j].idx_y);
			printf("%c", points[i * len + j].c);
		}
	}
}


void printImage(Point* points) {
	clear();
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			char c = points[i * len + j].c;
			printf("%c%c%c", c, c, c);
		}
		printf("\n");
	}
}

int main() {
	/*
	const char* idx_str = "idx";
	const char* coord_str = "coords";
	int i = 12;
	int j = 20;
	double x = 3.12;
	double y = 6.76;

	printf("%5s %5c %4s %4c\n", idx_str, ' ', coord_str, ' ');
	printf("---------------------\n");
	printf("[%d, %d] (%.2lf, %.2lf)\n", i, j, x, y);

	*/
	getImg();





	/*

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
	*/



	return 0;
}