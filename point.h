#pragma once

typedef struct {
    int idx_x;
    int idx_y;
    int coords[3];
    int r_coords[3];
    char c;
} Point;

Point newPoint(char c, int i, int j, int mid);