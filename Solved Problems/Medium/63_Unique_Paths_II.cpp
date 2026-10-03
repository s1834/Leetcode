class Solution {
    private:
        int n, m;
        int dp[101][101];
    
        int solve(vector<vector<int>>& obstacleGrid, int i, int j) {
            if(i == n - 1 && j == m - 1) return 1;
            if(i >= n || j >= m) return 0;
    
            if(obstacleGrid[i][j] == 1) return 0;
    
            if(dp[i][j] != -1) return dp[i][j];
    
            return dp[i][j] = solve(obstacleGrid, i + 1, j) + solve(obstacleGrid, i, j + 1);
        }
    
    public:
        int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
            n = obstacleGrid.size();
            m = obstacleGrid[0].size();
            memset(dp, -1, sizeof(dp));
    
            if(obstacleGrid[0][0] || obstacleGrid[n - 1][m - 1]) return 0;
    
            return solve(obstacleGrid, 0, 0);
        }
    };

/*
    ============================================================
    LeetCode 63 - Unique Paths II
    ============================================================

    Approach: Recursion + Memoization (Top-Down DP)
    ------------------------------------------------------------

    Similar to Unique Paths I, but now some cells contain
    obstacles (1), which cannot be visited.

    From each cell, we can move:
        1. Down  -> (i + 1, j)
        2. Right -> (i, j + 1)

    dp[i][j] stores the number of valid paths from (i, j)
    to the bottom-right destination.


    ============================================================
    1. Base Cases
    ============================================================

    if(i == n - 1 && j == m - 1) return 1;

        Reached the destination, so one valid path is found.

    if(i >= n || j >= m) return 0;

        Moved outside the grid, so this route is invalid.

    if(obstacleGrid[i][j] == 1) return 0;

        The current cell contains an obstacle, so no path can
        pass through it.


    ============================================================
    2. Memoization and Recurrence
    ============================================================

    if(dp[i][j] != -1) return dp[i][j];

        If this cell was already computed, reuse its answer.

    Otherwise, calculate:

        dp[i][j] = solve(i + 1, j) + solve(i, j + 1);

    The total paths equal the paths going down plus the paths
    going right. Invalid routes and obstacles contribute zero.

    Each cell's result is stored to avoid repeated computation.


    ============================================================
    3. Initial Checks
    ============================================================

    Initialize all DP entries to -1, indicating uncomputed
    states.

    If either the starting cell or destination contains an
    obstacle, return 0 immediately.

    Otherwise, begin recursion from (0, 0).


    ============================================================
    Complexity
    ============================================================

    Time:  O(n * m) - each cell is computed at most once.

    Space: O(n * m) - DP table, plus O(n + m) recursion stack.


    ============================================================
    Core Idea
    ============================================================

    paths(i, j) = paths(i + 1, j) + paths(i, j + 1)

    Destination -> 1 path
    Outside grid or obstacle -> 0 paths

    Memoization ensures each valid state is computed once.
    ============================================================
*/