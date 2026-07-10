#include <bits/stdc++.h>
using namespace std;

class IslandFinder {
private:
    int rows, cols;
    vector<vector<int>>& grid;
    vector<vector<bool>> visited;

    // 4-directional moves (use 8-dir array below if diagonals count)
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};

    bool isValid(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols
               && !visited[x][y] && grid[x][y] == 1;
    }

    // BFS is preferred over recursive DFS for large grids (avoids stack overflow)
    int bfs(int startX, int startY) {
        queue<pair<int,int>> q;
        q.push({startX, startY});
        visited[startX][startY] = true;
        int size = 0;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            size++;

            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (isValid(nx, ny)) {
                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        return size;
    }

public:
    IslandFinder(vector<vector<int>>& g) : grid(g) {
        rows = grid.size();
        cols = rows > 0 ? grid[0].size() : 0;
        visited.assign(rows, vector<bool>(cols, false));
    }

    // Returns {largestIslandSize, smallestIslandSize, totalIslandCount}
    tuple<int, int, int> findIslandExtremes() {
        int largest = 0;
        int smallest = INT_MAX;
        int count = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    int size = bfs(i, j);
                    largest = max(largest, size);
                    smallest = min(smallest, size);
                    count++;
                }
            }
        }

        if (count == 0) smallest = 0; // no islands at all

        return {largest, smallest, count};
    }
};

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0}
    };

    IslandFinder finder(grid);
    auto [largest, smallest, count] = finder.findIslandExtremes();

    cout << "Number of islands: " << count << "\n";
    cout << "Largest island size: " << largest << "\n";
    cout << "Smallest island size: " << smallest << "\n";

    return 0;
}