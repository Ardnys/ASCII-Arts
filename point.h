#pragma once
#include "intmatrix.h"

typedef struct {
    int idx_x;
    int idx_y;
    IntMatrix coords;
    IntMatrix r_coords;
    char c;
} Point;

Point newPoint(char c, int i, int j, int mid);
void set_r_coords(Point* p, IntMatrix* r_coords);