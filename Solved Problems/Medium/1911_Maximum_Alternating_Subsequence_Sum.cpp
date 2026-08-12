class Solution {
    private:
        long long t[100000][2];
    
        long long solve(vector<int>& nums, int idx, int isEven) {
            if(idx >= nums.size()) return 0;
    
            if(t[idx][isEven] != -1) return t[idx][isEven];
    
            long long skip = solve(nums, idx + 1, isEven);
    
            int val = nums[idx];
            if(!isEven) val = -val;
    
            long long take = solve(nums, idx + 1, !isEven) + val;
    
            return t[idx][isEven] = max(skip, take);
        }
        
    public:
        long long maxAlternatingSum(vector<int>& nums) {
            memset(t, -1, sizeof(t));
            return solve(nums, 0, 1);
        }
    };

/*
LeetCode 213. House Robber II

Idea:
------

This problem is almost the same as House Robber I (LeetCode 198),
but there is one important difference:

    The houses are arranged in a CIRCLE.

Therefore:

    House 0 and House n - 1 are also adjacent.

So we cannot rob both the first and the last house.

The easiest way to handle this circular constraint is to split
the problem into two linear House Robber problems.

There are only two possible cases:

    Case 1:
    Don't rob the first house.
    We can consider houses [1 ... n-1].

    Case 2:
    Don't rob the last house.
    We can consider houses [0 ... n-2].

Then take the maximum of the two cases.

------------------------------------------------------------

Why Split Into Two Cases?
--------------------------

Because the first and last houses are adjacent.

So a valid solution must satisfy at least one of these:

    1. First house is not robbed
    2. Last house is not robbed

We solve both possibilities independently.

For example:

    nums = [2, 3, 2]

We cannot rob both:

    house 0 = 2
    house 2 = 2

because they are adjacent in the circle.

So:

    Case 1: skip first
        [3, 2]
        answer = 3

    Case 2: skip last
        [2, 3]
        answer = 3

Final:

    max(3, 3) = 3

------------------------------------------------------------

Helper Function:
----------------

    int solve(vector<int>& nums, int l, int r)

This function solves the normal linear House Robber problem
on the range:

    [l, r)

Notice that r is EXCLUSIVE.

So:

    solve(nums, 0, n - 1)

processes:

    0 ... n - 2

while:

    solve(nums, 1, n)

processes:

    1 ... n - 1

This lets us conveniently remove either the first or last
house.

------------------------------------------------------------

DP State:
---------

Inside solve():

    prevPrev = 0;
    prev = 0;

These represent the two previous DP states.

    prevPrev = dp[i - 2]
    prev     = dp[i - 1]

where:

    dp[i] = maximum money that can be robbed from the
            considered range up to index i.

We don't need the complete DP array because the current answer
only depends on the previous two answers.

------------------------------------------------------------

For Every House:
----------------

    for(int i = l; i < r; i++)

We process every house in the selected range.

At every house we have two choices.

------------------------------------------------------------

1. Rob the Current House
------------------------

    int steal = prevPrev + nums[i];

If we rob house i, we cannot rob house i - 1.

Therefore, we combine:

    nums[i]

with the best answer from two positions before:

    prevPrev

So:

    steal = nums[i] + dp[i - 2]

------------------------------------------------------------

2. Skip the Current House
--------------------------

    int skip = prev;

If we skip the current house, the best answer remains the
best answer we already had before processing this house.

So:

    skip = dp[i - 1]

------------------------------------------------------------

Choose the Better Option:
--------------------------

    int mx = max(steal, skip);

Therefore:

    dp[i] = max(
        dp[i - 1],
        nums[i] + dp[i - 2]
    )

This is exactly the same recurrence as LeetCode 198.

------------------------------------------------------------

Move the DP Variables:
----------------------

    prevPrev = prev;
    prev = mx;

Before updating:

    prevPrev = dp[i - 2]
    prev     = dp[i - 1]

After updating:

    prevPrev = dp[i - 1]
    prev     = dp[i]

So the two variables move forward with the DP.

This is state compression because we don't store the entire
dp array.

------------------------------------------------------------

Case 1: Skip the Last House
----------------------------

    int skipOne = solve(nums, 0, n - 1);

Because r is exclusive, this considers:

    0, 1, 2, ..., n - 2

So house n - 1 is excluded.

This means:

    Last house is NOT robbed.

Now houses 0 and n - 2 form a normal linear House Robber
problem.

------------------------------------------------------------

Case 2: Skip the First House
-----------------------------

    int stealOne = solve(nums, 1, n);

This considers:

    1, 2, 3, ..., n - 1

So house 0 is excluded.

This means:

    First house is NOT robbed.

Again, we now have a normal linear House Robber problem.

------------------------------------------------------------

Final Answer:
-------------

    return max(skipOne, stealOne);

Every valid solution must exclude either:

    first house

or:

    last house

Therefore, solving both cases covers every possible valid
solution.

We simply choose whichever case gives more money.

------------------------------------------------------------

Why Is It "Skip One" and "Steal One"?
--------------------------------------

The variable names:

    skipOne
    stealOne

can be slightly confusing.

They don't actually mean that we definitely "steal" one house.

More accurately:

    skipOne  = solution when the LAST house is skipped

    stealOne = solution when the FIRST house is skipped

The second name could be renamed to something clearer, such as:

    int skipLast = solve(nums, 0, n - 1);
    int skipFirst = solve(nums, 1, n);

This makes the two cases easier to understand.

------------------------------------------------------------

Example:
--------

nums = [2, 7, 9, 3, 1]

Because this is circular:

    2 and 1

are adjacent.

------------------------------------------------

Case 1: Skip Last

Consider:

    [2, 7, 9, 3]

The normal House Robber solution gives:

    2 + 9 = 11

So:

    skipLast = 11

------------------------------------------------

Case 2: Skip First

Consider:

    [7, 9, 3, 1]

The best solution is:

    7 + 3 = 10

So:

    skipFirst = 10

------------------------------------------------

Final:

    max(11, 10) = 11

Therefore:

    answer = 11

------------------------------------------------------------

Why Can't We Just Run House Robber on the Whole Array?
---------------------------------------------------------

If we simply ran the LeetCode 198 solution on:

    [2, 7, 9, 3, 1]

it might choose:

    2 + 9 + 1 = 12

But this is INVALID in a circle because:

    house 0 and house 4

are adjacent.

The circular constraint is exactly why we need to split the
array into two linear cases.

------------------------------------------------------------

Why Do the Two Cases Cover Everything?
----------------------------------------

Suppose a valid solution robs the first house.

Because the first and last houses are adjacent, it cannot rob
the last house.

Therefore, that solution belongs to:

    Case 2: skip last

If a valid solution does not rob the first house, it belongs
to:

    Case 1: skip first

Equivalently, every valid solution can be represented by
excluding at least one of the two circular boundary houses.

Therefore, checking both linear ranges is sufficient.

------------------------------------------------------------

Special Case: n == 1
---------------------

    if(n == 1) return nums[0];

With only one house, there is no circular conflict.

The only possible choice is to rob that house.

For example:

    nums = [5]

Answer:

    5

------------------------------------------------------------

Why We Don't Need a Special Case for n == 2
--------------------------------------------

For:

    nums = [2, 3]

the two houses are adjacent.

Our two cases become:

    solve(nums, 0, 1)
        -> only house 0
        -> 2

    solve(nums, 1, 2)
        -> only house 1
        -> 3

Then:

    max(2, 3) = 3

So the general two-case approach already handles n == 2.

Only n == 1 needs to be handled separately because both
ranges would otherwise become invalid/empty.

------------------------------------------------------------

Connection to LeetCode 198:
----------------------------

LeetCode 198:

    Houses are in a LINE.

We use:

    dp[i] = max(dp[i-1], nums[i] + dp[i-2])

LeetCode 213:

    Houses are in a CIRCLE.

We cannot directly use the same solution because the first and
last houses are adjacent.

So we convert the circular problem into two linear problems:

    Circle
      |
      +-------------------+
      |                   |
    skip first         skip last
      |                   |
      ↓                   ↓
   [1 ... n-1]         [0 ... n-2]
      |                   |
      +---------+---------+
                |
                ↓
             max()

------------------------------------------------------------

Complexity:
-----------

The helper function processes at most n houses.

We call it twice:

    solve(nums, 0, n - 1)
    solve(nums, 1, n)

So:

    Time Complexity: O(n)

because:

    O(n) + O(n) = O(n)

We only use a few variables inside solve():

    prevPrev
    prev
    steal
    skip
    mx

Therefore:

    Space Complexity: O(1)

excluding the recursion stack, since there is no recursion here.

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

House Robber II is:

    House Robber I
          +
    Circular constraint

The key trick is:

    Circular array
         ↓
    First and last are adjacent
         ↓
    Cannot take both
         ↓
    Split into two cases
         ↓
    Case 1: skip first
    Case 2: skip last
         ↓
    Run normal House Robber
         ↓
    Take maximum

So the overall structure is:

    skipLast  = solve(0, n - 1)
    skipFirst = solve(1, n)

    answer = max(skipLast, skipFirst)

This is the key idea to remember for LeetCode 213.
*/