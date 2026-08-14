class Solution {
    private:
        int N, M, K;
        int MOD = 1e9 + 7;
    
        int dp[51][51][101]; // dp[idx][searchCost][maxSoFar]
    
        int solve(int idx, int searchCost, int maxSoFar) {
            if(idx == N) { // if idx reaches end
                if(searchCost == K) return 1; // if searchCost is equal to desired
                return 0;
            }
    
            if(dp[idx][searchCost][maxSoFar] != -1) return dp[idx][searchCost][maxSoFar];
    
            int result = 0;
    
            for(int i = 1; i <= M; i++) {
                if (i > maxSoFar) result = (result + solve(idx + 1, searchCost + 1, i)) % MOD; // if number is greater, increase searchCost
                else result = (result + solve(idx + 1, searchCost, maxSoFar)) % MOD;
            }
    
            return dp[idx][searchCost][maxSoFar] = result % MOD;
        }
    
    public:
        int numOfArrays(int n, int m, int k) {
            // use global variable so we dont need to pass them again and again
            N = n;
            M = m;
            K = k;
    
            memset(dp, -1, sizeof(dp));
    
            return solve(0, 0, 0); // solve(idx, searchCost, maxSoFar);
        }
    };

/*
LeetCode 1420. Build Array Where You Can Find The Maximum Exactly K Comparisons

Approach:
---------

We need to build an array of length N where:

    1 <= nums[i] <= M

While scanning the array from left to right, we keep track of
the maximum value seen so far.

Whenever we encounter a number greater than the current maximum,
the maximum changes and the "search cost" increases by 1.

We need to count how many arrays have exactly:

    K search cost

The answer can be very large, so we return it modulo:

    1e9 + 7

This solution uses:

    Recursion + 3D Memoization

------------------------------------------------------------

What Is Search Cost?
--------------------

Suppose:

    nums = [2, 1, 4, 3]

Scan from left to right:

    2 -> new maximum       cost = 1
    1 -> not greater       cost = 1
    4 -> new maximum       cost = 2
    3 -> not greater       cost = 2

So the search cost is:

    2

Another example:

    [1, 2, 3]

Every new number is larger than the previous maximum:

    1 -> cost 1
    2 -> cost 2
    3 -> cost 3

So:

    searchCost = 3

------------------------------------------------------------

DP State:
----------

The recursive function is:

    solve(idx, searchCost, maxSoFar)

There are THREE things we need to know:

    idx
        = current position where we need to place a number

    searchCost
        = number of times we have found a new maximum so far

    maxSoFar
        = maximum value in the array up to idx - 1

Therefore:

    dp[idx][searchCost][maxSoFar]

stores:

    "Number of valid ways to fill the array from idx onward,
     given that the current search cost is searchCost and the
     maximum value seen so far is maxSoFar."

This is why we need a 3D DP array.

------------------------------------------------------------

Why maxSoFar Is Needed:
-----------------------

Suppose the current maximum is:

    maxSoFar = 5

and we want to choose:

    i = 3

Since:

    3 <= 5

the maximum does not change.

So:

    searchCost stays the same

But if we choose:

    i = 7

then:

    7 > 5

so 7 becomes the new maximum and:

    searchCost increases by 1

Therefore, we must know the current maximum to decide whether
the search cost changes.

------------------------------------------------------------

Starting State:
---------------

    return solve(0, 0, 0);

Initially:

    idx = 0

We haven't placed any elements yet.

Therefore:

    searchCost = 0

And there is no maximum yet, so we use:

    maxSoFar = 0

Since all values we can place are between:

    1 and M

0 works as the initial "no maximum" value.

------------------------------------------------------------

Base Case:
----------

    if(idx == N) {

We have filled all N positions.

At this point, we only want arrays whose search cost is exactly K:

    if(searchCost == K) return 1;

If the search cost is not K:

    return 0;

So:

    1 = this construction is a valid array
    0 = this construction does not satisfy the required cost

This is how the recursion counts valid arrays.

------------------------------------------------------------

Memoization:
------------

Before doing any work, we check:

    if(dp[idx][searchCost][maxSoFar] != -1)
        return dp[idx][searchCost][maxSoFar];

If this state was already calculated, we return the stored
answer immediately.

Without memoization, the recursion would try a huge number of
possible arrays.

With memoization, every unique:

    (idx, searchCost, maxSoFar)

state is calculated only once.

------------------------------------------------------------

Trying Every Possible Number:
------------------------------

At every position, the value can be any number from:

    1 to M

So:

    for(int i = 1; i <= M; i++)

tries every possible value for the current position.

For every choice, there are two cases.

------------------------------------------------------------

Case 1: New Maximum
-------------------

    if(i > maxSoFar)

If the number we are placing is greater than the current
maximum, then we have found a new maximum.

For example:

    maxSoFar = 4
    i = 7

Since:

    7 > 4

the new maximum becomes:

    7

and search cost increases:

    searchCost + 1

So we call:

    solve(
        idx + 1,
        searchCost + 1,
        i
    );

Notice that:

    i

becomes the new maxSoFar.

------------------------------------------------------------

Case 2: Not a New Maximum
--------------------------

Otherwise:

    i <= maxSoFar

The maximum does not change.

Therefore:

    searchCost stays the same

and:

    maxSoFar stays the same

So we call:

    solve(
        idx + 1,
        searchCost,
        maxSoFar
    );

For example:

    maxSoFar = 7
    i = 3

Since:

    3 <= 7

there is no new maximum.

------------------------------------------------------------

Why Do We Add the Results?
---------------------------

For every possible value i, the recursive call represents all
valid arrays that can be created after choosing i at the current
position.

So we add the number of ways from every choice:

    result = result + recursiveResult

This gives the total number of valid arrays for the current
state.

------------------------------------------------------------

Why Take Modulo?
----------------

The number of possible arrays can be extremely large.

Since each position has M possible values, there can be:

    M^N

different arrays.

So we take modulo:

    1e9 + 7

while adding:

    result =
        (result + recursiveResult) % MOD;

This prevents the number from becoming too large and follows
the problem's requirement.

------------------------------------------------------------

Example:
--------

Suppose:

    N = 2
    M = 3
    K = 2

We need arrays of length 2 using values:

    1, 2, 3

with exactly 2 new maximums.

Start:

    solve(0, 0, 0)

At index 0, choose any number.

Suppose we choose:

    1

Since:

    1 > 0

search cost becomes:

    1

and maximum becomes:

    1

State:

    solve(1, 1, 1)

At index 1:

    Choose 1:
        1 <= 1
        cost remains 1

    Choose 2:
        2 > 1
        cost becomes 2

    Choose 3:
        3 > 1
        cost becomes 2

Therefore:

    [1,2]
    [1,3]

have search cost 2.

Similarly:

    [2,3]

also has search cost 2.

So the answer is:

    3

------------------------------------------------------------

Understanding the Search Cost:
------------------------------

The search cost is NOT:

    number of comparisons

It is the number of times a new maximum is discovered.

For example:

    [3, 1, 2, 5, 4]

Scan:

    3 -> new max      cost = 1
    1 -> no change    cost = 1
    2 -> no change    cost = 1
    5 -> new max      cost = 2
    4 -> no change    cost = 2

Final:

    searchCost = 2

This is exactly what the DP is tracking.

------------------------------------------------------------

Why maxSoFar Is Updated to i:
-----------------------------

In the new maximum case:

    if(i > maxSoFar)

we call:

    solve(idx + 1, searchCost + 1, i)

We use:

    i

instead of:

    max(maxSoFar, i)

because we already know:

    i > maxSoFar

Therefore:

    i

is definitely the new maximum.

------------------------------------------------------------

Why This Is 3D DP:
------------------

The future possibilities depend on three variables:

    1. idx
       Which position are we filling?

    2. searchCost
       How many maximum changes have happened so far?

    3. maxSoFar
       What is the current maximum?

So the state is:

    dp[idx][searchCost][maxSoFar]

and the transition depends on the number we choose:

    i = 1 ... M

------------------------------------------------------------

Important Observation:
-----------------------

The actual values chosen before idx do NOT matter individually.

We only need their:

    maximum value

and:

    current search cost

This is why we don't store the entire prefix of the array in
the DP state.

For example, these two prefixes:

    [2, 1, 2]

and:

    [2, 2, 1]

both have:

    maxSoFar = 2
    searchCost = 1

If they are at the same idx, the number of ways to complete the
array from there is the same.

Therefore, they can share the same DP state.

This is the key reason memoization works.

------------------------------------------------------------

Overall Flow:
-------------

                solve(idx, cost, max)
                         |
              choose i = 1 ... M
                         |
                 +-------+-------+
                 |               |
             i > max          i <= max
                 |               |
           new maximum        no change
                 |               |
             cost + 1          same cost
             max = i            same max
                 |               |
                 +-------+-------+
                         |
                         ↓
                    idx + 1
                         |
                         ↓
                  memoize result

------------------------------------------------------------

Why the Base Case Checks K:
----------------------------

We don't return 1 simply because we reached the end.

We return 1 only when:

    searchCost == K

because the problem asks for arrays with EXACTLY K maximum
changes.

For example, if:

    K = 3

then an array with:

    searchCost = 2

is invalid.

Likewise:

    searchCost = 4

is also invalid.

Only:

    searchCost = 3

contributes to the answer.

------------------------------------------------------------

Complexity:
-----------

There are three DP dimensions:

    idx        -> N
    searchCost -> K
    maxSoFar   -> M

So the number of DP states is:

    O(N * K * M)

For every state, we try every possible number:

    1 ... M

Therefore:

    Time Complexity: O(N * K * M²)

With the given constraints, this is the intended complexity for
this straightforward memoized solution.

The DP array stores:

    O(N * K * M)

states.

Therefore:

    Space Complexity: O(N * K * M)

There is also O(N) recursion stack space.

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This problem is a good example of identifying exactly what
information from the past affects the future.

We do NOT need to remember the entire array prefix.

We only need:

    current index
    current search cost
    current maximum

So:

    solve(idx, searchCost, maxSoFar)

At every position:

    Try every value from 1 to M.

    If value > maxSoFar:
        new maximum
        searchCost + 1
        maxSoFar = value

    Otherwise:
        searchCost unchanged
        maxSoFar unchanged

At the end:

    searchCost == K -> 1
    otherwise       -> 0

And memoize:

    dp[idx][searchCost][maxSoFar]

The key idea to remember is:

    "The future only depends on the position, how many
     maximum changes we have used, and the current maximum."

*/