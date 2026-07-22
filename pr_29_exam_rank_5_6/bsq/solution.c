#include <stdio.h>

#define ROWS 6
#define COLS 7

int min3(int a, int b, int c)
{
    int min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;
    return min;
}

int main(void)
{
    char map[ROWS][COLS + 1] = {
        ".......",
        "..o....",
        ".......",
        "....o..",
        ".......",
        "......."
    };

    int dp[ROWS][COLS];
    int max = 0;
    int max_row = 0;
    int max_col = 0;

    // Build DP table
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (map[i][j] == 'o')
                dp[i][j] = 0;
            else if (i == 0 || j == 0)
                dp[i][j] = 1;
            else
                dp[i][j] = 1 + min3(
                    dp[i - 1][j],
                    dp[i][j - 1],
                    dp[i - 1][j - 1]);

            if (dp[i][j] > max)
            {
                max = dp[i][j];
                max_row = i;
                max_col = j;
            }
        }
    }

    // Fill largest square
    int start_row = max_row - max + 1;
    int start_col = max_col - max + 1;

    for (int i = start_row; i <= max_row; i++)
        for (int j = start_col; j <= max_col; j++)
            map[i][j] = 'x';

    // Print result
    printf("Largest square size: %d\n\n", max);

    for (int i = 0; i < ROWS; i++)
        printf("%s\n", map[i]);

    return 0;
}













/*Logic
Read header.
Read map.
Validate map.
Create dp array (same size as map).
Compute largest square.
Fill largest square.
Print map.
-------------------------
DP (Dynamic Programming)
-------------------------
In BSQ:
dp is usually a 2D integer array with the same dimensions as the map.
Each dp[i][j] stores the size of the largest square ending at cell (i, j) (where (i, j) is the bottom-right corner).
map:
. . .
. . .
. . .
DP:
1 1 1
1 2 2
1 2 3
The 3 means:

A 3×3 empty square ends at the bottom-right cell.

Why DP?

Without it: repeatedly check many squares → slow.
With DP: each cell is computed once using only 3 neighbors:
top
left
top-left

So the entire algorithm runs in O(rows × cols) time.
-------------------------------------
*/
//int max = 0;
//int max_row = 0;
//int max_col = 0;

//for (int i = 0; i < rows; i++)
//{
//    for (int j = 0; j < cols; j++)
//    {
//        if (map[i][j] == obstacle)
//            dp[i][j] = 0;

//        else if (i == 0 || j == 0)
//            dp[i][j] = 1;

//        else
//            dp[i][j] = 1 + min3(
//                dp[i - 1][j],     // top
//                dp[i][j - 1],     // left
//                dp[i - 1][j - 1]  // top-left
//            );

//        if (dp[i][j] > max)
//        {
//            max = dp[i][j];
//            max_row = i;
//            max_col = j;
//        }
//    }
//}

//int start_row = max_row - max + 1;
//int start_col = max_col - max + 1;

//for (int i = start_row; i <= max_row; i++)
//{
//    for (int j = start_col; j <= max_col; j++)
//        map[i][j] = full;
//}

//int min3(int a, int b, int c)
//{
//    int min = a;

//    if (b < min)
//        min = b;
//    if (c < min)
//        min = c;
//    return (min);
//}

//if (obstacle)
//    dp = 0;
//else if (first row || first column)
//    dp = 1;
//else
//    dp = 1 + min(top, left, top_left);