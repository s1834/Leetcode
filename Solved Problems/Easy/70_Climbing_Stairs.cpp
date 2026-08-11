class Solution {
    public:
        int climbStairs(int n) {
            if(n <= 3) return n;
            int a = 2, b = 3, c; // a = n(2), b = n(3)
            for(int i = 4; i <= n; i++) {
                c = a + b;
                a = b;
                b = c;
            }
            return c;
        }
    };

/*
LeetCode 70. Climbing Stairs

Idea:
------

There are n stairs, and at each step we can climb either:

    1 step
    OR
    2 steps

We need to find the total number of distinct ways to reach
the nth stair.

The key observation is that to reach stair n, our last move
must be either:

    1. From stair n - 1 by taking 1 step
    2. From stair n - 2 by taking 2 steps

Therefore:

    ways(n) = ways(n - 1) + ways(n - 2)

This is exactly the Fibonacci-style recurrence.

------------------------------------------------------------

Base Cases:
-----------

    if(n <= 3) return n;

For:

    n = 1

There is only:

    1

way:

    1

For:

    n = 2

There are:

    2

ways:

    1 + 1
    2

For:

    n = 3

There are:

    3

ways:

    1 + 1 + 1
    1 + 2
    2 + 1

So:

    ways(1) = 1
    ways(2) = 2
    ways(3) = 3

------------------------------------------------------------

Why Fibonacci?
---------------

The Fibonacci sequence follows:

    F(n) = F(n-1) + F(n-2)

Climbing Stairs follows the exact same recurrence, but with
different starting values:

    ways(1) = 1
    ways(2) = 2

Therefore:

    ways(3) = 3
    ways(4) = 5
    ways(5) = 8
    ways(6) = 13
    ...

So this problem can be solved using the same
"previous two states" technique.

------------------------------------------------------------

Why Only Store Two Values?
--------------------------

To calculate:

    ways(n)

we only need:

    ways(n - 1)
    ways(n - 2)

We don't need all previous values.

Therefore:

    a = ways(n - 2)
    b = ways(n - 1)

and:

    c = a + b

After calculating the current value, shift the variables:

    a = b
    b = c

This is called

State Compression

because we reduce the DP array from O(n) space to O(1).

------------------------------------------------------------

Initialization:
---------------

    int a = 2, b = 3, c;

Here:

    a = ways(2)
    b = ways(3)

We already handled n <= 3, so for n >= 4 we start with
these two known values.

------------------------------------------------------------

Loop:
------

    for(int i = 4; i <= n; i++) {

We start at 4 because:

    ways(1), ways(2), ways(3)

are already known.

For every stair from 4 to n, calculate:

    c = a + b;

where:

    a = ways(i - 2)
    b = ways(i - 1)

Therefore:

    c = ways(i)

Then shift:

    a = b;
    b = c;

After the shift:

    a = ways(i - 1)
    b = ways(i)

So the variables are always ready for the next iteration.

------------------------------------------------------------

Example: n = 5
--------------

Initially:

    a = 2   // ways(2)
    b = 3   // ways(3)

i = 4:

    c = 2 + 3 = 5

Update:

    a = 3
    b = 5

So:

    b = ways(4)

--------------------------------

i = 5:

    c = 3 + 5 = 8

Update:

    a = 5
    b = 8

So:

    b = ways(5)

Return:

    c = 8

Therefore:

    answer = 8

------------------------------------------------------------

Why Return c?
--------------

After the final iteration:

    c

contains:

    ways(n)

For example, when n = 5:

    c = 8

which is the answer.

You could also return b after the loop because after each
iteration:

    b = current answer

but with your current implementation,

    return c;

is correct.

------------------------------------------------------------

Important Recurrence:
---------------------

Think about the LAST move.

To reach stair n:

        n
       / \
      /   \
 n - 1    n - 2

From:

    n - 1

we take:

    1 step

From:

    n - 2

we take:

    2 steps

Therefore:

    ways(n)
      =
    ways(n-1) + ways(n-2)

This is the main idea of the problem.

------------------------------------------------------------

Why Not Use Recursion?
----------------------

A recursive solution repeatedly calculates the same states.

For example:

    ways(5)
      /      \
 ways(4)    ways(3)
 /    \
...   ...

The same values such as ways(3) and ways(2) are calculated
multiple times.

That gives exponential time for the simple recursive
solution.

Your iterative solution calculates every state exactly once.

------------------------------------------------------------

Time Complexity:
----------------

The loop runs from:

    4 -> n

Therefore:

    O(n)

time.

------------------------------------------------------------

Space Complexity:
-----------------

Only three variables are used:

    a
    b
    c

Therefore:

    O(1)

extra space.

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

When you see:

    "How many ways can I reach state n?"

and the current state depends only on the previous two states:

    dp[n] = dp[n-1] + dp[n-2]

you can often use the Fibonacci/state-compression pattern:

    previous previous
           ↓
        previous
           ↓
         current

    c = a + b
    a = b
    b = c

For Climbing Stairs:

    ways(1) = 1
    ways(2) = 2

and:

    ways(n) = ways(n-1) + ways(n-2)

*/