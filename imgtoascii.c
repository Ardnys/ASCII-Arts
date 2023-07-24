#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int idx_x;
    int idx_y;
    int coords[3];
    int r_coords[3];
    char c;
} Point;

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

FILE* file; 

int main() {
    // let's assume we are only dealing with square images / matrices
    long long matrix_length = 50; // overkill but VS yells at me
    Point* pmat = (Point*)malloc(matrix_length * matrix_length * sizeof(Point));

    if (pmat == NULL) {
        printf("something went wrong with malloc\n");
        return 1;
    }

    for (int i = 0; i < matrix_length * matrix_length; i++)
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
            Point p = newPoint(c, j, uh, matrix_length/2);
            pmat[i] = p;
            i++;
            uh++;
            if (i % matrix_length == 0) {
                j++;
            }
        } while (1);
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                printf("Point: (%d, %d)\n", pmat[i * matrix_length + j].coords[0], pmat[i * matrix_length + j].coords[1]);
            }
            printf("\n");
        }

    } else {
        // file couldn't be opened
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
    free(pmat);

    return 0;
}