class Solution {
    private:
        int dp[1000][1000];
        int solve(string& text1, string& text2, int i, int j) {
            if(i >= text1.size() || j >= text2.size()) return 0;
    
            if(dp[i][j] != -1) return dp[i][j];
    
            if(text1[i] == text2[j]) return dp[i][j] = 1 + solve(text1, text2, i + 1, j + 1);
    
            return dp[i][j] = max(solve(text1, text2, i + 1, j), solve(text1, text2, i, j + 1));
        }
    
    public:
        int longestCommonSubsequence(string text1, string text2) {
            memset(dp, -1, sizeof(dp));
            return solve(text1, text2, 0, 0);
        }
    };

/*
LeetCode 1143. Longest Common Subsequence

Approach:
---------

We need to find the length of the longest subsequence that
appears in BOTH strings while keeping the relative order of
characters.

A subsequence does not need to be contiguous.

For example:

    text1 = "abcde"
    text2 = "ace"

The longest common subsequence is:

    "ace"

Answer:

    3

This solution uses:

    Recursion + Memoization (Top-Down DP)

------------------------------------------------------------

DP State:
---------

The recursive function is:

    solve(text1, text2, i, j)

where:

    i = current index in text1
    j = current index in text2

So:

    solve(i, j)

means:

    "What is the longest common subsequence we can find
     between text1[i...] and text2[j...]?"

We only care about the remaining suffixes of both strings.

Therefore, the DP state is:

    dp[i][j]

which stores the LCS length between:

    text1[i...]
    text2[j...]

------------------------------------------------------------

Starting State:
---------------

    return solve(text1, text2, 0, 0);

Initially, we are comparing:

    text1[0]
    text2[0]

So we start from the beginning of both strings.

------------------------------------------------------------

Base Case:
----------

    if(i >= text1.size() || j >= text2.size())
        return 0;

If either string has been completely processed, there cannot
be any more common characters.

For example:

    text1 = "abc"
    text2 = ""

There is no common subsequence, so:

    0

This is why reaching the end of either string returns 0.

------------------------------------------------------------

Memoization:
------------

    if(dp[i][j] != -1)
        return dp[i][j];

The same pair of indices can be reached through many different
recursive paths.

Once we have calculated:

    dp[i][j]

we don't need to calculate it again.

Initially:

    memset(dp, -1, sizeof(dp));

so:

    -1

means:

    "This state has not been calculated yet."

------------------------------------------------------------

Case 1: Characters Match
-------------------------

    if(text1[i] == text2[j])

If the current characters are equal, we can definitely use this
character in the common subsequence.

For example:

    text1 = "abc..."
             ^
             i

    text2 = "axc..."
             ^
             j

If:

    text1[i] == text2[j]

we take this character.

So the answer becomes:

    1 + solve(i + 1, j + 1)

The:

    +1

is for the matching character.

Then we move forward in BOTH strings because this character has
already been used.

------------------------------------------------------------

Why Move Both i and j?
----------------------

Suppose:

    text1[i] = 'a'
    text2[j] = 'a'

We use this 'a' as part of the LCS.

We cannot use the same character again, so we move past it:

    i + 1
    j + 1

Therefore:

    1 + solve(i + 1, j + 1)

------------------------------------------------------------

Case 2: Characters Don't Match
------------------------------

If:

    text1[i] != text2[j]

we cannot take both current characters together.

For example:

    text1[i] = 'a'
    text2[j] = 'b'

There are two possibilities:

    1. Skip text1[i]
    2. Skip text2[j]

We try both.

------------------------------------------------------------

Option 1: Skip text1[i]
-----------------------

    solve(text1, text2, i + 1, j)

We ignore the current character from text1 and continue
comparing:

    text1[i + 1...]
    text2[j...]

------------------------------------------------------------

Option 2: Skip text2[j]
-----------------------

    solve(text1, text2, i, j + 1)

We ignore the current character from text2 and continue
comparing:

    text1[i...]
    text2[j + 1...]

------------------------------------------------------------

Take the Better Option:
------------------------

Since either character could be the one that should be skipped,
we calculate both possibilities and take the maximum:

    max(
        solve(i + 1, j),
        solve(i, j + 1)
    )

This gives the longest possible common subsequence.

------------------------------------------------------------

Complete Recurrence:
--------------------

If:

    text1[i] == text2[j]

then:

    dp[i][j] =
        1 + dp[i + 1][j + 1]

Otherwise:

    dp[i][j] =
        max(
            dp[i + 1][j],
            dp[i][j + 1]
        )

This is the core of the LCS problem.

------------------------------------------------------------

Example:
--------

text1 = "abcde"
text2 = "ace"

Start:

    i = 0 -> 'a'
    j = 0 -> 'a'

They match:

    +1

Move both:

    i = 1 -> 'b'
    j = 1 -> 'c'

They don't match.

We have two choices:

    Skip 'b'
    OR
    Skip 'c'

The recursion explores both and keeps the better result.

Eventually we find:

    a -> c -> e

So:

    LCS = 3

------------------------------------------------------------

Why Is This a 2D DP?
---------------------

The answer depends on TWO changing values:

    i
    j

Therefore the state is:

    dp[i][j]

You can think of the DP table as:

              text2
          j -> 0  1  2  ...
       +----------------
    i  |
       0 |
       1 |
       2 |
      ...|

Each cell represents:

    LCS of text1[i...] and text2[j...]

------------------------------------------------------------

Important Difference Between Subsequence and Substring:
--------------------------------------------------------

LCS asks for a SUBSEQUENCE, not a substring.

So the selected characters do not need to be adjacent.

For example:

    text1 = "abcde"
    text2 = "ace"

We can select:

    a
      c
        e

even though they are separated in text1.

The recursive Skip choices allow us to ignore characters between
the characters that we choose.

------------------------------------------------------------

Why Do We Take max() Only When Characters Differ?
------------------------------------------------------------

If:

    text1[i] == text2[j]

we know that this matching character can be included in an
optimal solution, so we take it:

    1 + solve(i + 1, j + 1)

When they are different, they cannot both represent the same
position in the common subsequence.

Therefore, we need to decide which character to skip:

    skip text1[i]
    OR
    skip text2[j]

and take the better result.

------------------------------------------------------------

Example of Mismatch:
---------------------

text1 = "abc"
text2 = "adc"

At:

    i = 1 -> 'b'
    j = 1 -> 'd'

They don't match.

We calculate:

    solve(2, 1)
        // skip 'b'

and:

    solve(1, 2)
        // skip 'd'

One of these paths will eventually allow us to match:

    'a' and 'c'

The maximum gives the correct LCS.

------------------------------------------------------------

Why Memoization Is Important:
-----------------------------

Without DP, the recursion repeatedly solves the same states.

For example:

    solve(i, j)

can be reached from:

    solve(i + 1, j)

and:

    solve(i, j + 1)

This creates a large number of overlapping subproblems.

Memoization ensures each:

    (i, j)

pair is calculated only once.

------------------------------------------------------------

Overall Flow:
-------------

          solve(i, j)
              |
       +------+------+
       |             |
    same char     different
       |             |
       ↓             ↓
   take both     skip text1
       |             OR
       ↓          skip text2
1 + solve(i+1,j+1)   |
                     ↓
                    max
                     |
                     ↓
                 dp[i][j]

------------------------------------------------------------

Complexity:
-----------

Let:

    n = text1.size()
    m = text2.size()

There are:

    n * m

possible pairs of indices:

    (i, j)

Each state is calculated only once because of memoization.

Each state performs O(1) work apart from its recursive calls.

Therefore:

    Time Complexity: O(n * m)

The DP table contains:

    O(n * m)

states.

The recursion depth can be at most:

    O(n + m)

So:

    Space Complexity: O(n * m)

for the DP table, plus O(n + m) recursion stack space.

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

LCS is a classic:

    2D DP + Take/Skip

problem.

The state is:

    solve(i, j)

meaning:

    "LCS of the remaining portions of both strings."

If characters match:

    1 + solve(i + 1, j + 1)

If characters don't match:

    max(
        solve(i + 1, j),
        solve(i, j + 1)
    )

The key idea is:

    MATCH:
        take the character from both strings.

    MISMATCH:
        one of the current characters must be skipped,
        so try both possibilities and take the better one.

This is the main recurrence to remember for
LeetCode 1143.
*/