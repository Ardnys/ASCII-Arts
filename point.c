#include <math.h>

#include "point.h"

Point newPoint(char c, int i, int j, int mid) {
	Point p;
	Matrix coords;
	double co[3] = { j - mid, i - mid, 0 };
	initMatrix(&coords, 1, 3, co, 3);
	p.coords = coords;
	p.c = c;
	p.idx_x = i;
	p.idx_y = j;
	return p;
}

void set_r_coords(Point* p, Matrix* r_coords) {
	p->r_coords = *r_coords;
}

void rotate(Point* p, double angle) {
	
}