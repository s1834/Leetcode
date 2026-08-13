class Solution {
    private:
        int dp[1000][1000];
    
        int solve(vector<vector<int>>& pairs, int idx, int prevIdx) {
            if(idx >= pairs.size()) return 0; // out of bound
    
            if(prevIdx != -1 && dp[idx][prevIdx] != -1) return dp[idx][prevIdx]; // already calculated
    
            int take = 0;
            if(prevIdx == -1 || pairs[prevIdx][1] < pairs[idx][0]) take = 1 + solve(pairs, idx + 1, idx);
            int skip = solve(pairs, idx + 1, prevIdx);
    
            if(prevIdx != -1) return dp[idx][prevIdx] = max(take, skip); // save ans in dp
            return max(take, skip);
        }
    
    public:
        int findLongestChain(vector<vector<int>>& pairs) {
            memset(dp, -1, sizeof(dp));
            sort(pairs.begin(), pairs.end());
            return solve(pairs, 0, -1);
        }
    };

/*
LeetCode 646. Maximum Length of Pair Chain

Approach:
---------

We are given pairs:

    [a, b]

and one pair can come after another if:

    previous.second < current.first

For example:

    [1,2] -> [3,4]

is valid because:

    2 < 3

But:

    [1,3] -> [3,4]

is NOT valid because:

    3 < 3   // false

We want to find the maximum number of pairs that can be
chained together.

This solution uses:

    Sorting + Top-Down DP (Take / Skip)

------------------------------------------------------------

Why Sort the Pairs?
-------------------

    sort(pairs.begin(), pairs.end());

This sorts the pairs lexicographically:

    first element
    then second element if the first elements are equal

For example:

    [[3,4], [1,2], [2,3]]

becomes:

    [[1,2], [2,3], [3,4]]

Sorting gives us a fixed left-to-right order in which we can
make our Take / Skip decisions.

After sorting, when we are at index idx, we only need to
consider pairs appearing after it.

------------------------------------------------------------

Recursive State:
----------------

    solve(pairs, idx, prevIdx)

There are two important pieces of information:

    idx
        = current pair we are deciding whether to take

    prevIdx
        = index of the last pair that we selected

So:

    solve(idx, prevIdx)

means:

    "What is the maximum chain length we can build from idx
     onward, assuming pairs[prevIdx] is the last pair already
     selected?"

------------------------------------------------------------

Why Do We Need prevIdx?
------------------------

To determine whether the current pair can be added to the
chain, we need to compare:

    previous pair's ending value

with:

    current pair's starting value

The condition is:

    pairs[prevIdx][1] < pairs[idx][0]

For example:

    previous = [1,2]
    current  = [4,5]

We check:

    2 < 4

which is true, so we can take [4,5].

------------------------------------------------------------

Why prevIdx = -1?
------------------

Initially:

    solve(pairs, 0, -1)

There is no previous pair because we haven't selected anything
yet.

So:

    prevIdx = -1

means:

    "No pair has been selected yet."

Therefore, the first pair can always be considered for taking.

This is why the condition is:

    if(prevIdx == -1 ||
       pairs[prevIdx][1] < pairs[idx][0])

------------------------------------------------------------

Base Case:
----------

    if(idx >= pairs.size()) return 0;

If idx reaches the end of the array, there are no more pairs
to consider.

So the maximum additional chain length is:

    0

------------------------------------------------------------

Take Choice:
------------

    int take = 0;

We can take the current pair only when it can follow the
previous pair.

The condition is:

    prevIdx == -1 ||
    pairs[prevIdx][1] < pairs[idx][0]

If the condition is satisfied:

    take = 1 + solve(pairs, idx + 1, idx);

Why +1?

Because we are adding:

    pairs[idx]

to the chain.

After taking it, the current pair becomes the new previous
pair:

    prevIdx = idx

So the next state becomes:

    solve(idx + 1, idx)

------------------------------------------------------------

Skip Choice:
------------

    int skip = solve(pairs, idx + 1, prevIdx);

We can always skip the current pair.

If we skip it:

    idx

moves forward to:

    idx + 1

but the previous selected pair does not change.

Therefore:

    prevIdx

remains the same.

------------------------------------------------------------

Choose the Better Choice:
--------------------------

    max(take, skip)

We want the longest possible chain.

So:

    dp[idx][prevIdx] =
        max(take, skip)

This is the classic:

    Take / Skip

DP pattern.

------------------------------------------------------------

Memoization:
------------

Many different recursive paths can reach the same state:

    solve(idx, prevIdx)

Once we calculate that state, we store its result:

    dp[idx][prevIdx]

At the beginning:

    memset(dp, -1, sizeof(dp));

So:

    -1

means:

    "This state has not been calculated yet."

Then:

    if(prevIdx != -1 && dp[idx][prevIdx] != -1)
        return dp[idx][prevIdx];

If the value is already present, we return it immediately
instead of solving the same state again.

------------------------------------------------------------

Why Don't We Store prevIdx == -1?
----------------------------------

The DP table is indexed using:

    dp[idx][prevIdx]

But:

    prevIdx = -1

cannot be used as an array index.

Therefore, your code handles the initial state separately:

    if(prevIdx != -1)
        return dp[idx][prevIdx] = max(take, skip);

If:

    prevIdx == -1

we simply return:

    max(take, skip)

without storing it.

This is fine because the initial state:

    solve(0, -1)

is only called once.

------------------------------------------------------------

Example:
--------

pairs =

    [[1,2],
     [2,3],
     [3,4],
     [5,6]]

Start:

    solve(0, -1)

At [1,2]:

We can take it because there is no previous pair.

    take = 1 + solve(1, 0)

Or skip it:

    skip = solve(1, -1)

The recursion explores both possibilities.

Suppose we take:

    [1,2]

Then at:

    [2,3]

we check:

    2 < 2

which is false.

So [2,3] cannot follow [1,2].

We can skip it.

Next:

    [3,4]

Now:

    2 < 3

so [3,4] can follow [1,2].

Then:

    [5,6]

can follow [3,4]:

    4 < 5

So one valid chain is:

    [1,2] -> [3,4] -> [5,6]

Length:

    3

------------------------------------------------------------

Why Is the Condition Strictly < ?
----------------------------------

The problem requires:

    pairs[i][1] < pairs[j][0]

not:

    pairs[i][1] <= pairs[j][0]

So:

    [1,2] -> [3,4]

is valid:

    2 < 3

but:

    [1,2] -> [2,4]

is invalid:

    2 < 2   // false

This strict inequality is important.

------------------------------------------------------------

Connection to LeetCode 300:
----------------------------

This solution is very similar to your LIS solution.

For LIS:

    if(nums[prevIdx] < nums[idx])

we can take nums[idx].

Here:

    if(pairs[prevIdx][1] < pairs[idx][0])

we can take pairs[idx].

The DP structure is almost identical:

    solve(idx, prevIdx)

        |
        +------ TAKE
        |
        +------ SKIP

The only difference is the condition for whether the current
element can be taken.

------------------------------------------------------------

Why Sorting Helps:
------------------

After sorting, we process pairs from left to right.

For example:

    [1,2]
    [2,3]
    [3,4]
    [5,6]

When we are processing [3,4], all candidates considered after
it are at larger indices.

This lets the recursion move only in one direction:

    idx -> idx + 1

and therefore every possible chain can be represented by
Take / Skip decisions over the sorted array.

------------------------------------------------------------

DP State Interpretation:
------------------------

The most important thing to remember is:

    dp[idx][prevIdx]

means:

    maximum chain length we can form from pair idx onward,
    when prevIdx is the last pair already selected.

For example:

    dp[5][2]

means:

    "Starting from pair 5, what is the longest chain I can
     make if pair 2 is currently the last selected pair?"

The answer depends on whether pair 5 can follow pair 2.

------------------------------------------------------------

Overall Flow:
-------------

        Sort pairs
            |
            ↓
    solve(0, -1)
            |
            ↓
       Current pair
            |
       +----+----+
       |         |
     TAKE      SKIP
       |         |
   valid?     idx + 1
       |
       ↓
1 + solve(idx+1, idx)
       |
       +---------+
             |
             ↓
        max(take, skip)
             |
             ↓
       store in dp

------------------------------------------------------------

Why This Is Top-Down DP:
------------------------

The solution starts with:

    solve(0, -1)

and recursively breaks the problem into smaller states.

Whenever a state is calculated, it is stored in:

    dp[idx][prevIdx]

So this is:

    Recursion + Memoization

which is called:

    Top-Down Dynamic Programming.

------------------------------------------------------------

Complexity:
-----------

There are two changing indices:

    idx
    prevIdx

So there are approximately:

    O(n²)

possible DP states.

Each state does only O(1) work apart from recursive calls.

Therefore:

    Time Complexity: O(n²)

Sorting additionally takes:

    O(n log n)

which is smaller than O(n²).

So the overall complexity is:

    O(n²)

Space:

    dp[1000][1000]

stores O(n²) states.

The recursion stack can be O(n), but the DP table dominates.

Therefore:

    Space Complexity: O(n²)

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This problem is another example of:

    Sort + Take / Skip DP

The state is:

    solve(idx, prevIdx)

At every pair:

    TAKE:
        if previous.end < current.start

        1 + solve(idx + 1, idx)

    SKIP:
        solve(idx + 1, prevIdx)

Then:

    dp[idx][prevIdx] = max(take, skip)

The main thing to recognize is that the current decision
depends on the previously selected pair, which is why
prevIdx is part of the DP state.

*/