class Solution {
    public:
        int minCostClimbingStairs(vector<int>& cost) {
            int n = cost.size();
            if(n == 2) return min(cost[0], cost[1]);
            int a = cost[0], b = cost[1], c;
            for(int i = 2; i < n; i++) {
                c = cost[i] + min(a, b);
                a = b;
                b = c;
            }
            return min(a, b);
        }
    };

/*
LeetCode 746. Min Cost Climbing Stairs

Idea:
------

We are given the cost of stepping on each stair.

From any stair, we can climb either:

    1 step
    OR
    2 steps

We can start from either stair 0 or stair 1.

The goal is to reach the top with minimum total cost.

The important observation is:

To reach stair i, we could have come from either:

    i - 1
    OR
    i - 2

Therefore, the minimum cost to reach stair i is:

    cost[i] + min(minCost(i - 1), minCost(i - 2))

This gives the DP recurrence:

    dp[i] = cost[i] + min(dp[i-1], dp[i-2])

------------------------------------------------------------

Important Difference From LeetCode 70:
---------------------------------------

In Climbing Stairs (70), we count the number of ways.

Here, we are minimizing the total cost.

So instead of:

    dp[i] = dp[i-1] + dp[i-2]

we use:

    dp[i] = cost[i] + min(dp[i-1], dp[i-2])

The structure is still the same:

    current state depends on previous two states.

------------------------------------------------------------

Base Cases:
-----------

The cost to reach stair 0 is:

    cost[0]

because we pay cost[0] when stepping on it.

Similarly, the cost to reach stair 1 is:

    cost[1]

So:

    a = cost[0]
    b = cost[1]

where:

    a = minimum cost to reach stair 0
    b = minimum cost to reach stair 1

------------------------------------------------------------

Why Do We Need the Special Case n == 2?
----------------------------------------

If:

    cost = [10, 15]

we can start from either stair 0 or stair 1.

To reach the top:

    Start at 0 -> cost = 10
    Start at 1 -> cost = 15

Therefore:

    answer = min(10, 15)

which is:

    min(cost[0], cost[1])

So:

    if(n == 2) return min(cost[0], cost[1]);

handles this case directly.

------------------------------------------------------------

Transition:
-----------

For every stair starting from index 2:

    c = cost[i] + min(a, b);

Here:

    a = minimum cost to reach stair i - 2
    b = minimum cost to reach stair i - 1

We can reach stair i from either one.

Therefore, we choose the cheaper previous stair:

    min(a, b)

and then pay the cost of the current stair:

    cost[i]

So:

    c = cost[i] + min(a, b)

Now c represents:

    minimum cost to reach stair i

------------------------------------------------------------

Why Do We Shift a and b?
-------------------------

After calculating:

    c = dp[i]

we move the previous states forward:

    a = b;
    b = c;

Before the update:

    a = dp[i-2]
    b = dp[i-1]
    c = dp[i]

After the update:

    a = dp[i-1]
    b = dp[i]

This means the next iteration already has the two previous
states it needs.

------------------------------------------------------------

Example:
--------

cost = [10, 15, 20]

Initially:

    a = 10
    b = 15

Meaning:

    a = minimum cost to reach stair 0
    b = minimum cost to reach stair 1

--------------------------------

i = 2

To reach stair 2, we can come from:

    stair 0 -> cost 10
    stair 1 -> cost 15

Choose the cheaper:

    min(10,15) = 10

Then pay:

    cost[2] = 20

So:

    c = 20 + 10
      = 30

Update:

    a = 15
    b = 30

--------------------------------

Now we have reached stair 2 with minimum cost 30.

But the problem says we can climb from either of the last
two stairs to reach the top.

Therefore, the answer is:

    min(a, b)

    = min(15, 30)
    = 15

So the cheapest path is:

    Start at stair 1
    pay 15
    jump directly to the top

Answer:

    15

------------------------------------------------------------

Why Return min(a, b)?
----------------------

This is the most important detail of the problem.

The "top" is not an actual stair in the cost array.

We can reach the top by taking either:

    1 step from stair n - 1

or:

    2 steps from stair n - 2

And reaching the top itself has no additional cost.

Therefore:

    answer = min(
        minimum cost to reach stair n-1,
        minimum cost to reach stair n-2
    )

At the end:

    a = dp[n-2]
    b = dp[n-1]

so:

    return min(a, b);

------------------------------------------------------------

Example:
--------

cost = [1,100,1,1,1,100,1,1,100,1]

We calculate the minimum cost to reach every stair:

    dp[0] = 1
    dp[1] = 100

    dp[2] = 1 + min(1,100)
          = 2

    dp[3] = 1 + min(100,2)
          = 3

    dp[4] = 1 + min(2,3)
          = 3

    ...

We don't actually store the entire dp array.

Instead, we only keep:

    previous two dp values.

This is why the solution uses:

    a
    b
    c

instead of:

    vector<int> dp;

------------------------------------------------------------

State Compression:
------------------

A normal DP solution could use:

    dp[i] = cost[i] + min(dp[i-1], dp[i-2])

and store:

    dp[0], dp[1], ..., dp[n-1]

That would require:

    O(n)

space.

But notice that to calculate dp[i], we only need:

    dp[i-1]
    dp[i-2]

We don't need older values anymore.

So we compress the DP state into three variables:

    a = dp[i-2]
    b = dp[i-1]
    c = dp[i]

This reduces the space complexity to:

    O(1)

------------------------------------------------------------

Why Is the Recurrence Correct?
------------------------------

To reach stair i, there are only two possible previous
stairs:

    i - 1
    i - 2

If we came from i - 1:

    cost = dp[i-1] + cost[i]

If we came from i - 2:

    cost = dp[i-2] + cost[i]

We want the cheaper option:

    dp[i] =
        cost[i] + min(dp[i-1], dp[i-2])

There are no other ways to reach stair i because we can only
take 1 or 2 steps.

------------------------------------------------------------

Overall Flow:
-------------

    cost array
        ↓
    Start with:
        dp[0] = cost[0]
        dp[1] = cost[1]
        ↓
    For every i >= 2:
        dp[i] = cost[i] + min(dp[i-1], dp[i-2])
        ↓
    Compress DP:
        a = previous previous
        b = previous
        c = current
        ↓
    Top can be reached from either
    n-1 or n-2
        ↓
    return min(a, b)

------------------------------------------------------------

Time Complexity:
----------------

We iterate through the cost array once.

Therefore:

    Time Complexity: O(n)

------------------------------------------------------------

Space Complexity:
-----------------

Only three variables are used:

    a
    b
    c

Therefore:

    Space Complexity: O(1)

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This is a classic

1D Dynamic Programming + State Compression

problem.

The recurrence is:

    dp[i] = cost[i] + min(dp[i-1], dp[i-2])

Whenever a DP state depends only on the previous two states,
we can often replace the entire DP array with two variables.

Here:

    a = dp[i-2]
    b = dp[i-1]

Calculate:

    c = cost[i] + min(a,b)

Then shift:

    a = b
    b = c

Finally, because the top itself has no cost and can be reached
from either of the last two stairs:

    return min(a, b);

*/