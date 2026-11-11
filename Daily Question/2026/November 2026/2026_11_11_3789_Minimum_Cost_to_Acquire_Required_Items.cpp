
class Solution {
    public:
        long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
            if (need1 == 0 && need2 == 0) return 0;
    
            if (need1 == 0) return 1LL * min(cost2, costBoth) * need2;
    
            if (need2 == 0) return 1LL * min(cost1, costBoth) * need1;
    
            if (1LL * cost1 + cost2 <= costBoth) return (1LL * cost1 * need1) + (1LL * cost2 * need2);
    
            int minNeed = min(need1, need2);
    
            long long cost = 1LL * costBoth * minNeed;
    
            need1 -= minNeed;
            need2 -= minNeed;
    
            if (need1 == 0) return cost + (1LL * min(cost2, costBoth) * need2);
            return cost + (1LL * min(cost1, costBoth) * need1);
        }
    };

/*
    LeetCode 3789: Minimum Cost to Make Arrays Equal

    Approach: Greedy

    Intuition:
    We need to satisfy two independent requirements:
        - `need1`: Number of operations/items required for requirement 1.
        - `need2`: Number of operations/items required for requirement 2.

    We have three possible costs:
        - `cost1`: Cost of satisfying requirement 1 individually.
        - `cost2`: Cost of satisfying requirement 2 individually.
        - `costBoth`: Cost of satisfying both requirements simultaneously.

    The key observation is that we should use the operation that satisfies
    both requirements whenever it is cheaper than satisfying them separately.

    Step-by-Step Explanation:

    1. Both requirements are already satisfied:
        if (need1 == 0 && need2 == 0) return 0;

       If neither requirement needs anything, the minimum cost is 0.

    2. Only the first requirement is satisfied:
        if (need1 == 0)
            return 1LL * min(cost2, costBoth) * need2;

       We only need to satisfy requirement 2.

       For each remaining unit, we can either:
           - Use the individual operation at cost `cost2`.
           - Use the combined operation at cost `costBoth`.

       Therefore, choose the cheaper option and multiply it by `need2`.

    3. Only the second requirement is satisfied:
        if (need2 == 0)
            return 1LL * min(cost1, costBoth) * need1;

       This is symmetric to the previous case.
       Choose the cheaper operation for satisfying requirement 1.

    4. Check whether individual operations are cheaper:
        if (1LL * cost1 + cost2 <= costBoth)

       If satisfying both requirements individually costs less than or
       equal to one combined operation, there is no benefit in using
       the combined operation.

       Therefore, independently satisfy both requirements:

           cost1 * need1 + cost2 * need2

       `1LL` ensures that multiplication is performed using long long
       to avoid integer overflow.

    5. Use combined operations for the common requirement:
        int minNeed = min(need1, need2);

       The combined operation satisfies one unit of each requirement.

       We can use it for the maximum number of common units, which is
       the minimum of `need1` and `need2`.

        long long cost = 1LL * costBoth * minNeed;

       Add the cost of these combined operations.

    6. Update the remaining requirements:
        need1 -= minNeed;
        need2 -= minNeed;

       After using the combined operations, at least one of the two
       requirements becomes zero.

    7. Handle the remaining requirement:
        if (need1 == 0)
            return cost + (1LL * min(cost2, costBoth) * need2);

       If requirement 1 is completely satisfied, only requirement 2
       remains. Choose the cheaper of its individual operation and
       the combined operation.

       Otherwise, only requirement 1 remains, so choose between
       `cost1` and `costBoth`.

    Example:
        cost1 = 5
        cost2 = 4
        costBoth = 6
        need1 = 3
        need2 = 2

        Individual cost for satisfying both:
            cost1 + cost2 = 5 + 4 = 9

        Combined operation cost:
            costBoth = 6

        Since 6 < 9, using the combined operation is cheaper.

        minNeed = min(3, 2) = 2

        Use 2 combined operations:
            cost = 2 * 6 = 12

        Remaining requirements:
            need1 = 3 - 2 = 1
            need2 = 2 - 2 = 0

        Only requirement 1 remains.

        Cheapest way to satisfy it:
            min(cost1, costBoth) = min(5, 6) = 5

        Final minimum cost:
            12 + 5 = 17

    Complexity Analysis:
    - Time Complexity: O(1)
      The solution performs only a constant number of comparisons,
      arithmetic operations, and minimum calculations.

    - Space Complexity: O(1)
      Only a constant amount of extra memory is used.

    Core Idea:
    Compare the cost of satisfying both requirements individually
    against the cost of satisfying them together.

    If individual operations are cheaper, handle both requirements
    independently.

    Otherwise, satisfy the maximum common requirement using combined
    operations, then handle whichever requirement remains.
*/