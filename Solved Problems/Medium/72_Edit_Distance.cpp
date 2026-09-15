class Solution {
    private:
        int n, m;
        vector<vector<int>> dp;
    
        int solve(string& word1, string& word2, int i, int j) {
            if(i == n) return m - j; // insert in word1
            else if(j == m) return n - i; // delete from word2
            
            if(dp[i][j] != -1) return dp[i][j];
    
            if(word1[i] == word2[j]) return dp[i][j] = solve(word1, word2, i + 1, j + 1);
            else {
                int ins = 1 + solve(word1, word2, i, j + 1);
                int del = 1 + solve(word1, word2, i + 1, j);
                int rep = 1 + solve(word1, word2, i + 1, j + 1);
    
                return dp[i][j] = min({ins, del, rep});
            }
    
            return -1;
        }
    
    public:
        int minDistance(string word1, string word2) {
            n = word1.size();
            m = word2.size();
            dp.assign(n, vector<int>(m, -1));
            return solve(word1, word2, 0, 0);
        }
    };

/*
LeetCode 72. Edit Distance

Approach:
---------

We use Dynamic Programming + Recursion + Memoization.

The goal is to convert word1 into word2 using the minimum number
of operations.

The three allowed operations are:

    1. Insert a character
    2. Delete a character
    3. Replace a character

We define a DP state based on two pointers:

    i -> current index in word1
    j -> current index in word2

The state:

    dp[i][j]

stores the minimum number of operations required to convert:

    word1[i...]

into:

    word2[j...]

------------------------------------------------------------

solve():
---------

    solve(word1, word2, i, j)

At every state, we compare:

    word1[i]
    word2[j]

There are two main cases:

    1. Both characters are the same.
    2. Both characters are different.

------------------------------------------------------------

Base Case 1: word1 is exhausted
--------------------------------

    if(i == n) return m - j;

If we have reached the end of word1 but word2 still has
characters remaining, the only possible operation is to insert
those remaining characters into word1.

For example:

    word1 = "abc"
    word2 = "abcdef"

If:

    i == 3
    j == 3

then the remaining part of word2 is:

    "def"

We need 3 insertions.

Therefore:

    m - j

operations are required.

------------------------------------------------------------

Base Case 2: word2 is exhausted
--------------------------------

    else if(j == m) return n - i;

If word2 is finished but word1 still has characters remaining,
we need to delete all remaining characters from word1.

For example:

    word1 = "abcdef"
    word2 = "abc"

If:

    i == 3
    j == 3

the remaining part of word1 is:

    "def"

We need 3 deletions.

Therefore:

    n - i

operations are required.

------------------------------------------------------------

Memoization:
------------

    if(dp[i][j] != -1) return dp[i][j];

If we have already calculated the answer for state (i, j),
return it directly.

This prevents the same subproblem from being solved multiple
times.

------------------------------------------------------------

Case 1: Characters are Equal
-----------------------------

    if(word1[i] == word2[j])

If the current characters are already equal, we do not need
any operation.

We simply move both pointers forward:

    i + 1
    j + 1

Therefore:

    dp[i][j] = solve(word1, word2, i + 1, j + 1);

Example:

    word1 = "horse"
    word2 = "house"

At:

    i = 0 -> 'h'
    j = 0 -> 'h'

Both characters are equal.

So we keep 'h' and move forward.

------------------------------------------------------------

Case 2: Characters are Different
--------------------------------

If:

    word1[i] != word2[j]

we have three possible operations:

    1. Insert
    2. Delete
    3. Replace

We calculate the cost of all three and choose the minimum.

------------------------------------------------------------

1. INSERT
----------

    int ins = 1 + solve(word1, word2, i, j + 1);

We insert word2[j] into word1.

The important point is that after inserting the required
character, we have matched word2[j], but word1[i] is still
available.

Therefore:

    i stays the same
    j moves forward

So:

    solve(i, j + 1)

Example:

    word1 = "abc"
    word2 = "axbc"

At:

    word1[i] = 'b'
    word2[j] = 'x'

We can insert 'x' before 'b'.

After insertion, 'x' is handled, while 'b' still needs
processing.

------------------------------------------------------------

2. DELETE
---------

    int del = 1 + solve(word1, word2, i + 1, j);

We delete word1[i].

After deleting it, the current character of word1 is gone,
but word2[j] still needs to be matched.

Therefore:

    i moves forward
    j stays the same

So:

    solve(i + 1, j)

Example:

    word1 = "abc"
    word2 = "ac"

At:

    word1[i] = 'b'
    word2[j] = 'c'

We can delete 'b'.

Now we continue from the next character of word1.

------------------------------------------------------------

3. REPLACE
----------

    int rep = 1 + solve(word1, word2, i + 1, j + 1);

We replace word1[i] with word2[j].

After replacing the character, both current characters are
considered matched.

Therefore:

    i moves forward
    j moves forward

So:

    solve(i + 1, j + 1)

Example:

    word1 = "abc"
    word2 = "adc"

At:

    word1[i] = 'b'
    word2[j] = 'd'

We can replace:

    b -> d

using one operation.

Then both pointers move forward.

------------------------------------------------------------

Why +1 for every operation?
----------------------------

Each of INSERT, DELETE, and REPLACE performs exactly one
operation immediately.

Therefore:

    insert = 1 + remaining operations
    delete = 1 + remaining operations
    replace = 1 + remaining operations

We take the minimum:

    dp[i][j] = min({ins, del, rep});

------------------------------------------------------------

Why don't we need an operation when characters match?
--------------------------------------------------------

If:

    word1[i] == word2[j]

the current characters already match.

Performing an operation would be unnecessary.

Therefore, we simply move:

    i++
    j++

without increasing the operation count.

------------------------------------------------------------

Example:
--------

Convert:

    word1 = "horse"
    word2 = "ros"

We start with:

    solve(0, 0)

Comparisons:

    h vs r -> different

So we have three choices:

    INSERT
    DELETE
    REPLACE

The recursion explores all possibilities.

Whenever characters match, both pointers move forward without
adding any cost.

The DP eventually finds the minimum number of operations.

For this example, the answer is:

    3

One possible sequence is:

    horse
      ↓
    rorse      replace h -> r
      ↓
    rose       delete r
      ↓
    ros        delete e

Therefore:

    Edit Distance = 3

------------------------------------------------------------

DP State Visualization:
-----------------------

    dp[i][j]

means:

    Minimum operations required to convert
    word1[i...n-1] -> word2[j...m-1]

For example:

                    word2
                 j
                 ↓
             r   o   s
          ----------------
    h  |   dp  dp  dp
    o  |   dp  dp  dp
    r  |   dp  dp  dp
    s  |   dp  dp  dp
    e  |   dp  dp  dp
          ^
          i
        word1

Each state depends on at most three neighboring states:

                    dp[i][j]
                   /    |    \
                  /     |     \
              INSERT  DELETE  REPLACE
                |       |       |
                v       v       v
          dp[i][j+1] dp[i+1][j] dp[i+1][j+1]

------------------------------------------------------------

Important Pointer Movement:
---------------------------

INSERT:

    solve(i, j + 1)

Because word2[j] is inserted/matched, but word1[i] remains.

DELETE:

    solve(i + 1, j)

Because word1[i] is removed, but word2[j] remains.

REPLACE:

    solve(i + 1, j + 1)

Because both current characters are now matched.

MATCH:

    solve(i + 1, j + 1)

Because both current characters already match.

------------------------------------------------------------

Overall Algorithm:
------------------

    1. Store n = word1.size() and m = word2.size().

    2. Create a DP table initialized with -1.

    3. Start recursion from:

           solve(word1, word2, 0, 0)

    4. If word1 is exhausted:
           insert all remaining characters of word2.

    5. If word2 is exhausted:
           delete all remaining characters of word1.

    6. If current characters match:
           move both pointers forward.

    7. Otherwise calculate:

           INSERT
           DELETE
           REPLACE

    8. Take the minimum of the three operations.

    9. Store the result in dp[i][j].

------------------------------------------------------------

Time Complexity:
----------------

There are:

    n × m

possible DP states.

Each state is calculated only once because of memoization.

Each state performs O(1) work apart from recursive calls.

Therefore:

    O(n × m)

Time Complexity.

------------------------------------------------------------

Space Complexity:
-----------------

The DP table contains:

    n × m

states.

Therefore:

    O(n × m)

space is used for memoization.

The recursion stack can go up to:

    O(n + m)

in the worst case.

Therefore, total auxiliary space is:

    O(n × m)

------------------------------------------------------------

Core Idea:
----------

At every pair of positions (i, j):

                word1[i] != word2[j]
                         |
          +--------------+--------------+
          |              |              |
          v              v              v
       INSERT          DELETE        REPLACE
          |              |              |
          v              v              v
      (i, j+1)       (i+1, j)       (i+1, j+1)
          |              |              |
          +--------------+--------------+
                         |
                         v
                       MIN

If:

                word1[i] == word2[j]
                         |
                         v
                   (i+1, j+1)

No operation is required.

The DP finds the minimum number of INSERT, DELETE, and REPLACE
operations required to transform word1 into word2.
*/