class Solution {
    private:
        int m, n;
        vector<vector<int>> dp;
    
        int solve(string& word1, string& word2, int i, int j) {
            if(i == m) return n - j;
            else if(j == n) return m - i;
    
            if(dp[i][j] != -1) return dp[i][j];
            
            if(word1[i] == word2[j]) return dp[i][j] = solve(word1, word2, i + 1, j + 1);
            else {
                int remove1 = 1 + solve(word1, word2, i + 1, j);
                int remove2 = 1 + solve(word1, word2, i, j + 1);
    
                return dp[i][j] = min(remove1, remove2);
            }
        }
    
    public:
        int minDistance(string word1, string word2) {
            m = word1.size();
            n = word2.size();
            dp.assign(m + 1, vector<int>(n + 1, -1));
            return solve(word1, word2, 0, 0);
        }
    };

/*
LeetCode 583. Delete Operation for Two Strings

Approach:
---------

We use Dynamic Programming with Memoization (Top-Down DP).

The goal is to make word1 and word2 equal using the minimum
number of deletion operations.

The only operation allowed is:

    Delete one character from either word1 or word2.

At every position, if the current characters are equal, we keep
both characters and move forward.

If they are different, we have two choices:

    1. Delete the current character from word1.
    2. Delete the current character from word2.

We try both choices and take the minimum.

------------------------------------------------------------

DP State:
---------

    dp[i][j]

represents the minimum number of deletions required to make:

    word1[i ... m-1]

and:

    word2[j ... n-1]

equal.

The recursive function:

    solve(word1, word2, i, j)

solves exactly this subproblem.

------------------------------------------------------------

Base Case:
----------

    if(i == m) return n - j;

If we have reached the end of word1, there are still:

    n - j

characters remaining in word2.

Since the only allowed operation is deletion, we must delete
all remaining characters from word2.

Therefore:

    answer = n - j

------------------------------------------------------------

Second Base Case:
-----------------

    else if(j == n) return m - i;

If we have reached the end of word2, there are still:

    m - i

characters remaining in word1.

We must delete all of them.

Therefore:

    answer = m - i

------------------------------------------------------------

Memoization:
------------

    if(dp[i][j] != -1) return dp[i][j];

The same (i, j) state can be reached through multiple recursive
paths.

Without memoization, we would solve the same subproblem many
times.

We store the answer in:

    dp[i][j]

and reuse it whenever the same state appears again.

There are only:

    m * n

possible states.

------------------------------------------------------------

Case 1: Characters Are Equal
----------------------------

    if(word1[i] == word2[j])
        return dp[i][j] =
            solve(word1, word2, i + 1, j + 1);

If:

    word1[i] == word2[j]

then these two characters can remain in the final string.

We do not need to delete either one.

Therefore, we move both pointers forward:

    i -> i + 1
    j -> j + 1

No additional operation is required.

So:

    dp[i][j] = dp[i + 1][j + 1]

------------------------------------------------------------

Case 2: Characters Are Different
---------------------------------

If:

    word1[i] != word2[j]

then both characters cannot simply be kept together.

Since our only operation is deletion, we have two choices.

------------------------------------------------------------

Choice 1: Delete from word1
---------------------------

    int remove1 = 1 + solve(word1, word2, i + 1, j);

We delete:

    word1[i]

After deleting it, we move forward only in word1:

    i -> i + 1
    j remains the same

The +1 represents the deletion operation.

Therefore:

    remove1 = 1 + solve(i + 1, j)

------------------------------------------------------------

Choice 2: Delete from word2
---------------------------

    int remove2 = 1 + solve(word1, word2, i, j + 1);

We delete:

    word2[j]

After deleting it, we move forward only in word2:

    i remains the same
    j -> j + 1

Again, +1 represents the deletion operation.

Therefore:

    remove2 = 1 + solve(i, j + 1)

------------------------------------------------------------

Choosing the Minimum:
----------------------

When the characters are different, we don't know which character
should be removed.

Therefore, try both possibilities:

    remove1 = 1 + solve(i + 1, j)

    remove2 = 1 + solve(i, j + 1)

and choose the better one:

    dp[i][j] = min(remove1, remove2);

This guarantees that we find the minimum number of deletions.

------------------------------------------------------------

Example:
--------

    word1 = "sea"
    word2 = "eat"

Start with:

    i = 0 -> 's'
    j = 0 -> 'e'

Characters are different:

    's' != 'e'

So we have two choices:

    Delete 's'
        |
        v
    solve(1, 0)

or:

    Delete 'e'
        |
        v
    solve(0, 1)

The recursion explores both possibilities and keeps the one
requiring fewer total deletions.

Eventually, the common characters can be kept while the remaining
unmatched characters are deleted.

For this example, the minimum number of deletions is:

    2

------------------------------------------------------------

Connection With LCS:
--------------------

This problem can also be understood using the Longest Common
Subsequence (LCS).

Suppose the two strings have:

    L = length of their LCS

The LCS represents the maximum number of characters that can be
kept in both strings.

Therefore:

    Characters to delete from word1 = m - L

    Characters to delete from word2 = n - L

Total deletions:

    (m - L) + (n - L)

    = m + n - 2L

Our DP directly calculates this minimum deletion count without
explicitly calculating the LCS first.

------------------------------------------------------------

Why Do We Move Both Pointers When Characters Match?
----------------------------------------------------

Suppose:

    word1 = "sea"
    word2 = "eat"

If:

    word1[i] == word2[j]

that character can be part of the common string.

There is no reason to delete it.

Therefore, we keep it and move:

    i + 1
    j + 1

For example:

    "abc..."
     ^
     i

    "axc..."
     ^
     j

If both point to the same character, we keep that character
and continue comparing the remaining suffixes.

------------------------------------------------------------

Why Only Two Choices When Characters Differ?
---------------------------------------------

Unlike LeetCode 72 (Edit Distance), this problem does NOT allow
replacement.

The only allowed operation is:

    delete

Therefore, when:

    word1[i] != word2[j]

we only have:

    Delete word1[i]

or:

    Delete word2[j]

There is no:

    replace

operation.

This is the main difference from the Edit Distance problem.

------------------------------------------------------------

DP Table Interpretation:
------------------------

The same recurrence can be represented using a bottom-up table.

    dp[i][j]

means:

    minimum deletions required to make
    word1[i...] and word2[j...] equal.

When characters match:

    dp[i][j] = dp[i + 1][j + 1]

When characters differ:

    dp[i][j] = 1 + min(
        dp[i + 1][j],
        dp[i][j + 1]
    )

Base cases:

    i == m -> n - j

    j == n -> m - i

Our recursive solution calculates this table from the starting
state:

    dp[0][0]

using memoization.

------------------------------------------------------------

Algorithm:
----------

    1. Store the lengths:

           m = word1.size()
           n = word2.size()

    2. Create a DP table initialized with -1.

    3. Start recursion:

           solve(word1, word2, 0, 0)

    4. If word1 is exhausted:

           return remaining characters of word2.

    5. If word2 is exhausted:

           return remaining characters of word1.

    6. If current characters are equal:

           move both pointers.

    7. Otherwise:

           Try deleting from word1.

           Try deleting from word2.

    8. Take the minimum of the two choices.

    9. Store the result in dp[i][j].

------------------------------------------------------------

State Transition:
-----------------

              word1[i] == word2[j]
                       |
                       v
                solve(i+1, j+1)
                       |
                       |
                    No +1


              word1[i] != word2[j]
                       |
              +--------+--------+
              |                 |
              v                 v
        Delete word1[i]   Delete word2[j]
              |                 |
              v                 v
        1 + solve(i+1,j)  1 + solve(i,j+1)
              |                 |
              +--------+--------+
                       |
                       v
                     min

------------------------------------------------------------

Time Complexity:
----------------

There are:

    m * n

different DP states.

Each state performs constant work.

Therefore:

    O(m * n)

------------------------------------------------------------

Space Complexity:
-----------------

The DP table contains:

    (m + 1) * (n + 1)

states.

The recursive call stack can grow up to:

    O(m + n)

Therefore the overall space complexity is:

    O(m * n)

because the DP table dominates.

------------------------------------------------------------

Core Idea:
----------

If the current characters are equal:

        word1[i] == word2[j]
                 |
                 v
        Keep both characters
                 |
                 v
        solve(i + 1, j + 1)


If the current characters are different:

       word1[i] != word2[j]
                 |
          +------+------+
          |             |
          v             v
     Delete word1   Delete word2
          |             |
          v             v
      (i + 1, j)    (i, j + 1)
          |             |
          +------+------+
                 |
                 v
               minimum


The key idea is:

    Keep matching characters,
    and when characters differ,
    delete one of them and choose the
    option that results in fewer deletions.

The final answer is:

    solve(word1, word2, 0, 0)
*/