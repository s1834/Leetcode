// Version 1: Recrsion + Memoization

// class Solution {
//     private:
//         int dp[1000][1000];
//         int solve(string& text1, string& text2, int i, int j) {
//             if(i >= text1.size() || j >= text2.size()) return 0;
    
//             if(dp[i][j] != -1) return dp[i][j];
    
//             if(text1[i] == text2[j]) return dp[i][j] = 1 + solve(text1, text2, i + 1, j + 1);
    
//             return dp[i][j] = max(solve(text1, text2, i + 1, j), solve(text1, text2, i, j + 1));
//         }
    
//     public:
//         int longestCommonSubsequence(string text1, string text2) {
//             memset(dp, -1, sizeof(dp));
//             return solve(text1, text2, 0, 0);
//         }
//     };

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

// Version 2: Bottom Up

class Solution {
    public:
        int longestCommonSubsequence(string text1, string text2) {
            int n = text1.size(), m = text2.size();
            vector<vector<int>> dp (n + 1, vector<int>(m + 1));
    
            for(int i = 0; i < n; i++) dp[i][0] = 0;
            for(int i = 0; i < m; i++) dp[0][i] = 0;
    
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= m; j++) {
                    if(text1[i - 1] == text2[j - 1]) {
                        dp[i][j] = 1 + dp[i - 1][j - 1];
                    } else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }
            return dp[n][m];
        }
    };

/*
LeetCode 1143. Longest Common Subsequence

Approach:
---------

This is the bottom-up Dynamic Programming solution for finding
the Longest Common Subsequence (LCS) of two strings.

A subsequence keeps the relative order of characters but does
not need to be contiguous.

Example:

    text1 = "abcde"
    text2 = "ace"

LCS:

    "ace"

Answer:

    3

------------------------------------------------------------

DP Definition:
--------------

    dp[i][j]

represents the length of the Longest Common Subsequence between:

    text1[0 ... i-1]
    text2[0 ... j-1]

In other words:

    dp[i][j] = LCS length using the first i characters of text1
               and the first j characters of text2

This is why the DP table has size:

    (n + 1) x (m + 1)

The extra row and column represent the case where one of the
strings has length 0.

------------------------------------------------------------

Why n + 1 and m + 1?
--------------------

We want to represent:

    dp[0][j]

meaning:

    LCS between an empty text1 and the first j characters
    of text2

Similarly:

    dp[i][0]

means:

    LCS between the first i characters of text1 and an empty
    text2

In both cases, the answer is:

    0

because an empty string cannot have a common subsequence with
a non-empty string.

------------------------------------------------------------

Initialization:
---------------

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

The vector is initialized with 0, so the first row and first
column are already 0.

The explicit initialization:

    for(int i = 0; i < n; i++) dp[i][0] = 0;
    for(int i = 0; i < m; i++) dp[0][i] = 0;

is therefore not necessary, but it is expressing the base case
explicitly.

Conceptually:

    dp[i][0] = 0
    dp[0][j] = 0

------------------------------------------------------------

Why Use text1[i - 1] and text2[j - 1]?
----------------------------------------

The DP indices start from 1:

    i = 1 ... n
    j = 1 ... m

But string indices start from 0:

    0 ... n - 1
    0 ... m - 1

Therefore, when calculating:

    dp[i][j]

the corresponding characters are:

    text1[i - 1]
    text2[j - 1]

For example:

    dp[1][1]

represents the first character of both strings:

    text1[0]
    text2[0]

------------------------------------------------------------

Case 1: Characters Match
-------------------------

    if(text1[i - 1] == text2[j - 1])

If the current characters are equal, we can include this
character in the LCS.

For example:

    text1 = "abc"
    text2 = "axc"

When comparing the 'c':

    text1[i - 1] == text2[j - 1]

So we include 'c'.

The previous LCS is:

    dp[i - 1][j - 1]

because we remove the matching character from both strings.

Therefore:

    dp[i][j] = 1 + dp[i - 1][j - 1];

The:

    +1

represents the current matching character.

------------------------------------------------------------

Why dp[i - 1][j - 1]?
----------------------

Once the current characters match and we take them, we need to
find the LCS of everything before those characters.

So:

    text1[0 ... i-2]
    text2[0 ... j-2]

which is exactly:

    dp[i - 1][j - 1]

Therefore:

    current match
          +
    best answer before both characters

becomes:

    1 + dp[i - 1][j - 1]

------------------------------------------------------------

Case 2: Characters Don't Match
------------------------------

    else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }

If:

    text1[i - 1] != text2[j - 1]

we cannot take both current characters as the same character
in the common subsequence.

So we have two choices.

------------------------------------------------------------

Choice 1: Ignore text1[i - 1]
------------------------------

    dp[i - 1][j]

We remove the current character from text1 and find the LCS
using:

    first i - 1 characters of text1
    first j characters of text2

This means:

    "What if this character from text1 is not part of the LCS?"

------------------------------------------------------------

Choice 2: Ignore text2[j - 1]
------------------------------

    dp[i][j - 1]

We remove the current character from text2 and find the LCS
using:

    first i characters of text1
    first j - 1 characters of text2

This means:

    "What if this character from text2 is not part of the LCS?"

------------------------------------------------------------

Take the Maximum:
------------------

Since we don't know which character should be skipped, we try
both possibilities:

    max(dp[i - 1][j], dp[i][j - 1])

The larger value represents the better LCS.

------------------------------------------------------------

Example:
--------

text1 = "abcde"
text2 = "ace"

The DP table conceptually looks like:

          ""  a  c  e
      ""   0  0  0  0
       a   0  1  1  1
       b   0  1  1  1
       c   0  1  2  2
       d   0  1  2  2
       e   0  1  2  3

The final answer is:

    dp[n][m] = dp[5][3] = 3

Corresponding to:

    "ace"

------------------------------------------------------------

How the Table Is Filled:
-------------------------

We fill the table from:

    top-left -> bottom-right

using:

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)

This is possible because every state:

    dp[i][j]

only depends on previously calculated states:

    dp[i - 1][j - 1]
    dp[i - 1][j]
    dp[i][j - 1]

So by the time we calculate dp[i][j], all required values
are already available.

------------------------------------------------------------

Relationship With the Recursive Version:
-----------------------------------------

The recursive + memoization version uses:

    solve(i, j)

and asks:

    "What is the LCS from these two positions onward?"

This bottom-up version asks:

    "What is the LCS using the first i and first j characters?"

The recurrence is the same.

Recursive:

    if(match)
        1 + solve(i + 1, j + 1)
    else
        max(
            solve(i + 1, j),
            solve(i, j + 1)
        )

Bottom-up:

    if(match)
        dp[i][j] = 1 + dp[i - 1][j - 1]
    else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

The difference is only in the direction in which we calculate
the states.

------------------------------------------------------------

Why We Don't Need to Reconstruct the String:
---------------------------------------------

The problem asks only for:

    length of the LCS

not the actual subsequence.

Therefore, we only store the length in:

    dp[i][j]

If we needed the actual LCS string, we would need additional
logic to reconstruct it by following the DP table backwards.

------------------------------------------------------------

Important Pattern:
------------------

For LCS, remember these two cases:

    MATCH:
        dp[i][j] = 1 + dp[i - 1][j - 1]

    MISMATCH:
        dp[i][j] = max(
            dp[i - 1][j],
            dp[i][j - 1]
        )

The match means:

    "Take this character from both strings."

The mismatch means:

    "One of these two current characters must be skipped,
     so try both possibilities."

------------------------------------------------------------

Complexity:
-----------

Let:

    n = text1.size()
    m = text2.size()

There are:

    (n + 1) * (m + 1)

DP states.

Each state takes O(1) work.

Therefore:

    Time Complexity: O(n * m)

The DP table contains n * m values:

    Space Complexity: O(n * m)

------------------------------------------------------------

Main Idea to Remember:
----------------------

This is a classic 2D DP problem.

    dp[i][j]
        =
    LCS of first i characters of text1
    and first j characters of text2

At every pair of characters:

    If they match:
        Take them both.
        Move diagonally.

    If they don't match:
        Skip one of them.
        Take the better of top and left.

Finally:

    dp[n][m]

contains the length of the Longest Common Subsequence.
*/