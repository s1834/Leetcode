class Solution {
    private:
        int dp[2500][2500]; // dp of constraints
    
        int solve(vector<int>& nums, int idx, int prevIdx) {
            if(idx >= nums.size()) return 0; // out of bound
    
            if(prevIdx != -1 && dp[idx][prevIdx]) return dp[idx][prevIdx]; // already calculated
    
            int take = 0;
            if(prevIdx == -1 || nums[prevIdx] < nums[idx]) take = 1 + solve(nums, idx + 1, idx);
            int skip = solve(nums, idx + 1, prevIdx);
    
            if(prevIdx != -1) return dp[idx][prevIdx] = max(take, skip); // save ans in dp
            return max(take, skip);
        }
    
    public:
        int lengthOfLIS(vector<int>& nums) {
            return solve(nums, 0, -1);
        }
    };

/*
LeetCode 300. Longest Increasing Subsequence

Approach:
---------

We need to find the length of the longest subsequence such that
the elements are in strictly increasing order.

A subsequence does NOT need to be contiguous.

For example:

    nums = [10, 9, 2, 5, 3, 7, 101, 18]

One possible LIS is:

    [2, 3, 7, 101]

so the answer is:

    4

The main idea is to process the array from left to right.

At every index, we have two choices:

    1. Take nums[idx] into the increasing subsequence
    2. Skip nums[idx]

If we take nums[idx], it must be greater than the previously
selected element.

------------------------------------------------------------

State Definition:
-----------------

The recursive function is:

    solve(nums, idx, prevIdx)

Here:

    idx
        = current index we are deciding whether to take or skip.

    prevIdx
        = index of the previous element that we selected in
          our increasing subsequence.

So the state:

    solve(idx, prevIdx)

means:

    "What is the maximum LIS length we can build from idx
     onward, assuming nums[prevIdx] was the last element
     already selected?"

------------------------------------------------------------

Why Do We Need prevIdx?
------------------------

To decide whether we can take nums[idx], we need to know the
previous selected value.

For an increasing subsequence:

    previous value < current value

So we check:

    nums[prevIdx] < nums[idx]

For example:

    nums = [2, 5, 3]

If we previously selected:

    2

and currently have:

    5

then:

    2 < 5

so we can take 5.

But if the previous value was:

    5

and current value is:

    3

then:

    5 < 3

is false, so we cannot take 3.

------------------------------------------------------------

Why Can prevIdx Be -1?
-----------------------

At the beginning:

    solve(nums, 0, -1)

There is no previously selected element yet.

So:

    prevIdx = -1

represents:

    "We have not selected anything yet."

That means at the beginning, we are free to take nums[0].

This is why the condition is:

    if(prevIdx == -1 || nums[prevIdx] < nums[idx])

If there is no previous element, we can always take the
current element.

------------------------------------------------------------

Base Case:
----------

    if(idx >= nums.size()) return 0;

If idx reaches the end of the array, there are no more elements
to consider.

Therefore, the maximum additional length is:

    0

------------------------------------------------------------

Two Choices:
------------

At every index we consider:

    take
    skip

------------------------------------------------------------

1. Take nums[idx]
------------------

    int take = 0;

We can take the current element only if:

    prevIdx == -1

OR:

    nums[prevIdx] < nums[idx]

If we take it:

    take = 1 + solve(nums, idx + 1, idx);

Why:

    +1

Because nums[idx] becomes part of our subsequence.

And:

    idx

becomes the new prevIdx because the current element is now the
last selected element.

For example:

    previous selected = 3
    current = 7

If we take 7:

    [3, 7]

Now 7 is the previous selected element for future choices.

Therefore:

    prevIdx = idx

------------------------------------------------------------

2. Skip nums[idx]
------------------

    int skip = solve(nums, idx + 1, prevIdx);

If we skip the current element, the previously selected element
does not change.

So:

    idx -> idx + 1

but:

    prevIdx stays the same.

For example:

    previous selected = 3
    current = 2

We cannot take 2, so we simply move forward:

    solve(idx + 1, prevIdx)

------------------------------------------------------------

Choose the Better Option:
--------------------------

After calculating both possibilities:

    take
    skip

we want the longer subsequence:

    max(take, skip)

Therefore:

    return max(take, skip);

------------------------------------------------------------

Memoization:
------------

The same state can be reached through different choices.

For example, we may reach:

    solve(idx = 5, prevIdx = 2)

through different combinations of elements selected before
index 5.

But once we know the answer for this exact state, we don't need
to calculate it again.

So we store:

    dp[idx][prevIdx]

This is memoization.

------------------------------------------------------------

Why Is prevIdx == -1 Not Stored?
---------------------------------

Your DP array is:

    int dp[2500][2500];

But -1 cannot be used as an array index.

Therefore, your code only stores states where:

    prevIdx != -1

using:

    if(prevIdx != -1)
        return dp[idx][prevIdx] = max(take, skip);

The initial state:

    solve(nums, 0, -1)

is calculated directly and is not stored.

This is fine because there is only one initial state with
prevIdx == -1.

------------------------------------------------------------

Important Detail About This Check:
-----------------------------------

Your code has:

    if(prevIdx != -1 && dp[idx][prevIdx])
        return dp[idx][prevIdx];

This works because LIS length is always at least 1 for a valid
state that has a previous selected element, so a stored value of
0 effectively means "not calculated yet."

However, conceptually, it is more common to initialize the DP
array to -1 and check:

    if(dp[idx][prevIdx] != -1)

because:

    -1 = not calculated
     0 = a valid calculated answer

For this problem, your current approach can still work because
the stored LIS result is never 0 for these states.

------------------------------------------------------------

Example:
--------

nums = [10, 9, 2, 5, 3, 7, 101, 18]

Start:

    solve(0, -1)

At index 0:

    nums[0] = 10

Since there is no previous element, we have two choices:

    Take 10
    Skip 10

The recursion explores both possibilities and keeps the better
one.

Eventually, one optimal path is:

    2 -> 3 -> 7 -> 101

giving:

    4

------------------------------------------------------------

Understanding One Recursive State:
-----------------------------------

Suppose we are at:

    idx = 5
    prevIdx = 2

For:

    nums = [10, 9, 2, 5, 3, 7, ...]

we have:

    nums[prevIdx] = nums[2] = 2
    nums[idx]     = nums[5] = 7

Since:

    2 < 7

we can take 7.

So:

    take = 1 + solve(nums, 6, 5)

where index 5 becomes the new previous index.

Or we can skip 7:

    skip = solve(nums, 6, 2)

Then:

    dp[5][2] = max(take, skip)

------------------------------------------------------------

Why This Is 2D DP:
------------------

The answer depends on TWO changing pieces of information:

    1. Current position: idx
    2. Previous selected element: prevIdx

Therefore, the state is:

    dp[idx][prevIdx]

This is why the solution uses a 2D DP table.

A useful way to think about it:

    dp[idx][prevIdx]

    = maximum LIS we can create from idx onward
      when prevIdx is the previously selected index.

------------------------------------------------------------

Top-Down DP:
------------

This solution uses:

    Recursion + Memoization

which is called Top-Down Dynamic Programming.

We start with:

    solve(nums, 0, -1)

and recursively break the problem into smaller states:

    solve(idx + 1, idx)
    solve(idx + 1, prevIdx)

Whenever a state is solved, its answer is stored in dp.

If we encounter the same state again, we directly return the
stored result.

------------------------------------------------------------

Why We Don't Need to Track the Whole Subsequence:
---------------------------------------------------

We only need the LENGTH of the LIS.

We don't actually need to store:

    [2, 3, 7, 101]

during the recursion.

To determine whether we can take the next number, we only need
to know:

    the index of the previously selected number.

Therefore:

    prevIdx

is enough information to make the next decision.

------------------------------------------------------------

Subsequence vs Subarray:
------------------------

This is important for LeetCode 300.

A subsequence does not have to be contiguous.

For example:

    [2, 5, 3, 7]

can give the subsequence:

    [2, 3, 7]

even though 2, 3, and 7 are not adjacent in the original array.

Our Skip choice is what allows us to ignore elements in between.

------------------------------------------------------------

Overall Flow:
-------------

Start:

    solve(0, -1)

             |
             ↓
       Current index
             |
       +-----+-----+
       |           |
      TAKE        SKIP
       |           |
   valid?      move to idx+1
       |
       ↓
  1 + solve(idx+1, idx)

             ↓
       max(take, skip)

             ↓
        store in dp

------------------------------------------------------------

Complexity:
-----------

There are approximately:

    n * n

possible combinations of:

    idx
    prevIdx

Each state is calculated only once because of memoization.

Therefore:

    Time Complexity: O(n²)

The 2D DP table contains:

    O(n²)

states.

So:

    Space Complexity: O(n²)

Additionally, the recursion stack can go up to O(n), but the
dominant extra space is the O(n²) DP table.

For n = 2500, a full int[2500][2500] table is also quite large
(~25 MB), but it fits within typical constraints for this
problem depending on the platform's memory limit.

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This is a classic

    Take / Skip + Memoization

problem.

At every index:

                nums[idx]
                /       \
             TAKE       SKIP
              |           |
       if increasing      ignore
              |
              ↓
    1 + solve(idx+1, idx)

The state is:

    solve(idx, prevIdx)

because we need both:

    current position
    previous selected element

The recurrence is:

    dp[idx][prevIdx] =
        max(
            1 + dp[idx+1][idx],      // take
            dp[idx+1][prevIdx]      // skip
        )

when nums[prevIdx] < nums[idx].

This is the main idea behind your recursive DP solution for
LeetCode 300.
*/