#include <stdio.h>

int main() {
    char mat[50][50];

    FILE* fileptr = fopen("threat.txt", "r");

    if (fileptr == NULL) {
        printf("File couldn't be opened.\n");
        return 0;
    } else {
        int i = 0;
        int j = 0;

        do {
            char c = fgetc(fileptr);
            if (c == '\n') {
                i++;
                j = 0;
                continue;
            }
            mat[i][j] = c;

            j++;
            if (feof(fileptr)) {
                break;
            }
        } while (1);
    }

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            printf("%c", mat[i][j]);
        }
        printf("\n");  
    }
    
    return 0;
}