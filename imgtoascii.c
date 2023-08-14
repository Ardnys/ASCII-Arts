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
void rotateThemPoints(Point* buffer1, Point* buffer2, double angle, int buffer_flag);
void thething(Point* points, Point* prevts);

int getImg() {
	// let's assume we are only dealing with square images / matrices
	long long len = 50; // overkill but VS yells at me
	Point* points = (Point*)malloc(len * len * sizeof(Point));
	Point* prevts = (Point*)malloc(len * len * sizeof(Point));

	if (points == NULL || prevts == NULL) {
		fprintf(stderr, "something went wrong with malloc\n");
		return 1;
	}

	for (int i = 0; i < len * len; i++)
	{
		points[i] = newPoint(' ', -1, -1, -1);
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
			Point q = newPoint(c, j, uh, len / 2);
			prevts[i] = q;
			points[i] = p;
			i++;
			uh++;
			if (i % len == 0) {
				j++;
			}
		} while (1);
		// printImage(points);
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

	thething(points, prevts);

	free(points);
	free(prevts);
}

void pront(Point* points) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			gotoxy(points[i * len + j].idx_x, points[i * len + j].idx_y);
			printf("%c", points[i * len + j].c);
		}
	}
}

void prent(Point* buffer1, Point* buffer2, int flag) {
	int x1, y1, x2, y2;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (flag == 0) {
				// write to buffer1
				x1 = buffer1[i * len + j].idx_x;
				y1 = buffer1[i * len + j].idx_y;
				x2 = buffer2[i * len + j].idx_x;
				y2 = buffer2[i * len + j].idx_y;

				if (buffer2[x2 * len + y2].c != buffer1[x1 * len + y2].c) {
					gotoxy(x1, y1);
					printf("%c", 'o');
				}

			}
			else {
				// write to buffer2
				x1 = buffer1[i * len + j].idx_x;
				y1 = buffer1[i * len + j].idx_y;
				x2 = buffer2[i * len + j].idx_x;
				y2 = buffer2[i * len + j].idx_y;

				printf("c1: %c\nc2: %c\n", buffer1[x1 * len + y1].c, buffer2[x2 * len + y2].c);
				

				if (buffer2[x2 * len + y2].c != buffer1[x1 * len + y1].c) {
					gotoxy(x2, y2);
					printf("%c", buffer2[i * len + j].c);
				}
			}
		}
	}
}

void thething(Point* points, Point* prevts) {
	int rotations = 72;
	int flag = 1;
	double* angles = linspace(0, 2 * PI, rotations);
	clear();
	pront(points);
	rotateThemPoints(points, prevts, PI / 4, 1);
	prent(points, prevts, 1);
	
	

	// printImage(points);

	//for (int i = 0; i < rotations; i++) {
	//	// printf("%lf\n", angles[i]);
	//	rotateThemPoints(points, prevts, angles[i], --flag);
	//	flag += 2;
	//	Sleep(1 / 24);
	//}

	free(angles);

	
}


void rotateThemPoints(Point* buffer1, Point* buffer2, double angle, int buffer_flag) {
	int idx = 0;
	if (buffer_flag == 0) {
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				idx = i * len + j;
				rotate(&buffer1[idx], angle);
				calculate_index(&buffer1[idx], len / 2);
			}
		}

	}
	else {
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < len; j++) {
				idx = i * len + j;
				rotate(&buffer2[idx], angle);
				calculate_index(&buffer2[idx], len / 2);
			}
		}
	}
}


void printImage(Point* points) {
	// clear();
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			char c = points[i * len + j].c;
			printf("%c", c);
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