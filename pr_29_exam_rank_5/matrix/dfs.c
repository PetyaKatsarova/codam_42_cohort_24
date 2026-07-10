#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000

int rows, cols;
int grid[MAX_ROWS][MAX_COLS];
int visited[MAX_ROWS][MAX_COLS];

// 4-directional moves (change to 8 if diagonals should count)
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int isValid(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols
           && !visited[x][y] && grid[x][y] == 1;
}

// BFS using a manual queue (array-based, since C has no std::queue)
int bfs(int startX, int startY) {
    // Queue stores flattened coordinates: index = x * cols + y
    int *queue = malloc(rows * cols * sizeof(int));
    int front = 0, back = 0;
    int size = 0;

    queue[back++] = startX * cols + startY;
    visited[startX][startY] = 1;

    while (front < back) {
        int curr = queue[front++];
        int x = curr / cols;
        int y = curr % cols;
        size++;

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (isValid(nx, ny)) {
                visited[nx][ny] = 1;
                queue[back++] = nx * cols + ny;
            }
        }
    }

    free(queue);
    return size;
}

// Fills largest, smallest, and count via pointers (C has no tuples)
void findIslandExtremes(int *largest, int *smallest, int *count) {
    *largest = 0;
    *smallest = INT_MAX_CUSTOM;
    *count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                int size = bfs(i, j);
                if (size > *largest) *largest = size;
                if (size < *smallest) *smallest = size;
                (*count)++;
            }
        }
    }

    if (*count == 0) *smallest = 0; // no islands at all
}

int main() {
    rows = 5;
    cols = 5;

    int input[5][5] = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0}
    };

    memcpy(grid, input, sizeof(input));
    memset(visited, 0, sizeof(visited));

    int largest, smallest, count;
    findIslandExtremes(&largest, &smallest, &count);

    printf("Number of islands: %d\n", count);
    printf("Largest island size: %d\n", largest);
    printf("Smallest island size: %d\n", smallest);

    return 0;
}