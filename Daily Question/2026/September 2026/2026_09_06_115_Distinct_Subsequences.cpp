class Solution {
    private:
        vector<vector<int>> dp;
    
        int solve(string& s, string& t, int i, int j) {
            if(j == t.size()) return 1; // t is finished
            if(i == s.size()) return 0; // s is finished, t is not
    
            if(dp[i][j] != -1) return dp[i][j];
    
            if(s[i] == t[j]) return dp[i][j] = solve(s, t, i + 1, j + 1) + solve(s, t, i + 1, j);
    
            return dp[i][j] = solve(s, t, i + 1, j);
        }
    
    public:
        int numDistinct(string s, string t) {
            dp.assign(s.size(), vector<int>(t.size(), -1));
            return solve(s, t, 0, 0);
        }
    };

/*
LeetCode 115. Distinct Subsequences

Approach:
---------

We need to find how many distinct subsequences of string s are
equal to string t.

A subsequence is created by deleting zero or more characters from
s while keeping the remaining characters in the same order.

For example:

    s = "rabbbit"
    t = "rabbit"

There are multiple ways to delete one of the extra 'b's from s
and obtain t.

We use:

    Recursion + Memoization (Top-Down DP)

At every position, if the current characters match, we have two
choices:

    1. Use s[i] as t[j].
    2. Skip s[i] and try to match t[j] with a later character.

If the characters do not match, we have only one choice:

    Skip s[i].

------------------------------------------------------------

DP State:
---------

    dp[i][j]

represents the number of distinct ways to form:

    t[j ... end]

using characters from:

    s[i ... end]

In other words:

    dp[i][j] =
        number of subsequences of s[i...] that equal t[j...]

This state is identified by two positions:

    i -> current position in s
    j -> current position in t

------------------------------------------------------------

Why Do We Need Two Indices?
----------------------------

We need to know:

    1. Which character of s we are currently considering.
    2. Which character of t we are currently trying to match.

For example:

    s = "babgbag"
    t = "bag"

If:

    i = 2
    j = 1

then we are considering:

    s[2 ... end]

and trying to construct:

    t[1 ... end]

So the recursive problem becomes completely defined by:

    (i, j)

This is why memoization uses:

    dp[i][j]

------------------------------------------------------------

Base Case 1: t Is Finished
--------------------------

    if(j == t.size()) return 1;

If j reaches the end of t, we have successfully matched the
entire target string.

There is exactly ONE successful way to finish:

    choose nothing more.

For example:

    t = "abc"

Once we have successfully matched:

    a -> b -> c

the target is complete.

Therefore:

    return 1;

The important point is that this means:

    "A valid subsequence has been formed."

It does NOT mean there is only one way to reach this state.
Different recursive paths can reach this state, and each one is
counted separately by the recursion.

------------------------------------------------------------

Base Case 2: s Is Finished
--------------------------

    if(i == s.size()) return 0;

If we have reached the end of s but t is still not finished,
there are no characters left that can be used to construct t.

Therefore:

    return 0;

For example:

    s = "ab"
    t = "abc"

After consuming all characters of s, we still need:

    "c"

which is impossible.

So this branch contributes:

    0

------------------------------------------------------------

Memoization:
------------

    if(dp[i][j] != -1)
        return dp[i][j];

The same state can be reached through many different choices.

Without memoization, the recursion would repeatedly solve the
same subproblem.

Once:

    dp[i][j]

has been calculated, we store its result and reuse it whenever
the same state appears again.

This converts the recursion from exponential repeated work into
a DP solution with O(n * m) states.

------------------------------------------------------------

Case 1: Characters Match
------------------------

    if(s[i] == t[j])

When:

    s[i] == t[j]

the current character of s can potentially be used to match the
current character of t.

But we have TWO choices.

------------------------------------------------------------

Choice 1: Use s[i]
------------------

We can use the current character to match t[j].

So both strings move forward:

    i + 1
    j + 1

This gives:

    solve(s, t, i + 1, j + 1)

For example:

    s = "abc"
    t = "ac"

At:

    i = 0 -> 'a'
    j = 0 -> 'a'

We can use this 'a'.

Now we need to match:

    "bc"

with:

    "c"

So we move to:

    solve(1, 1)

------------------------------------------------------------

Choice 2: Skip s[i]
-------------------

Even though:

    s[i] == t[j]

we are NOT forced to use it.

We can skip this occurrence of the character and try to match
t[j] using a later character in s.

Therefore:

    solve(s, t, i + 1, j)

For example:

    s = "aaa"
    t = "aa"

At the first 'a', we could:

    use it

or:

    skip it

Both choices can lead to different subsequences.

------------------------------------------------------------

Therefore:
-----------

When:

    s[i] == t[j]

the total number of ways is:

    solve(i + 1, j + 1)
    +
    solve(i + 1, j)

So the code does:

    dp[i][j] =
        solve(s, t, i + 1, j + 1)
        +
        solve(s, t, i + 1, j);

This is the most important recurrence in the solution.

------------------------------------------------------------

Why Do We ADD the Two Choices?
------------------------------

The two branches represent different decisions:

    Branch 1:
        Use s[i]

    Branch 2:
        Do not use s[i]

Every valid subsequence belongs to exactly one of these two
categories.

Therefore, the number of valid subsequences is:

    ways using s[i]
    +
    ways skipping s[i]

Hence:

    dp[i][j] = use + skip

------------------------------------------------------------

Case 2: Characters Do Not Match
--------------------------------

If:

    s[i] != t[j]

then s[i] cannot be used to match t[j].

Therefore, there is only one possible decision:

    Skip s[i].

So:

    dp[i][j] = solve(s, t, i + 1, j);

Notice that j does NOT change.

Why?

Because we have not matched t[j] yet.

We simply move to the next character in s and continue trying
to find t[j].

------------------------------------------------------------

Example:
--------

    s = "babgbag"
    t = "bag"

Initially:

    solve(0, 0)

We need to form:

    "bag"

from:

    "babgbag"

At every character we decide whether to:

    take it
    or
    skip it

For example, the first 'b' can be used to match the first 'b':

    b
    ↓
    a
    ↓
    g

But we can also skip that 'b' and use a later 'b'.

This is why multiple distinct subsequences can produce the same
target string.

------------------------------------------------------------

Visualizing the Recursion:
--------------------------

When characters match:

                solve(i, j)
                    |
              s[i] == t[j]
                    |
           +--------+--------+
           |                 |
         TAKE              SKIP
           |                 |
     solve(i+1,j+1)     solve(i+1,j)
           |                 |
           ↓                 ↓
      match both         match t[j]
      characters         later in s

When characters do not match:

                solve(i, j)
                    |
              s[i] != t[j]
                    |
                  SKIP
                    |
             solve(i+1, j)

------------------------------------------------------------

Example With Duplicates:
------------------------

Consider:

    s = "aaa"
    t = "aa"

There are 3 distinct ways to select two 'a's:

    positions (0, 1)
    positions (0, 2)
    positions (1, 2)

The recursion counts these separately.

At the first 'a':

    TAKE
        -> use position 0
        -> now choose one more 'a'

    SKIP
        -> ignore position 0
        -> choose both from positions 1 and 2

This is exactly why the TAKE + SKIP recurrence works.

------------------------------------------------------------

Why "Distinct Subsequences" Does Not Mean Unique Strings?
--------------------------------------------------------------

Here, "distinct subsequences" refers to different ways of
selecting positions from s that produce t.

For example:

    s = "aaa"
    t = "aa"

Even though every resulting string is visually:

    "aa"

there are 3 different selections of positions.

The problem asks us to count these valid selections.

------------------------------------------------------------

Initialization:
---------------

    dp.assign(s.size(), vector<int>(t.size(), -1));

We create a DP table where:

    rows    -> positions in s
    columns -> positions in t

Every state initially contains:

    -1

which means:

    "This state has not been calculated yet."

When solve(i, j) calculates a result, it stores it in:

    dp[i][j]

------------------------------------------------------------

Why the DP Table Is n x m:
--------------------------

The recursive states are:

    i = 0 ... n - 1
    j = 0 ... m - 1

So we store:

    n * m

actual recursive states.

The base cases:

    i == n
    j == m

are handled directly before accessing dp[i][j], so they do not
need to be stored in the table.

------------------------------------------------------------

Complete Algorithm:
-------------------

    1. Create a memoization table dp initialized to -1.

    2. Start recursion from:

           solve(s, t, 0, 0)

    3. If t is completely matched:

           return 1

    4. If s is exhausted before t:

           return 0

    5. If dp[i][j] is already calculated:

           return dp[i][j]

    6. If:

           s[i] == t[j]

       try both:

           TAKE:
               solve(i + 1, j + 1)

           SKIP:
               solve(i + 1, j)

       and add their results.

    7. Otherwise:

           s[i] != t[j]

       skip s[i]:

           solve(i + 1, j)

    8. Store the result in dp[i][j].

------------------------------------------------------------

Core Recurrence:
----------------

If:

    s[i] == t[j]

then:

    dp[i][j] =
        dp[i + 1][j + 1]
        +
        dp[i + 1][j]

Meaning:

    use current character
              +
    skip current character


If:

    s[i] != t[j]

then:

    dp[i][j] =
        dp[i + 1][j]

because the current character cannot match t[j].

------------------------------------------------------------

Correctness Intuition:
----------------------

At every position i in s, we consider every possible way that
s[i] can participate in constructing t.

If:

    s[i] == t[j]

every valid subsequence either:

    1. Uses s[i] to match t[j], or
    2. Does not use s[i].

These two possibilities cover every valid subsequence exactly
once.

If:

    s[i] != t[j]

then using s[i] for t[j] is impossible, so every valid solution
must skip s[i].

The recursion continues until either:

    t is completely matched -> valid solution -> 1

or:

    s is exhausted first -> impossible -> 0

Therefore, summing the choices gives exactly the number of
distinct subsequences of s that equal t.

Memoization only avoids recalculating the same states; it does
not change the result.

------------------------------------------------------------

Time Complexity:
----------------

There are:

    n * m

possible states:

    dp[i][j]

Each state performs only O(1) work apart from its recursive
calls.

Therefore:

    Time Complexity = O(n * m)

where:

    n = s.size()
    m = t.size()

------------------------------------------------------------

Space Complexity:
-----------------

The DP table contains:

    n * m

states.

Therefore:

    DP Space = O(n * m)

The recursion depth can be at most:

    O(n)

So total auxiliary space is:

    O(n * m) + O(n)

which is:

    O(n * m)

------------------------------------------------------------

Main Idea to Remember:
----------------------

This is a classic:

    TAKE / SKIP DP

problem.

At every character of s:

    If s[i] == t[j]:

        TAKE it:
            solve(i + 1, j + 1)

        OR

        SKIP it:
            solve(i + 1, j)

        Total:
            TAKE + SKIP

    If s[i] != t[j]:

        SKIP:
            solve(i + 1, j)

The base cases are:

    t finished
        -> 1

    s finished while t remains
        -> 0

So the entire solution can be remembered as:

        Match?
        /    \
      TAKE  SKIP
       |      |
    i+1,j+1  i+1,j

        No Match
             |
           SKIP
             |
           i+1,j

The DP state:

    dp[i][j]

simply stores:

    "How many ways can I form t[j...] using s[i...]?"

This converts the otherwise exponential recursion into an
O(n * m) Dynamic Programming solution.
*/