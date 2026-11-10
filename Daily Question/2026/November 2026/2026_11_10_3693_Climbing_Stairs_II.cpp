class Solution {
    public:
        vector<int> dp;
    
        int solve(int i, int n, vector<int>& costs) {
            if (i == n) return 0;
    
            if (dp[i] != -1) return dp[i];
    
            int cost = INT_MAX;
    
            // jump of 1
            int j = i + 1;
            if(j <= n) cost = solve(j, n, costs) + costs[j - 1] + (j - i) * (j - i);
           
            // jump of 2
            j = i + 2;
            if (j <= n) cost = min(cost, solve(j, n, costs) + costs[j - 1] + (j - i) * (j - i));
            
            // jump of 3
            j = i + 3;
            if (j <= n) cost = min(cost, solve(j, n, costs) + costs[j - 1] + (j - i) * (j - i));
    
            return dp[i] = cost;
        }
    
        int climbStairs(int n, vector<int>& costs) {
            dp.assign(n + 1, -1);
            return solve(0, n, costs);
        }
    };

/*
    LeetCode 3693: Climbing Stairs II

    Approach: Top-Down Dynamic Programming (Recursion + Memoization)

    Intuition:
    We need to reach stair `n`, starting from stair 0.

    From any stair `i`, we can jump:
        - 1 step
        - 2 steps
        - 3 steps

    Each jump has a cost consisting of:
        1. The cost of landing on the destination stair.
        2. The square of the jump length.

    Therefore, if we jump from stair `i` to stair `j`, the total cost is:

        costs[j - 1] + (j - i) * (j - i) + solve(j)

    Notice that `costs` is 0-indexed, while stairs are treated as
    1-indexed for landing costs. Hence, landing on stair `j` requires
    accessing `costs[j - 1]`.

    Our goal is to find the minimum cost required to reach stair `n`.

    DP State:
        dp[i] = Minimum cost required to reach stair `n`
                starting from stair `i`.

    Base Case:
        if (i == n) return 0;

        Once we reach stair `n`, no additional cost is required.

    Memoization:
        if (dp[i] != -1) return dp[i];

        Before calculating the answer for stair `i`, we check whether
        its result has already been computed.
        If so, we return the stored result instead of exploring the
        same states again.

    Step-by-Step Explanation:

    1. Initialize:
        int cost = INT_MAX;

       This stores the minimum cost among all valid jumps from stair `i`.

    2. Jump of 1:
        j = i + 1;

        If j <= n, the jump is valid.

        Total cost:
            solve(j, n, costs)
            + costs[j - 1]
            + (j - i) * (j - i)

        We calculate the cost of landing on stair `j`, the jump penalty,
        and the minimum cost required to reach the destination from `j`.

    3. Jump of 2:
        j = i + 2;

        If valid, calculate the same expression and take the minimum
        with the previously calculated cost.

    4. Jump of 3:
        j = i + 3;

        Again, if valid, calculate the total cost and update the minimum.

    5. Store the result:
        return dp[i] = cost;

       Once all possible jumps have been considered, store the minimum
       cost for the current stair and return it.

    Example:
        n = 4
        costs = [1, 2, 3, 4]

        We start at stair 0 and need to reach stair 4.

        One possible path:
            0 -> 1 -> 3 -> 4

        Cost of each jump:

            0 -> 1:
                costs[0] + (1 - 0)^2
                = 1 + 1 = 2

            1 -> 3:
                costs[2] + (3 - 1)^2
                = 3 + 4 = 7

            3 -> 4:
                costs[3] + (4 - 3)^2
                = 4 + 1 = 5

        Total cost = 2 + 7 + 5 = 14

        The DP explores all valid combinations of jumps and returns
        the minimum possible total cost.

    Complexity Analysis:

    Let n be the destination stair.

    - Time Complexity: O(n)
      There are n + 1 possible states (0 through n).
      Each state is computed only once because of memoization.
      Every state considers at most 3 possible jumps.
      Therefore, the total time complexity is O(3 * n) = O(n).

    - Space Complexity: O(n)
      The DP array stores n + 1 states.
      The recursion stack can also grow up to O(n) in the worst case.

      Overall auxiliary space complexity is O(n).

    Core Idea:
    Use recursion to explore jumps of length 1, 2, and 3.
    For every jump, add the landing stair's cost and the squared
    jump length.

    Memoize the minimum cost for every starting stair so that each
    state is computed only once.
*/