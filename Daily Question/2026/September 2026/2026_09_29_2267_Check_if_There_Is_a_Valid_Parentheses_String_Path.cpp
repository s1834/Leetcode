class Solution {
    private:
        int n, m;
        int dp[100][100][200];
    
        bool solve(vector<vector<char>>& grid, int i, int j, int openCount) {
            if(i == n || j == m) return false;
    
            openCount += (grid[i][j] == '(') ? 1 : -1;
            
            if(openCount < 0) return false;
            
            if(dp[i][j][openCount] != -1) return dp[i][j][openCount];
            
            if(i == n - 1 && j == m - 1) return dp[i][j][openCount] = (openCount == 0);
    
            bool down = solve(grid, i + 1, j, openCount);
            bool right = solve(grid, i, j + 1, openCount);
    
            return dp[i][j][openCount] = down || right;
        }
    
    public:
        bool hasValidPath(vector<vector<char>>& grid) {
            n = grid.size();
            m = grid[0].size();
            if((m + n - 1) % 2 != 0) return false;
            if(grid[0][0] == ')' || grid[n - 1][m - 1] == '(') return false;
            
            memset(dp, -1, sizeof(dp));
    
            return solve(grid, 0, 0, 0);
        }
    };

/*
    ============================================================
    LeetCode 2267 - Check if There Is a Valid Parentheses String
    Path in a Grid
    ============================================================

    Approach:
    ------------------------------------------------------------
    Use DFS + memoization.

    The important state is:

        (i, j, openCount)

    where:

        i, j
            -> current cell

        openCount
            -> number of currently unmatched '(' after processing
               the path up to this cell

    At every cell:

        '(' -> openCount++
        ')' -> openCount--

    If `openCount` ever becomes negative, the path is invalid.

    From every cell we can move:

        down
        right

    So DFS checks whether either direction can eventually reach
    the bottom-right cell with:

        openCount == 0


    ============================================================
    Key Observation
    ============================================================

    A valid parentheses string must satisfy two conditions:

        1. At no point can ')' exceed '('.

        2. At the end, the number of '(' and ')' must be equal.

    `openCount` captures both conditions.

    If:

        openCount < 0

    then we have encountered more closing parentheses than opening
    ones, so the path can never become valid.

    At the destination, we require:

        openCount == 0


    ============================================================
    Important Early Checks
    ============================================================

        if((m + n - 1) % 2 != 0) return false;

    ------------------------------------------------------------

    Every path from `(0,0)` to `(n-1,m-1)` contains exactly:

        n + m - 1

    cells.

    A valid parentheses string must have even length because the
    number of '(' and ')' must be equal.

    Therefore, if the path length is odd, a valid path is
    impossible.

    ------------------------------------------------------------

        if(grid[0][0] == ')' || grid[n - 1][m - 1] == '(')
            return false;

    ------------------------------------------------------------

    The first character must be '(' because a valid parentheses
    string cannot start with ')'.

    Similarly, the final character must be ')' because the final
    balance must become zero.


    ============================================================
    DP State
    ============================================================

        dp[i][j][openCount]

    means:

        "Starting from cell (i,j), with `openCount` unmatched
         opening parentheses currently active, is it possible to
         reach the destination and form a valid parentheses
         string?"

    The answer is stored as:

        true  -> possible
        false -> impossible

    Memoization prevents solving the same state repeatedly.


    ============================================================
    State Transition
    ============================================================

    First process the current cell:

        openCount += (grid[i][j] == '(') ? 1 : -1;

    ------------------------------------------------------------

    Then:

        if(openCount < 0)
            return false;

    because the current path already has an invalid prefix.

    From the current cell there are at most two choices:

        down  = solve(i + 1, j, openCount)

        right = solve(i, j + 1, openCount)

    Therefore:

        dp[i][j][openCount] = down || right


    ============================================================
    Base Case
    ============================================================

    If we reach:

        i == n - 1
        j == m - 1

    there are no more cells to process.

    Therefore the path is valid exactly when:

        openCount == 0

    So:

        return dp[i][j][openCount] = (openCount == 0);


    ============================================================
    Example
    ============================================================

    Suppose a path produces:

        ( ( ) )

    The balance changes as:

        '(' -> 1
        '(' -> 2
        ')' -> 1
        ')' -> 0

    Since the balance never becomes negative and ends at zero,
    this path is valid.

    ------------------------------------------------------------

    An invalid path such as:

        ) ( )

    gives:

        ')' -> -1

    The algorithm immediately returns false because:

        openCount < 0


    ============================================================
    Why Memoization Is Needed
    ============================================================

    Multiple different paths can reach the same cell with the
    same `openCount`.

    For example, if we reach:

        (i, j, 2)

    through two different paths, the future possibilities are
    identical.

    Therefore we only need to solve that state once.

    This is why the DP state contains exactly:

        position + current balance


    ============================================================
    Complexity
    ============================================================

    There are at most:

        n * m * O(n + m)

    possible states because `openCount` is bounded by the path
    length.

    Each state has at most two transitions.

    Therefore:

        Time:  O(n * m * (n + m))

        Space: O(n * m * (n + m))

    including the memoization table and recursion stack.


    ============================================================
    Core Idea
    ============================================================

    Treat the grid path as a parentheses string.

    Maintain its current balance:

        '(' -> +1
        ')' -> -1

    Reject immediately if the balance becomes negative.

    At the destination, accept only if the balance is zero.

    Since many paths can reach the same:

        (row, col, balance)

    state, memoize it.

    ------------------------------------------------------------
    In short:

        DFS
          +
        balance tracking
          +
        memoization
          =
        valid grid-path check
    ============================================================
*/