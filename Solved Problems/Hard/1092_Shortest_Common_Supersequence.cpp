class Solution {
    public:
        string shortestCommonSupersequence(string str1, string str2) {
            int n = str1.size(), m = str2.size();
            vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    
            for(int i = 0; i < n + 1; i++) {
                for(int j = 0; j < m + 1; j++) {
                    if(i == 0 || j == 0) dp[i][j] = i + j;
                    else if(str1[i - 1] == str2[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
                    else dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
                }
            }
    
            string ans = "";
            int i = n, j = m;
            while(i > 0 && j > 0) {
                if(str1[i - 1] == str2[j - 1]) {
                    ans += str1[i - 1];
                    i--;
                    j--;
                } else {
                    if(dp[i - 1][j] < dp[i][j - 1]) {
                        ans += str1[i - 1];
                        i--;
                    } else {
                        ans += str2[j - 1];
                        j--;
                    }
                }
            }
    
            while(i > 0) {
                ans += str1[i - 1];
                i--;
            }
            
            while(j > 0) {
                ans += str2[j - 1];
                j--;
            }
    
            reverse(ans.begin(), ans.end());
            return ans;
        }
    };

/*
LeetCode 1092. Shortest Common Supersequence

Approach:
---------

We need to find the shortest string that contains both str1 and
str2 as subsequences.

A subsequence does not need to be contiguous, but the relative
order of characters must be maintained.

For example:

    str1 = "abac"
    str2 = "cab"

One possible common supersequence is:

    "cabac"

It contains both strings as subsequences.

The solution has two main parts:

    1. Build a DP table to find the length of the shortest
       common supersequence.
    2. Traverse the DP table backwards to construct the actual
       shortest common supersequence.

------------------------------------------------------------

DP Definition:
--------------

    dp[i][j]

represents the length of the Shortest Common Supersequence
of:

    first i characters of str1
    first j characters of str2

So:

    dp[i][j] = SCS length of str1[0 ... i-1]
               and str2[0 ... j-1]

We use:

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

because we also need to represent the case where one of the
strings is empty.

------------------------------------------------------------

Why n + 1 and m + 1?
--------------------

The extra row represents:

    str1 = ""

and the extra column represents:

    str2 = ""

For example:

    dp[0][3]

means:

    SCS of an empty str1 and the first 3 characters of str2.

The only possible supersequence is to take all 3 characters
from str2.

Therefore:

    dp[0][3] = 3

Similarly:

    dp[4][0] = 4

because all 4 characters of str1 must be taken.

------------------------------------------------------------

Base Case:
----------

    if(i == 0 || j == 0)
        dp[i][j] = i + j;

If one string is empty, there is no common character to reuse.

Therefore, we must simply take all characters from the other
string.

Examples:

    dp[0][0] = 0

    dp[0][j] = j

    dp[i][0] = i

------------------------------------------------------------

Case 1: Current Characters Match
---------------------------------

    else if(str1[i - 1] == str2[j - 1])

If the current characters are equal, we only need ONE copy of
that character in the supersequence.

For example:

    str1 = "abc"
    str2 = "ac"

Suppose we are comparing:

    str1[2] = 'c'
    str2[1] = 'c'

We can use the same 'c' for both strings.

So we take:

    1

for this character and move diagonally:

    dp[i - 1][j - 1]

Therefore:

    dp[i][j] = 1 + dp[i - 1][j - 1];

The diagonal movement means:

    "This character has been consumed from BOTH strings."

------------------------------------------------------------

Why Only One Character When They Match?
----------------------------------------

Suppose:

    str1 = "ab"
    str2 = "ac"

The character 'a' occurs at the beginning of both strings.

We don't need:

    "a a ..."

We can use a single:

    "a"

to satisfy both strings.

So matching characters can be shared.

This is the main reason the SCS can be shorter than simply
concatenating the two strings.

------------------------------------------------------------

Case 2: Current Characters Are Different
-----------------------------------------

    else {
        dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
    }

If:

    str1[i - 1] != str2[j - 1]

then the current characters cannot be represented by the same
character.

We have two choices.

------------------------------------------------------------

Choice 1: Take str1[i - 1]
--------------------------

If we take the current character from str1, we consume:

    str1[i - 1]

but still need all of:

    first j characters of str2

So the remaining problem is:

    dp[i - 1][j]

This corresponds to moving:

    UP

in the DP table.

------------------------------------------------------------

Choice 2: Take str2[j - 1]
--------------------------

Alternatively, we take the current character from str2.

Then the remaining problem is:

    dp[i][j - 1]

This corresponds to moving:

    LEFT

in the DP table.

------------------------------------------------------------

Why Take min()?
----------------

We need to include one of the two different characters.

So we try both possibilities:

    take str1 character
        -> dp[i - 1][j]

    take str2 character
        -> dp[i][j - 1]

and choose the one that produces the shorter SCS:

    min(dp[i - 1][j], dp[i][j - 1])

Then we add:

    1

for the character we just selected.

Therefore:

    dp[i][j] =
        1 + min(dp[i - 1][j], dp[i][j - 1]);

------------------------------------------------------------

Complete DP Recurrence:
-----------------------

If:

    str1[i - 1] == str2[j - 1]

then:

    dp[i][j] = 1 + dp[i - 1][j - 1]

Otherwise:

    dp[i][j] = 1 + min(
        dp[i - 1][j],
        dp[i][j - 1]
    )

The difference from LCS is important.

For LCS:

    MATCH:
        +1 and diagonal

    MISMATCH:
        max(top, left)

For SCS:

    MATCH:
        +1 and diagonal

    MISMATCH:
        1 + min(top, left)

------------------------------------------------------------

Example:
--------

Take:

    str1 = "abcde"
    str2 = "ace"

The DP table is:

                 ""    a    c    e
              +-----+-----+-----+-----+
          ""  |  0  |  1  |  2  |  3  |
              +-----+-----+-----+-----+
           a  |  1  |  1  |  2  |  3  |
              +-----+-----+-----+-----+
           b  |  2  |  2  |  3  |  4  |
              +-----+-----+-----+-----+
           c  |  3  |  3  |  3  |  4  |
              +-----+-----+-----+-----+
           d  |  4  |  4  |  4  |  5  |
              +-----+-----+-----+-----+
           e  |  5  |  5  |  5  |  5  |
              +-----+-----+-----+-----+

The final cell:

    dp[n][m]

is:

    dp[5][3] = 5

So the shortest common supersequence has length 5.

One valid answer is:

    "abcde"

because:

    str1 = "abcde"
    str2 = "ace"

Both are subsequences of "abcde".

------------------------------------------------------------

How the DP Table Is Built:
---------------------------

We fill the table from:

    top-left -> bottom-right

because every state depends only on already calculated states:

    dp[i - 1][j - 1]
    dp[i - 1][j]
    dp[i][j - 1]

So when calculating:

    dp[i][j]

all required values are already available.

------------------------------------------------------------

Now Construct the Actual String:
---------------------------------

The DP table only tells us the LENGTH of the shortest
supersequence.

But the problem asks us to return the actual string.

Therefore, we start from the bottom-right:

    i = n
    j = m

and walk backwards through the DP table.

This is the reverse of how we filled the table.

------------------------------------------------------------

Why Start From dp[n][m]?
-------------------------

    dp[n][m]

represents:

    SCS of the COMPLETE str1 and COMPLETE str2.

So this is exactly the state whose choices produced our
optimal answer.

By following the choices backwards, we can reconstruct the
characters that created that minimum length.

------------------------------------------------------------

Reconstruction Case 1: Characters Match
---------------------------------------

    if(str1[i - 1] == str2[j - 1]) {

        ans += str1[i - 1];
        i--;
        j--;

    }

If the current characters match, they were represented by ONE
character in the SCS.

Therefore:

    add the character once

and move diagonally:

    i--
    j--

This means:

    "We consumed this character from both strings."

------------------------------------------------------------

Reconstruction Case 2: Characters Differ
-----------------------------------------

If:

    str1[i - 1] != str2[j - 1]

we need to determine which character was selected while
calculating the DP value.

We compare:

    dp[i - 1][j]

and:

    dp[i][j - 1]

------------------------------------------------------------

If UP Is Smaller:
-----------------

    if(dp[i - 1][j] < dp[i][j - 1])

then the DP table tells us that taking:

    str1[i - 1]

produces the shorter remaining supersequence.

So:

    ans += str1[i - 1];
    i--;

We move UP.

------------------------------------------------------------

Otherwise:
----------

    else {
        ans += str2[j - 1];
        j--;
    }

We choose the character from str2 and move LEFT.

This also handles the case where:

    dp[i - 1][j] == dp[i][j - 1]

In that case, either choice gives a valid shortest common
supersequence.

The returned answer may be different from another valid answer,
but it will have the same minimum length.

------------------------------------------------------------

Why Is ans Built Backwards?
----------------------------

We start from:

    i = n
    j = m

and move toward:

    i = 0
    j = 0

Therefore, the characters are added from the END of the answer
towards the BEGINNING.

For example, we may build:

    "edcba"

instead of:

    "abcde"

So after reconstruction:

    reverse(ans.begin(), ans.end());

gives the answer in the correct order.

------------------------------------------------------------

Remaining Characters in str1:
------------------------------

After the main loop:

    while(i > 0 && j > 0)

one of the strings may have been completely processed while the
other still has characters remaining.

If:

    i > 0

then str1 still contains characters that haven't been added.

Since str2 is already exhausted, we have no choice but to add
all remaining characters from str1:

    while(i > 0) {
        ans += str1[i - 1];
        i--;
    }

------------------------------------------------------------

Remaining Characters in str2:
------------------------------

Similarly, if:

    j > 0

then str2 still has characters remaining.

We add all of them:

    while(j > 0) {
        ans += str2[j - 1];
        j--;
    }

------------------------------------------------------------

Example of Reconstruction:
---------------------------

For:

    str1 = "abcde"
    str2 = "ace"

we start at:

    dp[5][3]

Current:

    str1[4] = 'e'
    str2[2] = 'e'

Match:

    add 'e'
    move diagonal

Then:

    str1[3] = 'd'
    str2[1] = 'c'

Different.

Compare:

    dp[3][2] = 3
    dp[4][1] = 4

UP is smaller, so:

    add 'd'
    move UP

Then:

    'c' == 'c'

Add:

    'c'

Then:

    'b' != 'a'

Compare UP and LEFT and choose 'b'.

Finally:

    'a' == 'a'

Add 'a'.

We have constructed:

    "edcba"

because we moved backwards.

After reversing:

    "abcde"

------------------------------------------------------------

Important Difference From LCS:
-------------------------------

LCS asks:

    "What is the maximum number of characters that can be
     shared between the two strings?"

SCS asks:

    "What is the minimum total number of characters needed
     to contain both strings?"

Therefore:

LCS:

    match:
        1 + diagonal

    mismatch:
        max(top, left)


SCS:

    match:
        1 + diagonal

    mismatch:
        1 + min(top, left)

The SCS is essentially trying to SHARE matching characters
whenever possible and otherwise add one of the two characters.

------------------------------------------------------------

Another Useful Relationship:
-----------------------------

There is also a relationship between SCS and LCS:

    SCS length =
        str1.length()
        + str2.length()
        - LCS length

Why?

If we simply concatenate both strings, the length is:

    n + m

Every character that belongs to the common subsequence can be
shared once instead of appearing twice.

So if the LCS has length L:

    SCS = n + m - L

The DP used here calculates the SCS length directly, rather
than calculating LCS first.

------------------------------------------------------------

Overall Flow:
-------------

             Build DP Table
                    |
                    ↓
       dp[i][j] = shortest length
                    |
                    ↓
             Start at dp[n][m]
                    |
                    ↓
        Compare str1[i-1], str2[j-1]
                    |
          +---------+---------+
          |                   |
        MATCH              DIFFERENT
          |                   |
          ↓                   ↓
       Add once          Compare UP/LEFT
          |                   |
       ↙ diagonal         choose smaller
                              |
                    +---------+---------+
                    |                   |
                   UP                 LEFT
                    |                   |
               take str1           take str2
                    |                   |
                  i--                 j--
                    \                   /
                     \                 /
                      ↓               ↓
                    Continue until
                    one string ends
                            |
                            ↓
                  Add remaining chars
                            |
                            ↓
                         reverse
                            |
                            ↓
                         answer

------------------------------------------------------------

Complexity:
-----------

Let:

    n = str1.size()
    m = str2.size()

There are:

    (n + 1) * (m + 1)

DP states.

Each state takes O(1) work.

Therefore:

    Time Complexity: O(n * m)

The DP table requires:

    O(n * m)

space.

The reconstruction takes:

    O(n + m)

additional time.

Therefore overall:

    Time Complexity: O(n * m)

    Space Complexity: O(n * m)

------------------------------------------------------------

Main Idea to Remember:
----------------------

This problem has TWO things to remember:

1. BUILD the shortest length:

    if characters MATCH:

        dp[i][j] = 1 + dp[i - 1][j - 1]

    if characters DIFFER:

        dp[i][j] = 1 + min(
            dp[i - 1][j],
            dp[i][j - 1]
        )

2. RECONSTRUCT the string from bottom-right:

    MATCH:
        add character once
        move diagonal

    DIFFERENT:
        compare UP and LEFT
        take the direction with smaller dp value

Finally, add any remaining characters and reverse the answer.

The main mental model is:

    MATCH
        -> share the character
        -> diagonal

    DIFFERENT
        -> we must add one character
        -> choose the cheaper side

So:

    "Build DP forward,
     reconstruct answer backward."
*/