#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "point.h"
#include "matrix.h"
#include "mafs.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))

double PI = 3.14159265;
size_t LEN = 50;

FILE *file;

void printImage(Point *points);
//void rotateThemPoints(Point* buffer1, Point* buffer2, double angle, int buffer_flag);
//void thething(Point* points, Point* prevts);

int getImg(Point *points, Point *prevts) {
    // let's assume we are only dealing with square images / matrices

    if (points == NULL || prevts == NULL) {
        fprintf(stderr, "something went wrong with malloc\n");
        return 1;
    }

    for (int i = 0; i < LEN * LEN; i++) {
        points[i] = newPoint(' ', -1, -1, -1);
    }

    errno_t err;

    err = fopen_s(&file, "C:\\Dev\\C\\spinning_image_cli\\threat.txt", "r");
    if (err == 0) {
        // file opened
        int i = 0;
        int j = 0;
        int uh = 0;
        do {
            char c = (char) fgetc(file);
            if (c == '\n') {
                uh = 0;
                continue;
            }
            if (feof(file)) {
                break;
            }
            Point p = newPoint(c, j, uh, (int) LEN / 2);
            Point q = newPoint(c, j, uh, (int) LEN / 2);
            prevts[i] = q;
            points[i] = p;
            i++;
            uh++;
            if (i % LEN == 0) {
                j++;
            }
        } while (1);
//        printImage(points);
    } else {
        fprintf(stderr, "file couldn't be opened\n");
    }

    if (file) {
        err = fclose(file);
        if (err == 0) {
            printf("file closed\n");
        } else {
            printf("file closedn't\n");
        }
    }
}

void printImage(Point *points) {
    for (size_t i = 0; i < LEN; ++i) {
        for (size_t j = 0; j < LEN; ++j) {
            char c = points[i * LEN + j].c;
            printf("%c", c);
        }
        printf("\n");
    }
}

void pront(Point* points) {
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            gotoxy(points[i * LEN + j].idx_x, points[i * LEN + j].idx_y);
            printf("%c", points[i * LEN + j].c);
        }
    }
}

void updateFrame(Point* points, Point* prevts) {
    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            size_t idx = i * LEN + j;

            gotoxy(points[idx].idx_x, points[idx].idx_y);
            printf("%c", points[idx].c);
        }
    }
//    clear();
}

void rotateFrame(Point* points, double angle, Point* prevts) {
    size_t idx = 0;
    for (int i = 0; i < LEN; ++i) {
        for (int j = 0; j < LEN; ++j) {
            idx = (size_t) i * LEN + j;
            rotate(&points[idx], angle);
            calculate_index(&points[idx], (int)LEN / 2);
        }
    }
    updateFrame(points, prevts);
    prevts = points;
}

void playAnimation(Point* points, Point* prevts) {
    int rotations = 48;
    double* angles = linspace(0, 2 * PI, rotations);

    clear();
    pront(points);

    // TODO add previous frame and check the empty spots

    for (int i = 0; i < rotations; ++i) {
        rotateFrame(points, angles[i], prevts);
    }
}

void freeMemory(Point* point) {
    for (size_t i = 0; i < LEN; ++i) {
        for (size_t j = 0; j < LEN; ++j) {
            freeMatrix(&point[i * LEN + j].coords);
            freeMatrix(&point[i * LEN + j].r_coords);
        }
    }
}


int main() {
    Point *points = (Point *) malloc(LEN * LEN * sizeof(Point));
    Point *prevts = (Point *) malloc(LEN * LEN * sizeof(Point));

    getImg(points, prevts);
    playAnimation(points, prevts);

    freeMemory(points);
    freeMemory(prevts);
    free(points);
    free(prevts);
}