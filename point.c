//
// Created by Emre on 10/7/2023.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "mafs.h"
#include "point.h"
#include "matrix.h"

Point newPoint(char c, int i, int j, int mid) {
    Point p;
    Matrix coords;
    Matrix r_coords;
    double co[3] = { j - mid, i - mid, 0 };
    initMatrix(&coords, 3, 1, co, 3);
    // initMatrix(&r_coords, 1, 3, co, 3);
    p.coords = coords;
    // p.r_coords = r_coords;
    p.c = c;
    p.idx_x = i;
    p.idx_y = j;
    return p;
}

void set_r_coords(Point* p, Matrix* r_coords) {
    p->r_coords = *r_coords;
}

void rotate(Point* p, double angle) {
    double cos_theta = cos(angle);
    double sin_theta = sin(angle);

    // i'd rather not call all these every time i rotate it

    Matrix rx_matrix, ry_matrix, rz_matrix, res;

    double rx[9] = { 1, 0, 0, 0, cos_theta, -sin_theta, 0, sin_theta, cos_theta };
    double ry[9] = { cos_theta, 0, sin_theta, 0, 1, 0, -sin_theta, 0, cos_theta };
    double rz[9] = { cos_theta, -sin_theta, 0, sin_theta, cos_theta, 0, 0, 0, 1 };

    initMatrix(&rx_matrix, 3, 3, rx, 9);
    initMatrix(&ry_matrix, 3, 3, ry, 9);
    initMatrix(&rz_matrix, 3, 3, rz, 9);

    mat_multiply(&ry_matrix, &p->coords, &p->r_coords);
}

void calculate_index(Point* p, int mid) {
    int x = (int)p->r_coords.values[0] + mid;
    int y = (int)p->r_coords.values[1] + mid;
    if (x >= 0 && x < mid * 2 && y >= 0 && y < mid * 2) {
        p->idx_x = y;
        p->idx_y = x;
    }
}

void printPoint(Point* p) {
    printf("%5s %5c %10s\n", "idx", ' ', "coords");
    printf("--------------------------------------\n");
    printf("[%d, %d] %3c (%.2lf, %.2lf)\n", p->idx_x, p->idx_y, ' ',
           p->coords.values[0],   p->coords.values[1]);
}