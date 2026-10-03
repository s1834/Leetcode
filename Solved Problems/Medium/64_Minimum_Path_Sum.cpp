class Solution {
    private:
        int n, m;
        int dp[201][201];
    
        int solve(vector<vector<int>>& grid, int i, int j) {
            if(i >= n || j >= m) return INT_MAX;
    
            if(i == n - 1 && j == m - 1) return grid[i][j];
    
            if(dp[i][j] != -1) return dp[i][j];
    
            int down = solve(grid, i + 1, j);
            int right = solve(grid, i, j + 1);
    
            return dp[i][j] = grid[i][j] + min(down, right);
        }
    
    
    public:
        int minPathSum(vector<vector<int>>& grid) {
            n = grid.size();
            m = grid[0].size();
            memset(dp, -1, sizeof(dp));
            
            return solve(grid, 0, 0);;
        }
    };

/*
    ============================================================
    LeetCode 64 - Minimum Path Sum
    ============================================================

    Approach: Recursion + Memoization (Top-Down DP)
    ------------------------------------------------------------

    Start at (0, 0) and reach the bottom-right cell (n-1, m-1).

    From each cell, we can move only:
        1. Down  -> (i + 1, j)
        2. Right -> (i, j + 1)

    The goal is to find the path whose sum of cell values
    is minimum.


    ============================================================
    1. Base Cases
    ============================================================

    if(i >= n || j >= m) return INT_MAX;

        If we move outside the grid, that path is invalid.
        INT_MAX ensures an invalid path is not chosen when
        comparing the two directions.

    if(i == n - 1 && j == m - 1) return grid[i][j];

        Once we reach the destination, return its cell value.


    ============================================================
    2. Recurrence Relation
    ============================================================

    Calculate the minimum cost of reaching the destination
    through both possible directions:

        down  = solve(i + 1, j)
        right = solve(i, j + 1)

    Choose the direction with the smaller remaining path sum,
    then add the value of the current cell:

        dp[i][j] = grid[i][j] + min(down, right);

    This gives the minimum path sum starting from (i, j).


    ============================================================
    3. Memoization
    ============================================================

    dp[i][j] stores the minimum path sum from cell (i, j)
    to the destination.

    Initially, all entries are -1, meaning uncomputed.

    If dp[i][j] != -1, return the stored answer instead of
    solving the same subproblem again.

    Finally, start the recursion from (0, 0).


    ============================================================
    Complexity
    ============================================================

    Time:  O(n * m) - each cell is computed at most once.

    Space: O(n * m) - DP table, plus O(n + m) recursion stack.


    ============================================================
    Core Idea
    ============================================================

    minPath(i, j) = grid[i][j] + min(
        minPath(i + 1, j),
        minPath(i, j + 1)
    )

    Outside grid -> INT_MAX
    Destination  -> grid[n-1][m-1]

    Memoization avoids recomputing the minimum path sum
    for cells visited through multiple recursive paths.
    ============================================================
*/