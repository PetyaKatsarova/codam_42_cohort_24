#include <stdio.h>
#include <stdlib.h>

/*
arr is a double pointer used to store the addresses of multiple rows.
Double Pointer (**pp) → Pointer (*p) → Data (x)
*/
int main() {
     int rows = 3, cols = 4;
    int **arr;

    // Allocating memory for rows pointers
    arr = (int **)malloc(rows * sizeof(int *));

    // Allocating memory for each row
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *)malloc(cols * sizeof(int));
    }

    // Assigning values and printing the 2D array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = i + j;
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}