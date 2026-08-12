class Solution {
    private: 
        int t[101]; // dp
    
        int solve(vector<int>& nums, int i) {
            if(i >= nums.size()) return 0;
    
            if(t[i] != -1) return t[i];
    
            int steal = nums[i] + solve(nums, i + 2); // include nums[i];
            int skip = solve(nums, i + 1); // not include nums[i];
    
            return t[i] = max(steal, skip);
        }
    
    public:
        int rob(vector<int>& nums) {
            memset(t, -1, sizeof(t));
            return solve(nums, 0);
        }
    };

/*
LeetCode 198. House Robber

Idea:
------

We have houses arranged in a row.

Each house contains some amount of money, but we cannot rob
two adjacent houses because that would trigger the alarm.

For every house, we have exactly two choices:

    1. Steal from the current house
    2. Skip the current house

If we steal nums[i], we cannot steal nums[i + 1], so the next
house we can consider is i + 2.

This gives the recurrence:

    dp[i] = max(
        nums[i] + dp[i + 2],   // steal current house
        dp[i + 1]              // skip current house
    )

Your solution implements this recurrence using recursion +
memoization.

------------------------------------------------------------

DP Meaning:
-----------

The most important thing to understand is what t[i] means.

    t[i] = maximum amount of money we can rob starting
           from house i

So t[i] does NOT mean:

    "maximum money robbed from the first i houses"

Instead, it means:

    "maximum money we can collect from index i onward."

For example:

    nums = [2, 7, 9, 3, 1]

    t[2]

means:

    maximum money we can rob from:

        [9, 3, 1]

------------------------------------------------------------

Base Case:
----------

    if(i >= nums.size()) return 0;

If i goes beyond the last house, there are no more houses
to rob.

Therefore:

    maximum money = 0

For example:

    solve(nums, 5) -> 0

for an array of size 5.

This also handles the case where we steal the last house and
move to:

    i + 2

which may go beyond the array.

------------------------------------------------------------

Memoization:
------------

    if(t[i] != -1) return t[i];

The recursive solution can reach the same index multiple times.

For example:

    solve(0)
       |
       +---- solve(2)
       |       |
       |       +---- solve(4)
       |
       +---- solve(1)
               |
               +---- solve(3)
               |
               +---- solve(4)

Notice that:

    solve(4)

can be calculated more than once.

Instead of solving it again, we store its answer in:

    t[4]

So whenever we reach index 4 again:

    if(t[4] != -1)
        return t[4];

This is called memoization.

------------------------------------------------------------

Two Choices at Every House:
----------------------------

    int steal = nums[i] + solve(nums, i + 2);

This represents the case where we rob the current house.

We receive:

    nums[i]

But because adjacent houses cannot both be robbed, we cannot
consider:

    i + 1

So we continue from:

    i + 2

Therefore:

    steal = nums[i] + solve(i + 2)

------------------------------------------------------------

Skip Current House:
--------------------

    int skip = solve(nums, i + 1);

Here we don't rob the current house.

Since we didn't rob it, we are free to consider the very next
house:

    i + 1

Therefore:

    skip = solve(i + 1)

------------------------------------------------------------

Choose the Better Option:
--------------------------

    return t[i] = max(steal, skip);

At every house we choose whichever option gives more money:

    steal
       OR
    skip

So:

    t[i] = max(steal, skip)

We also store the result in t[i] so that this state does not
need to be calculated again.

------------------------------------------------------------

Example:
--------

nums = [2, 7, 9, 3, 1]

Start:

    solve(0)

We have two choices.

------------------------------------------------

Choice 1: Steal house 0

    money = 2

Then house 1 cannot be robbed:

    2 + solve(2)

------------------------------------------------

Choice 2: Skip house 0

    solve(1)

So:

    solve(0)
       =
    max(
        2 + solve(2),
        solve(1)
    )

Now consider solve(2):

    nums[2] = 9

Again:

    steal = 9 + solve(4)
    skip  = solve(3)

Therefore:

    solve(2) = max(9 + solve(4), solve(3))

Eventually the maximum is:

    2 + 9 + 1 = 12

So the answer is:

    12

The houses robbed are:

    [2, 9, 1]

------------------------------------------------------------

Why Memoization Is Important:
------------------------------

Without:

    t[i]

the recursion would repeatedly solve the same subproblems.

The recursion tree would contain many duplicate calls.

For example, a state such as:

    solve(4)

can be reached from multiple different paths.

Memoization converts those repeated calculations into a
single calculation.

Each index is solved at most once.

------------------------------------------------------------

Why t Has Size 101:
--------------------

    int t[101];

The array is used to store the DP result for every possible
index.

Because the problem's constraint allows at most 100 houses,
indices 0 through 99 are sufficient, and size 101 provides
enough space.

You initialize it with:

    memset(t, -1, sizeof(t));

So:

    -1 = this state has not been calculated yet.

Once calculated:

    t[i] = actual maximum amount

Since the answer is non-negative, -1 is a safe marker for
"not calculated."

------------------------------------------------------------

Why Use i + 2 When Stealing?
-----------------------------

This is the key constraint of the problem.

If we rob:

    house i

we cannot rob:

    house i + 1

because they are adjacent.

Therefore the next valid house is:

    i + 2

So:

    steal = nums[i] + solve(i + 2)

But if we skip house i, we can immediately consider:

    i + 1

so:

    skip = solve(i + 1)

------------------------------------------------------------

Overall Recurrence:
-------------------

The entire solution can be summarized as:

    solve(i) =
        max(
            nums[i] + solve(i + 2),
            solve(i + 1)
        )

with:

    solve(i) = 0    when i >= n

and memoization:

    t[i] = solve(i)

------------------------------------------------------------

Top-Down DP:
-------------

This solution is called Top-Down Dynamic Programming.

Why?

Because we start from the final problem:

    solve(0)

and recursively break it into smaller problems:

    solve(1)
    solve(2)
    solve(3)
    ...

Whenever a state is solved, we save its result.

So the approach is:

    Recursion
       +
    Memoization
       =
    Top-Down DP

------------------------------------------------------------

Comparison With Bottom-Up DP:
------------------------------

The same problem can also be solved using an iterative DP
array:

    dp[i] = maximum money considering houses up to i

But your solution uses the other direction:

    t[i] = maximum money starting from i

Both approaches use the same fundamental recurrence, but the
state definition is different.

------------------------------------------------------------

Complexity:
-----------

There are n possible states:

    solve(0)
    solve(1)
    ...
    solve(n-1)

Because of memoization, each state is calculated only once.

Each state does O(1) work after its recursive calls.

Therefore:

    Time Complexity: O(n)

The recursion can go at most n levels deep.

So:

    Auxiliary Space: O(n)

because of:

    1. Memoization array
    2. Recursion call stack

The fixed-size array itself is constant with respect to the
problem's declared maximum, but algorithmically the DP storage
is O(n).

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This is a classic "Take or Skip" DP problem.

At every index:

             house i
             /     \
         STEAL     SKIP
           |         |
        i + 2      i + 1

If we STEAL:

    nums[i] + solve(i + 2)

If we SKIP:

    solve(i + 1)

Take the better choice:

    max(steal, skip)

So whenever you see a problem where at every position you have
a choice like:

    take this element
    OR
    don't take this element

and taking it affects the next state, think about:

    Take / Skip DP

*/