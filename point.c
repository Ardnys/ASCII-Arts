#include "point.h"

Point newPoint(char c, int i, int j, int mid) {
    Point p;
    p.c = c;
    p.idx_x = i;
    p.idx_y = j;
    p.coords[0] = j - mid;
    p.coords[1] = i - mid;
    p.coords[2] = 0;
    return p;
}