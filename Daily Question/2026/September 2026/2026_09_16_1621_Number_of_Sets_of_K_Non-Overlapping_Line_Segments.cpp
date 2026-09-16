class Solution {
    public:
        int numberOfSets(int n, int k) {
            int MOD = 1e9 + 7;
            int dp[1001][1001] = {};
    
            // Base Case
            // k == 0 ----> 1 (i < n)
            for(int i = 0; i < n; i++) dp[0][i] = 1;
    
            for(int K = 1; K <= k; K++) {
                vector<int> prevRowSum(n + 1, 0); // suffix sum
                for(int x = n - 1; x >= 0; x--) prevRowSum[x] = (prevRowSum[x + 1] + dp[K - 1][x]) % MOD;
    
                for(int i = n - 1; i >= 0; i--) {
                    int take = prevRowSum[i + 1];
                    int skip = dp[K][i + 1] % MOD;
                    dp[K][i] = (take + skip) % MOD;
                }
            }
    
            return dp[k][0];
        }
    };

/*
LeetCode 1621. Number of Sets of K Non-Overlapping Line Segments

Approach:
---------

We use Dynamic Programming + Suffix Sum.

The key idea is to count how many ways we can choose exactly k
non-overlapping line segments from n points.

We consider the points:

    0, 1, 2, ..., n - 1

A segment is formed by choosing two points:

    start < end

and we need to choose exactly k segments such that they do not
overlap.

------------------------------------------------------------

DP Definition:
--------------

We define:

    dp[K][i]

as the number of ways to choose exactly K non-overlapping segments
using points starting from index i.

So:

    dp[K][i]

means:

    Number of ways to create K segments using points
    i, i + 1, ..., n - 1.

------------------------------------------------------------

Base Case:
----------

When:

    K = 0

we need to choose zero segments.

There is exactly one way to do that:

    choose nothing

Therefore:

    dp[0][i] = 1

for every valid point i.

Code:

    for(int i = 0; i < n; i++)
        dp[0][i] = 1;

This is important because every time we successfully choose the
last segment, the remaining problem becomes:

    choose 0 more segments

which has exactly one valid way.

------------------------------------------------------------

Transition:
-----------

Suppose we are currently at point:

    i

and want to choose K segments.

There are two possibilities:

    1. Skip point i
    2. Start a segment at point i

------------------------------------------------------------

Case 1: Skip Point i
--------------------

If we do not use point i as the start of a segment, we simply
move to the next point:

    skip = dp[K][i + 1]

So:

    dp[K][i] = dp[K][i + 1]

if we skip i.

------------------------------------------------------------

Case 2: Take Point i as Start
-----------------------------

Suppose we use i as the starting point of the next segment.

We need to choose its ending point.

The segment can end at any point:

    i + 1, i + 2, ..., n - 1

If the segment ends at x, then the remaining K - 1 segments must
start from x or later.

Therefore, the number of ways for a particular ending point x is:

    dp[K - 1][x]

So the total number of ways to start a segment at i is:

    dp[K - 1][i + 1]
  + dp[K - 1][i + 2]
  + ...
  + dp[K - 1][n - 1]

This is a suffix sum.

------------------------------------------------------------

Why prevRowSum?
---------------

Calculating the above sum separately for every i would make the
transition O(n) for every state, resulting in O(k * n^2).

Instead, we precompute suffix sums of the previous DP row.

    prevRowSum[x]

represents:

    dp[K - 1][x] + dp[K - 1][x + 1] + ...
    + dp[K - 1][n - 1]

Code:

    vector<int> prevRowSum(n + 1, 0);

    for(int x = n - 1; x >= 0; x--)
        prevRowSum[x] =
            (prevRowSum[x + 1] + dp[K - 1][x]) % MOD;

Now:

    prevRowSum[i + 1]

gives us exactly:

    dp[K - 1][i + 1]
  + dp[K - 1][i + 2]
  + ...
  + dp[K - 1][n - 1]

So:

    take = prevRowSum[i + 1];

------------------------------------------------------------

Combining Take and Skip:
------------------------

For every state dp[K][i]:

    take = prevRowSum[i + 1];

    skip = dp[K][i + 1];

Therefore:

    dp[K][i] = take + skip

or:

    dp[K][i] =
        prevRowSum[i + 1] + dp[K][i + 1]

We take modulo MOD because the number of possible sets can
become extremely large.

------------------------------------------------------------

Why Does Choosing the Ending Point Work?
-----------------------------------------

Suppose we are at point i.

If we choose a segment:

    [i, x]

then the next segment must start at or after x.

For example:

    [1, 4]

and another segment:

    [4, 6]

are allowed because they only share the endpoint.

So after choosing [i, x], the remaining problem starts from:

    x

This is why the transition uses:

    dp[K - 1][x]

rather than:

    dp[K - 1][x + 1]

The suffix sum starts at:

    i + 1

because a segment must have two distinct endpoints:

    start < end

------------------------------------------------------------

Bottom-Up Order:
----------------

We calculate K from:

    1 -> k

For every K, we calculate i from:

    n - 1 -> 0

Why backwards?

Because:

    dp[K][i]

depends on:

    dp[K][i + 1]

which must already be calculated.

It also depends on:

    dp[K - 1][...]

which belongs to the previous row and is already available.

Therefore, the order is:

    K = 0
       |
       v
    K = 1
       |
       v
    K = 2
       |
       v
      ...
       |
       v
    K = k

and inside each row:

    i = n - 1 -> 0

------------------------------------------------------------

Example:
--------

Consider:

    n = 4
    points = [0, 1, 2, 3]

and:

    k = 1

We need to choose exactly one segment.

Possible segments are:

    [0,1]
    [0,2]
    [0,3]
    [1,2]
    [1,3]
    [2,3]

So there are:

    6

ways.

The DP calculates these possibilities by considering every
possible starting point and every possible ending point.

------------------------------------------------------------

Meaning of take:
----------------

At:

    dp[K][i]

take means:

    Start a new segment at point i.

We can choose any valid endpoint after i.

For every possible endpoint x:

    dp[K - 1][x]

counts the ways to choose the remaining K - 1 segments.

The suffix sum combines all these possibilities.

------------------------------------------------------------

Meaning of skip:
-----------------

skip means:

    Do not start a segment at point i.

So we simply move forward:

    dp[K][i + 1]

This ensures that every possible starting point is considered.

------------------------------------------------------------

Important:
----------

We are counting SETS of non-overlapping segments.

The DP processes the segments from left to right, so the same
collection of segments is not counted in different orders.

For example, choosing:

    [0,1] then [2,3]

is naturally processed from left to right.

We do not separately count:

    [2,3] then [0,1]

as another arrangement.

------------------------------------------------------------

DP Visualization:
-----------------

For a fixed K:

    dp[K][i]

          / \
         /   \
      skip   take
       |       |
       v       v
    dp[K][i+1]  choose endpoint x
                   |
                   v
             dp[K-1][x]
                   |
                   v
              suffix sum

Therefore:

    dp[K][i]
        =
    dp[K][i + 1]
        +
    sum(dp[K - 1][x])
        for x = i + 1 ... n - 1

------------------------------------------------------------

Why We Need MOD:
----------------

The number of possible sets grows very quickly.

Therefore, every addition is performed modulo:

    1e9 + 7

Code:

    (take + skip) % MOD

and:

    (prevRowSum[x + 1] + dp[K - 1][x]) % MOD

------------------------------------------------------------

Final Answer:
-------------

We start from:

    i = 0

because all n points are available.

We need exactly:

    k

segments.

Therefore the answer is:

    dp[k][0]

------------------------------------------------------------

Algorithm:
----------

    1. Create dp[n + 1][n + 1].

    2. Initialize:

           dp[0][i] = 1

       because choosing zero segments has exactly one way.

    3. For every K from 1 to k:

           a. Build suffix sums of dp[K - 1].

           b. Iterate i from n - 1 to 0.

           c. Calculate:

                  take = prevRowSum[i + 1]

                  skip = dp[K][i + 1]

           d. Store:

                  dp[K][i] = (take + skip) % MOD

    4. Return:

           dp[k][0]

------------------------------------------------------------

Time Complexity:
----------------

There are k DP rows.

For each row:

    1. Build suffix sum -> O(n)

    2. Fill DP row -> O(n)

Therefore:

    Time = O(n * k)

------------------------------------------------------------

Space Complexity:
-----------------

The full DP table contains:

    (k + 1) * (n + 1)

states.

Additionally, we maintain:

    prevRowSum

of size O(n).

Therefore:

    Space = O(n * k)

------------------------------------------------------------

Core Idea:
----------

    dp[K][i]

        |
        +------------------+
        |                  |
      Skip               Take
        |                  |
        v                  v
    dp[K][i+1]       Start segment at i
                           |
                           v
                    choose endpoint x
                           |
                           v
                    dp[K-1][x]
                           |
                           v
                      suffix sum

So:

    dp[K][i]
       =
    dp[K][i + 1]
       +
    sum(dp[K - 1][x])
       for x > i

The suffix sum is the optimization that reduces the transition
from O(n) to O(1), giving an overall:

    O(n * k)

solution.
*/