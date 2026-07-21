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