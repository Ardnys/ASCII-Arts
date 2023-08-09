#pragma once
#include "Matrix.h"

typedef struct {
    int idx_x;
    int idx_y;
    Matrix coords;
    Matrix r_coords;
    char c;
} Point;

Point newPoint(char c, int i, int j, int mid);
void set_r_coords(Point* p, Matrix* r_coords);
void rotate(Point* p, double angle);
void calculate_index(Point* p, int mid);
void prontPoint(Point* p);