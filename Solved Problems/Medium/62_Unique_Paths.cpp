class Solution {
    private:
        int dp[101][101];
    
        int solve(int& m, int& n, int i, int j) {
            if(i == m && j == n) return 1;
            if(i > m || j > n) return 0;
    
            if(dp[i][j] != -1) return dp[i][j];
    
            return dp[i][j] = solve(m, n, i + 1, j) + solve(m, n, i, j + 1);
        }
    
    public:
        int uniquePaths(int m, int n) {
            memset(dp, -1, sizeof(dp));
            return solve(m, n, 1, 1);
        }
    };

/*
    ============================================================
    LeetCode 62 - Unique Paths
    ============================================================

    Approach: Recursion + Memoization (Top-Down DP)
    ------------------------------------------------------------

    We start at cell (1, 1) and want to reach cell (m, n).

    From any cell, we can move only:
        1. Down  -> (i + 1, j)
        2. Right -> (i, j + 1)

    The number of unique paths from a cell is the sum of the
    paths available by moving down and moving right.


    ============================================================
    1. Base Cases
    ============================================================

    if(i == m && j == n) return 1;

        We have reached the destination, so there is exactly
        one valid path: the path we just completed.

    if(i > m || j > n) return 0;

        We have moved outside the grid, so this route contributes
        zero valid paths.


    ============================================================
    2. Memoization
    ============================================================

    dp[i][j] stores the number of unique paths from cell (i, j)
    to the destination (m, n).

    Initially, every entry is -1, meaning that the state has
    not been calculated yet.

    If dp[i][j] != -1, return the stored answer instead of
    recalculating the same recursive calls.

    Otherwise:

        dp[i][j] = solve(m, n, i + 1, j)
                 + solve(m, n, i, j + 1);

    We add both possibilities because every valid path must
    begin by moving either down or right.


    ============================================================
    3. Initialization
    ============================================================

    memset(dp, -1, sizeof(dp));

        Marks every DP state as uncomputed.

    solve(m, n, 1, 1);

        Starts the recursion from the top-left cell.


    ============================================================
    Complexity
    ============================================================

    Time:  O(m * n)
           Each grid cell is computed at most once.

    Space: O(m * n)
           For the DP table, plus O(m + n) recursion stack
           in the worst case.


    ============================================================
    Core Idea
    ============================================================

    paths(i, j) = paths(i + 1, j) + paths(i, j + 1)

    Destination -> 1 path
    Outside grid -> 0 paths

    Memoization avoids repeatedly solving the same subproblems.
    ============================================================
*/