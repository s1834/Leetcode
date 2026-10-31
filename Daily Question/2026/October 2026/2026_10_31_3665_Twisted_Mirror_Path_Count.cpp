class Solution {
    private:
        const int MOD = 1e9 + 7;
        int m, n;
    
        vector<vector<vector<int>>> dp;
    
        int findPath(vector<vector<int>>& grid, int i, int j, int right) {
            if(i >= m || j >= n) return 0;
    
            if(i == m - 1 && j == n - 1) return 1;
    
            if(dp[i][j][right] != -1) return dp[i][j][right];
    
            if(grid[i][j] == 1) {
                if(right) return dp[i][j][right] = findPath(grid, i + 1, j, false) % MOD;
                else return dp[i][j][right] = findPath(grid, i, j + 1, true) % MOD;
            } else return dp[i][j][right] = ((findPath(grid, i, j + 1, true) % MOD) + (findPath(grid, i + 1, j, false) % MOD)) % MOD;
        }
    
    public:
        int uniquePaths(vector<vector<int>>& grid) {
            m = grid.size();
            n = grid[0].size();
    
            dp.assign(m, vector<vector<int>>(n, vector<int>(2, -1))); // m rows, n cols, 2 directions
            return findPath(grid, 0, 0, 1);
        }
    };

/*
Problem: Unique Paths with Obstacles and Directional Movement

Approach: Recursion + Memoization (3D Dynamic Programming)

Intuition:
----------
We need to count the number of valid paths from the top-left cell
(0, 0) to the bottom-right cell (m - 1, n - 1).

Movement is allowed in two directions:
- Right
- Down

However, some cells contain 1, which acts as a directional constraint:
- If we enter a cell containing 1 while moving right, we must move down.
- If we enter a cell containing 1 while moving down, we must move right.

For cells containing 0, we can move in either direction.

The key observation is that the number of possible paths from a
cell depends not only on its coordinates but also on the direction
from which we arrived.

Therefore, we use a 3D DP state:

dp[i][j][right]

where:
- i = Current row.
- j = Current column.
- right = 1 means the previous movement was right.
- right = 0 means the previous movement was down.

We use memoization to avoid recalculating the same state.

--------------------------------------------------
1. Class Variables
--------------------------------------------------

const int MOD = 1e9 + 7;

The number of possible paths can become very large.

Therefore, all results are calculated modulo 10^9 + 7.

int m, n;

Store the dimensions of the grid:
- m = Number of rows.
- n = Number of columns.

vector<vector<vector<int>>> dp;

The 3D DP array stores the number of valid paths from each
(i, j, right) state.

Each state is initially -1, indicating that it has not been
calculated yet.

--------------------------------------------------
2. Recursive Function: findPath()
--------------------------------------------------

int findPath(vector<vector<int>>& grid, int i, int j, int right)

This function returns the number of valid paths from the current
cell (i, j) to the destination, considering the previous
movement direction.

The right parameter represents:
- 1: We arrived at the current cell by moving right.
- 0: We arrived at the current cell by moving down.

--------------------------------------------------
3. Base Case: Out of Bounds
--------------------------------------------------

if(i >= m || j >= n) return 0;

If the current position moves outside the grid, it is not a
valid path.

Therefore, return 0.

Since movement is restricted to right and down, checking the
lower and right boundaries is sufficient.

--------------------------------------------------
4. Base Case: Destination Reached
--------------------------------------------------

if(i == m - 1 && j == n - 1) return 1;

If we reach the bottom-right cell, we have found one valid path.

Return 1.

This check is performed before the memoization lookup because
the destination always contributes exactly one completed path.

--------------------------------------------------
5. Memoization Check
--------------------------------------------------

if(dp[i][j][right] != -1)
    return dp[i][j][right];

If the current state has already been calculated, return its
stored result.

This avoids exploring the same cell and direction combination
multiple times.

Notice that we maintain separate states for right = 0 and
right = 1 because the next allowed movement may depend on
the direction from which we entered the current cell.

--------------------------------------------------
6. Case 1: Current Cell Contains 1
--------------------------------------------------

if(grid[i][j] == 1) {

A cell containing 1 forces us to change the movement direction.

The next movement must be perpendicular to the direction used
to enter the current cell.

Case A: Previous Movement Was Right
-----------------------------------

if(right)
    return dp[i][j][right] =
        findPath(grid, i + 1, j, false) % MOD;

If right == 1, we entered the current cell by moving right.

Therefore, we must move down.

Next coordinates:
(i + 1, j)

The next movement direction is down, so we pass false.

The result is stored in dp[i][j][right] after taking modulo.

Case B: Previous Movement Was Down
-----------------------------------

else
    return dp[i][j][right] =
        findPath(grid, i, j + 1, true) % MOD;

If right == 0, we entered the current cell by moving down.

Therefore, we must move right.

Next coordinates:
(i, j + 1)

The next movement direction is right, so we pass true.

Again, store the result in the corresponding DP state.

--------------------------------------------------
7. Case 2: Current Cell Contains 0
--------------------------------------------------

else return dp[i][j][right] =
    ((findPath(grid, i, j + 1, true) % MOD) +
     (findPath(grid, i + 1, j, false) % MOD)) % MOD;

If the current cell contains 0, there is no directional restriction.

We can choose either of the two possible movements.

Option 1: Move Right
-------------------

findPath(grid, i, j + 1, true)

Move to the next column and mark the previous movement as right.

Option 2: Move Down
------------------

findPath(grid, i + 1, j, false)

Move to the next row and mark the previous movement as down.

Add Both Possibilities
----------------------

The total number of paths is:

Paths = Right Paths + Down Paths

Take modulo after adding the two results to prevent integer
overflow and satisfy the problem's modulo requirement.

Store the result in dp[i][j][right] for future reuse.

--------------------------------------------------
8. Initialize DP and Start Recursion
--------------------------------------------------

int uniquePaths(vector<vector<int>>& grid)

First, calculate the grid dimensions:

m = grid.size();
n = grid[0].size();

Initialize the DP array:

dp.assign(
    m,
    vector<vector<int>>(n, vector<int>(2, -1))
);

This creates a 3D DP structure:

m rows
n columns
2 possible previous movement directions

Every state is initialized to -1.

Finally:

return findPath(grid, 0, 0, 1);

Start recursion from the top-left cell.

The initial direction is set to 1, representing that the previous
movement was right.

This is the initial direction assumption used by the implementation.

--------------------------------------------------
9. Example Walkthrough
--------------------------------------------------

Consider:

grid = [
    [0, 0, 0],
    [0, 1, 0],
    [0, 0, 0]
]

Start at (0, 0) with right = 1.

Since grid[0][0] == 0, both movements are possible:

1. Move right to (0, 1), with right = 1.
2. Move down to (1, 0), with right = 0.

Consider reaching cell (1, 1), where grid[1][1] == 1.

If we enter from the left:
- Previous movement was right.
- We are forced to move down to (2, 1).

If we enter from above:
- Previous movement was down.
- We are forced to move right to (1, 2).

Thus, the direction state determines which transition is allowed
at a cell containing 1.

The recursion explores all valid possibilities and memoizes
the number of paths for each state.

--------------------------------------------------
10. Why the Algorithm Works
--------------------------------------------------

1. Every recursive call represents a valid position and the
   direction used to enter that position.

2. For a cell containing 1, the algorithm allows only the
   perpendicular movement.

3. For a cell containing 0, both right and down movements
   are explored.

4. Out-of-bound movements contribute zero paths.

5. Reaching the destination contributes exactly one path.

6. Memoization ensures that every (i, j, right) state is
   calculated only once.

Therefore, the algorithm counts all valid paths without
recomputing previously solved states.

--------------------------------------------------
11. Complexity Analysis
--------------------------------------------------

Let m be the number of rows and n be the number of columns.

Number of DP States:
--------------------

There are:
- m possible row positions.
- n possible column positions.
- 2 possible direction states.

Total states = 2 * m * n

Time Complexity: O(m * n)

Each state is calculated at most once, and each state performs
at most two recursive calls.

Space Complexity: O(m * n)

The DP array stores 2 states for every cell.

The recursion stack can also grow up to O(m + n), since every
recursive path moves only right or down.

Core Idea:
----------
Use 3D memoization because the number of valid paths depends on
both the current cell and the direction used to enter it.
At cells containing 1, force a perpendicular turn; at cells
containing 0, allow both right and down movements.
*/