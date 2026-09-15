// Version 1: Recursion + Memoization 1
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

// Version 2: Recursion + Memoization 2
class Solution {
    private:
        int m, n;
        vector<vector<int>> dp;
    
        int solve(string& word1, string& word2, int m, int n) {
            if(m == 0 || n == 0) return m + n;
    
            if(dp[m][n] != -1) return dp[m][n];
            
            if(word1[m - 1] == word2[n - 1]) return dp[m][n] = solve(word1, word2, m - 1, n - 1);
            else {
                int remove1 = 1 + solve(word1, word2, m - 1, n);
                int remove2 = 1 + solve(word1, word2, m, n - 1);
    
                return dp[m][n] = min(remove1, remove2);
            }
        }
    
    public:
        int minDistance(string word1, string word2) {
            m = word1.size();
            n = word2.size();
            dp.assign(m + 1, vector<int>(n + 1, -1));
            return solve(word1, word2, m, n);
        }
    };

/*
LeetCode 583. Delete Operation for Two Strings

Version 2: Recursion + Memoization 2

Approach:
---------

We use Dynamic Programming with Memoization (Top-Down DP).

The goal is to make word1 and word2 equal using the minimum
number of deletion operations.

The only allowed operation is:

    Delete one character from either word1 or word2.

At every state, we compare the LAST characters of the current
prefixes of word1 and word2.

There are two cases:

    1. Last characters are equal
       -> keep both characters and move diagonally.

    2. Last characters are different
       -> delete either the last character of word1
          or the last character of word2,
          and take the minimum.

------------------------------------------------------------

DP State:
---------

    dp[m][n]

represents the minimum number of deletions required to make:

    word1[0 ... m-1]

and:

    word2[0 ... n-1]

equal.

Here:

    m = number of characters currently considered from word1
    n = number of characters currently considered from word2

So:

    solve(word1, word2, m, n)

solves the subproblem for the first m characters of word1 and
the first n characters of word2.

This version is slightly different from Version 1:

    Version 1:
        i and j represented starting indices.

    Version 2:
        m and n represent lengths of the current prefixes.

Therefore, the current characters are:

    word1[m - 1]
    word2[n - 1]

------------------------------------------------------------

Base Case:
----------

    if(m == 0 || n == 0) return m + n;

If either string becomes empty, all remaining characters from
the other string must be deleted.

Case 1:
-------

    m == 0

word1 is empty, while word2 still contains n characters.

We need to delete all n characters from word2.

Therefore:

    answer = n

Case 2:
-------

    n == 0

word2 is empty, while word1 still contains m characters.

We need to delete all m characters from word1.

Therefore:

    answer = m

Both cases are represented by:

    m + n

because one of them is zero.

------------------------------------------------------------

Memoization:
------------

    if(dp[m][n] != -1) return dp[m][n];

The same (m, n) state can be reached through multiple recursive
paths.

Without memoization, we would repeatedly calculate the same
subproblems.

We store every calculated answer in:

    dp[m][n]

If the state has already been calculated, return it immediately.

This reduces the number of states to:

    O(m * n)

------------------------------------------------------------

Case 1: Last Characters Are Equal
---------------------------------

    if(word1[m - 1] == word2[n - 1])

If the last characters are equal, we do not need to delete
either of them.

For example:

    word1 = "abc"
    word2 = "adc"

At the current state, if:

    word1[m - 1] == word2[n - 1]

then both characters can remain in the final string.

We simply remove them from consideration and solve the remaining
prefixes:

    solve(word1, word2, m - 1, n - 1)

Therefore:

    dp[m][n] = dp[m - 1][n - 1]

There is NO +1 because we performed no deletion.

------------------------------------------------------------

Case 2: Last Characters Are Different
--------------------------------------

If:

    word1[m - 1] != word2[n - 1]

then the two characters cannot both remain as the final matching
character.

Since the only allowed operation is deletion, we have two choices:

    1. Delete word1[m - 1]
    2. Delete word2[n - 1]

We try both and take the minimum.

------------------------------------------------------------

Choice 1: Remove From word1
---------------------------

    int remove1 = 1 + solve(word1, word2, m - 1, n);

We delete:

    word1[m - 1]

from word1.

After deleting it, word1 has one fewer character:

    m -> m - 1

while word2 remains unchanged:

    n -> n

Therefore:

    remove1 = 1 + solve(m - 1, n)

The +1 represents the deletion operation.

------------------------------------------------------------

Choice 2: Remove From word2
---------------------------

    int remove2 = 1 + solve(word1, word2, m, n - 1);

We delete:

    word2[n - 1]

from word2.

After deleting it:

    m -> m

    n -> n - 1

Therefore:

    remove2 = 1 + solve(m, n - 1)

Again, the +1 represents the deletion operation.

------------------------------------------------------------

Choosing the Minimum:
----------------------

When the characters are different, we don't know which character
should be removed.

Therefore, we try both possibilities:

    remove1 = 1 + solve(m - 1, n)

    remove2 = 1 + solve(m, n - 1)

and choose the minimum:

    dp[m][n] = min(remove1, remove2);

This guarantees the minimum number of deletions.

------------------------------------------------------------

Why Are We Comparing word1[m - 1] and word2[n - 1]?
-----------------------------------------------------

Here m and n represent LENGTHS, not 0-based indices.

For example:

    word1 = "abc"

If:

    m = 3

then the last valid index is:

    m - 1 = 2

and therefore:

    word1[m - 1] = word1[2] = 'c'

Similarly:

    word2[n - 1]

represents the last character of the current prefix of word2.

This is why we use:

    word1[m - 1]
    word2[n - 1]

instead of:

    word1[m]
    word2[n]

------------------------------------------------------------

Example:
--------

    word1 = "sea"
    word2 = "eat"

We start with:

    solve("sea", "eat", 3, 3)

Compare:

    word1[2] = 'a'
    word2[2] = 't'

They are different.

Therefore, we have two choices:

    Remove 'a' from word1
        |
        v
    solve(2, 3)

OR:

    Remove 't' from word2
        |
        v
    solve(3, 2)

The recursion continues exploring both possibilities.

Whenever the characters match, both lengths decrease:

    solve(m - 1, n - 1)

Eventually one string becomes empty, and the remaining characters
of the other string are deleted.

The minimum result is:

    2

------------------------------------------------------------

Connection With LCS:
--------------------

This problem can also be solved using the Longest Common
Subsequence (LCS).

Suppose:

    L = length of LCS(word1, word2)

The LCS represents the maximum number of characters that can
remain in BOTH strings.

Therefore:

    Characters deleted from word1 = m - L

    Characters deleted from word2 = n - L

Total deletions:

    (m - L) + (n - L)

    = m + n - 2L

Our current DP directly calculates the minimum number of
deletions without explicitly calculating the LCS.

------------------------------------------------------------

Difference From LeetCode 72:
----------------------------

LeetCode 72 (Edit Distance) allows:

    Insert
    Delete
    Replace

LeetCode 583 allows ONLY:

    Delete

Therefore, when characters are different, we have only two
choices:

    delete from word1
    delete from word2

There is NO replace operation.

That is why the recurrence is:

    min(
        1 + solve(m - 1, n),
        1 + solve(m, n - 1)
    )

instead of the three choices used in Edit Distance.

------------------------------------------------------------

DP Table Interpretation:
------------------------

The same recurrence can be represented using a bottom-up table.

    dp[m][n]

means:

    minimum deletions required to make
    word1[0...m-1] and word2[0...n-1] equal.

When the last characters match:

    dp[m][n] = dp[m - 1][n - 1]

When they differ:

    dp[m][n] = 1 + min(
        dp[m - 1][n],
        dp[m][n - 1]
    )

Base cases:

    dp[0][n] = n

    dp[m][0] = m

Our recursive solution calculates exactly these states,
but only when they are needed.

------------------------------------------------------------

State Transition:
-----------------

              word1[m-1] == word2[n-1]
                         |
                         v
                 Keep both characters
                         |
                         v
                   solve(m-1,n-1)
                         |
                         |
                      No +1


              word1[m-1] != word2[n-1]
                         |
                +--------+--------+
                |                 |
                v                 v
          Remove word1      Remove word2
                |                 |
                v                 v
        1 + solve(m-1,n)  1 + solve(m,n-1)
                |                 |
                +--------+--------+
                         |
                         v
                       minimum

------------------------------------------------------------

Algorithm:
----------

    1. Find the lengths of both strings.

    2. Create a DP table of size:

           (m + 1) x (n + 1)

       initialized with -1.

    3. Start recursion with:

           solve(word1, word2, m, n)

    4. If either length becomes 0:

           return m + n

    5. If the last characters are equal:

           solve(m - 1, n - 1)

    6. Otherwise:

           Remove the last character from word1.

           Remove the last character from word2.

    7. Take the minimum of the two choices.

    8. Store the result in dp[m][n].

    9. Return dp[m][n] through the initial recursive call.

------------------------------------------------------------

Why This DP Works:
------------------

At every step, we are deciding which characters can stay in the
final common string.

If the last characters are equal:

        word1[m-1] == word2[n-1]

we can safely keep both.

If they are different:

        word1[m-1] != word2[n-1]

at least one of them must be removed.

So we try:

        remove word1[m-1]

and:

        remove word2[n-1]

The optimal answer must come from one of these two choices.

Memoization ensures that every unique pair:

        (m, n)

is solved only once.

------------------------------------------------------------

Time Complexity:
----------------

There are:

    m * n

possible DP states.

Each state performs only constant work apart from recursive
calls.

Therefore:

    O(m * n)

------------------------------------------------------------

Space Complexity:
-----------------

The DP table requires:

    O(m * n)

space.

The recursion stack can grow up to:

    O(m + n)

Therefore overall:

    O(m * n)

because the DP table dominates.

------------------------------------------------------------

Core Idea:
----------

              Last characters equal
                       |
                       v
                  Keep both
                       |
                       v
                solve(m-1,n-1)


              Last characters different
                       |
              +--------+--------+
              |                 |
              v                 v
        Delete from word1  Delete from word2
              |                 |
              v                 v
          (m-1,n)            (m,n-1)
              |                 |
              +--------+--------+
                       |
                       v
                     min


The key idea is:

    If characters match, keep them.

    If characters don't match, one of them must be deleted.

    Try deleting either one and choose the minimum.

The final answer is:

    solve(word1, word2, m, n)
*/

// Version 3: Bottom-Up
class Solution {
    public:
        int minDistance(string word1, string word2) {
            int m = word1.size();
            int n = word2.size();
    
            vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
            for(int i = 0; i <= m; i++) {
                for(int j = 0; j <= n; j++) {
                    if(i == 0 || j == 0) dp[i][j] = i + j;
                    else if(word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                    else {
                        int remove1 = 1 + dp[i - 1][j];
                        int remove2 = 1 + dp[i][j - 1];
                        dp[i][j] = min(remove1, remove2);
                    }
                }
            }
    
            return dp[m][n];
        }
    };

/*
LeetCode 583. Delete Operation for Two Strings

Approach:
---------

We use Dynamic Programming with a bottom-up approach.

The goal is to find the minimum number of deletions required to
make word1 and word2 equal.

At every position, we compare the characters currently being
considered.

------------------------------------------------------------

DP Definition:
--------------

    dp[i][j] = minimum number of deletions required to make
               the first i characters of word1 and the first j
               characters of word2 equal.

Therefore:

    dp[m][n]

is the answer for the complete two strings.

------------------------------------------------------------

Base Cases:
-----------

If one of the strings is empty, the only way to make both strings
equal is to delete every character from the other string.

    if(i == 0 || j == 0)
        dp[i][j] = i + j;

For example:

    word1 = "abc"
    word2 = ""

We need to delete all 3 characters:

    dp[3][0] = 3

Similarly:

    word1 = ""
    word2 = "xyz"

    dp[0][3] = 3

------------------------------------------------------------

Case 1: Characters Are Equal
----------------------------

If:

    word1[i - 1] == word2[j - 1]

then the current characters already match.

We do not need to delete either character.

Therefore, we simply use the answer for the previous characters:

    dp[i][j] = dp[i - 1][j - 1];

For example:

    word1 = "abc"
    word2 = "adc"

When comparing the last characters:

    'c' == 'c'

So we can keep both and solve:

    "ab" vs "ad"

------------------------------------------------------------

Case 2: Characters Are Different
---------------------------------

If:

    word1[i - 1] != word2[j - 1]

then both characters cannot remain in the final equal strings.

We have two choices:

    1. Delete word1[i - 1]
    2. Delete word2[j - 1]

------------------------------------------------------------

Choice 1: Remove From word1
---------------------------

Delete the current character from word1.

    int remove1 = 1 + dp[i - 1][j];

The `1` represents the deletion we just performed.

After deleting word1[i - 1], we need to make:

    first (i - 1) characters of word1
    first j characters of word2

equal.

------------------------------------------------------------

Choice 2: Remove From word2
---------------------------

Delete the current character from word2.

    int remove2 = 1 + dp[i][j - 1];

Again, the `1` represents the deletion we just performed.

Now we need to make:

    first i characters of word1
    first (j - 1) characters of word2

equal.

------------------------------------------------------------

Choose the Better Option:
--------------------------

Since we want the minimum number of deletions:

    dp[i][j] = min(remove1, remove2);

Therefore:

    if(word1[i - 1] != word2[j - 1]) {
        int remove1 = 1 + dp[i - 1][j];
        int remove2 = 1 + dp[i][j - 1];

        dp[i][j] = min(remove1, remove2);
    }

------------------------------------------------------------

Bottom-Up Order:
----------------

Each state depends on:

    dp[i - 1][j]
    dp[i][j - 1]
    dp[i - 1][j - 1]

Therefore, we calculate the table from:

    i = 0 -> m
    j = 0 -> n

so that all required smaller states are already calculated.

------------------------------------------------------------

Example:
--------

    word1 = "sea"
    word2 = "eat"

We want to make them equal.

One optimal solution is:

    "sea" -> "ea"
    "eat" -> "ea"

So we delete:

    's' from word1
    't' from word2

Answer:

    2

The DP table ultimately gives:

    dp[3][3] = 2

------------------------------------------------------------

Why Does This Work?
-------------------

At every state dp[i][j]:

    If the current characters are equal:
        Keep both characters.

    If they are different:
        One of them must be deleted.

We try both possible deletions and choose the one requiring
fewer total deletions.

Since every state represents the optimal answer for its
corresponding prefixes, building the table from smaller prefixes
to larger prefixes gives the optimal answer for the complete
strings.

------------------------------------------------------------

Algorithm:
----------

    1. Let m = word1.size() and n = word2.size().

    2. Create a DP table of size:

           (m + 1) x (n + 1)

    3. Initialize the first row and first column.

    4. For every i and j:

           If word1[i - 1] == word2[j - 1]:
               dp[i][j] = dp[i - 1][j - 1]

           Otherwise:
               dp[i][j] = 1 + min(
                   dp[i - 1][j],
                   dp[i][j - 1]
               )

    5. Return:

           dp[m][n]

------------------------------------------------------------

Time Complexity:
----------------

There are:

    (m + 1) * (n + 1)

DP states.

Each state takes O(1) work.

Therefore:

    Time = O(m * n)

------------------------------------------------------------

Space Complexity:
-----------------

The DP table contains:

    (m + 1) * (n + 1)

values.

Therefore:

    Space = O(m * n)

------------------------------------------------------------

Core Idea:
----------

    Same characters
          |
          v
    Keep both
          |
          v
    dp[i - 1][j - 1]


    Different characters
          |
          v
    Delete from word1
          OR
    Delete from word2
          |
          v
    Take minimum
          |
          v
    dp[i][j] = 1 + min(
                    dp[i - 1][j],
                    dp[i][j - 1]
                )

------------------------------------------------------------

Code Mapping:
-------------

    dp[i][j]

    = answer for first i chars of word1
      and first j chars of word2


    dp[i - 1][j]

    = delete word1[i - 1]


    dp[i][j - 1]

    = delete word2[j - 1]


    dp[i - 1][j - 1]

    = both current characters are removed/handled together
      when they are equal
*/