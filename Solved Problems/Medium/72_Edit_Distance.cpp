// Version 2: Recursion + Memoization 1
// class Solution {
//     private:
//         int n, m;
//         vector<vector<int>> dp;
    
//         int solve(string& word1, string& word2, int i, int j) {
//             if(i == n) return m - j; // insert in word1
//             else if(j == m) return n - i; // delete from word2
            
//             if(dp[i][j] != -1) return dp[i][j];
    
//             if(word1[i] == word2[j]) return dp[i][j] = solve(word1, word2, i + 1, j + 1);
//             else {
//                 int ins = 1 + solve(word1, word2, i, j + 1);
//                 int del = 1 + solve(word1, word2, i + 1, j);
//                 int rep = 1 + solve(word1, word2, i + 1, j + 1);
    
//                 return dp[i][j] = min({ins, del, rep});
//             }
    
//             return -1;
//         }
    
//     public:
//         int minDistance(string word1, string word2) {
//             n = word1.size();
//             m = word2.size();
//             dp.assign(n, vector<int>(m, -1));
//             return solve(word1, word2, 0, 0);
//         }
//     };

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

// Version 2: Recursion + Memoization 2
// class Solution {
//     private:
//         vector<vector<int>> dp;
    
//         int solve(string& word1, string& word2, int n, int m) {
//             if(n == 0 || m == 0) return n + m; 
            
//             if(dp[n][m] != -1) return dp[n][m];
    
//             if(word1[n - 1] == word2[m - 1]) return dp[n][m] = solve(word1, word2, n - 1, m - 1);
//             else {
//                 int ins = 1 + solve(word1, word2, n, m - 1);
//                 int del = 1 + solve(word1, word2, n - 1, m);
//                 int rep = 1 + solve(word1, word2, n - 1, m - 1);
    
//                 return dp[n][m] = min({ins, del, rep});
//             }
    
//             return -1;
//         }
    
//     public:
//         int minDistance(string word1, string word2) {
//             int n = word1.size();
//             int m = word2.size();
//             dp.assign(n + 1, vector<int>(m + 1, -1));
//             return solve(word1, word2, n, m);
//         }
//     };

/*
LeetCode 72. Edit Distance

Approach:
---------

We use Dynamic Programming with Memoization (Top-Down DP).

The goal is to convert word1 into word2 using the minimum number
of operations.

We are allowed 3 operations:

    1. Insert a character
    2. Delete a character
    3. Replace a character

Instead of working with the strings themselves, we define the DP
state using how many characters are still remaining in each string.

------------------------------------------------------------

DP State:
---------

    dp[n][m]

represents the minimum number of operations required to convert:

    word1[0 ... n-1]

into:

    word2[0 ... m-1]

Here:

    n = number of characters currently considered from word1
    m = number of characters currently considered from word2

So the recursive function:

    solve(word1, word2, n, m)

returns the minimum edit distance between the first n characters
of word1 and the first m characters of word2.

------------------------------------------------------------

Base Case:
----------

    if(n == 0 || m == 0) return n + m;

If one of the strings becomes empty, the answer is straightforward.

Case 1:
-------

    n == 0

word1 is empty, but word2 still has m characters.

The only way to create word2 is to insert all m characters.

Therefore:

    operations = m

Case 2:
-------

    m == 0

word2 is empty, but word1 still has n characters.

The only way to convert word1 into an empty string is to delete
all n characters.

Therefore:

    operations = n

Both cases can be represented together as:

    n + m

because one of n or m is zero.

------------------------------------------------------------

Memoization:
------------

    if(dp[n][m] != -1) return dp[n][m];

There can be many different recursive paths that reach the same
state (n, m).

Without memoization, the same state would be calculated repeatedly.

We store the answer for every state in:

    dp[n][m]

If the value has already been calculated, return it immediately.

This reduces the number of states to:

    O(n * m)

------------------------------------------------------------

Case 1: Characters Are Equal
----------------------------

    if(word1[n - 1] == word2[m - 1])

The last characters of the current prefixes are already equal.

For example:

    word1 = "horse"
    word2 = "roses"

If:

    word1[n - 1] == word2[m - 1]

we do not need any operation on these characters.

We can simply ignore the matching characters and solve the
remaining prefixes:

    solve(word1, word2, n - 1, m - 1)

Therefore:

    dp[n][m] = solve(n - 1, m - 1)

------------------------------------------------------------

Case 2: Characters Are Different
---------------------------------

If:

    word1[n - 1] != word2[m - 1]

then we have 3 possible operations.

We calculate the cost of all three and take the minimum.

------------------------------------------------------------

1. INSERT
----------

    int ins = 1 + solve(word1, word2, n, m - 1);

We want to insert:

    word2[m - 1]

into word1.

After inserting that character, the last character of word2
has been matched.

Therefore, we move only in word2:

    n stays the same
    m decreases by 1

So:

    insert = 1 + solve(n, m - 1)

The +1 represents the insertion operation itself.

Example:

    word1 = "abc"
    word2 = "abcd"

We can insert 'd' into word1.

------------------------------------------------------------

2. DELETE
----------

    int del = 1 + solve(word1, word2, n - 1, m);

We delete:

    word1[n - 1]

from word1.

After deleting it, we move only in word1:

    n decreases by 1
    m stays the same

So:

    delete = 1 + solve(n - 1, m)

The +1 represents the deletion operation.

Example:

    word1 = "abcd"
    word2 = "abc"

We can delete 'd' from word1.

------------------------------------------------------------

3. REPLACE
-----------

    int rep = 1 + solve(word1, word2, n - 1, m - 1);

Since the two characters are different, we can replace:

    word1[n - 1]

with:

    word2[m - 1]

After replacing them, both characters are matched.

Therefore, move in both strings:

    n decreases by 1
    m decreases by 1

So:

    replace = 1 + solve(n - 1, m - 1)

The +1 represents the replacement operation.

------------------------------------------------------------

Choosing the Minimum:
----------------------

We have three possible operations:

    ins = 1 + solve(n, m - 1)

    del = 1 + solve(n - 1, m)

    rep = 1 + solve(n - 1, m - 1)

We choose the operation that requires the minimum total number
of operations:

    dp[n][m] = min({ins, del, rep});

------------------------------------------------------------

Why Does Insert Use (n, m - 1)?
-------------------------------

This is an important part of the problem.

Suppose:

    word1 = "abc"
    word2 = "abcd"

We need to insert 'd'.

After inserting 'd', the last character of word2 is handled,
but word1 itself has not lost a character.

Therefore:

    word1 -> n remains the same
    word2 -> m decreases

So:

    insert -> solve(n, m - 1)

------------------------------------------------------------

Why Does Delete Use (n - 1, m)?
-------------------------------

Suppose:

    word1 = "abcd"
    word2 = "abc"

We delete 'd' from word1.

The character from word2 has not been matched yet, so:

    word1 -> n decreases
    word2 -> m remains the same

Therefore:

    delete -> solve(n - 1, m)

------------------------------------------------------------

Why Does Replace Use (n - 1, m - 1)?
------------------------------------

Suppose:

    word1 = "abc"
    word2 = "abd"

The last characters are:

    c != d

We can replace:

    c -> d

After that replacement, both characters are handled.

Therefore:

    word1 -> n - 1
    word2 -> m - 1

So:

    replace -> solve(n - 1, m - 1)

------------------------------------------------------------

Example:
--------

    word1 = "horse"
    word2 = "ros"

We start with:

    solve("horse", "ros", 5, 3)

At every state:

    If last characters are equal:
        move diagonally

    If last characters are different:
        try:

            INSERT
            DELETE
            REPLACE

        and take the minimum.

The recursion eventually reaches states where one string becomes
empty, which gives the remaining number of required insertions
or deletions.

------------------------------------------------------------

Bottom-Up Interpretation:
-------------------------

The same DP can be visualized as a table.

        ""   r   o   s
    ""   0   1   2   3
    h    1   ?   ?   ?
    o    2   ?   ?   ?
    r    3   ?   ?   ?
    s    4   ?   ?   ?
    e    5   ?   ?   ?

The first row represents converting an empty word1 into prefixes
of word2.

Therefore:

    0 1 2 3 ...

The first column represents converting prefixes of word1 into
an empty word2.

Therefore:

    0
    1
    2
    3
    ...

For every other cell:

    if characters are equal:

        dp[i][j] = dp[i - 1][j - 1]

    otherwise:

        dp[i][j] = 1 + min(
            dp[i][j - 1],       // insert
            dp[i - 1][j],       // delete
            dp[i - 1][j - 1]    // replace
        )

Our recursive solution is simply calculating this same table
from the top-right side using memoization.

------------------------------------------------------------

Algorithm:
----------

    1. Store the sizes of both strings.

    2. Create a DP table initialized with -1.

    3. Start recursion from:

           solve(word1, word2, n, m)

    4. If either string becomes empty:
           return n + m.

    5. If the current characters are equal:
           solve(n - 1, m - 1)

    6. Otherwise calculate:

           insert
           delete
           replace

    7. Take the minimum of the three.

    8. Store the result in dp[n][m].

------------------------------------------------------------

Time Complexity:
----------------

There are:

    n * m

different DP states.

Each state performs only constant work apart from the recursive
calls.

Therefore:

    O(n * m)

------------------------------------------------------------

Space Complexity:
-----------------

DP table:

    O(n * m)

Recursive call stack:

    O(n + m)

Therefore overall:

    O(n * m)

(the DP table dominates).

------------------------------------------------------------

Core Idea:
----------

At every position where the characters are different, we have
exactly three choices:

                 Different characters
                         |
             +-----------+-----------+
             |           |           |
           Insert      Delete      Replace
             |           |           |
          (n,m-1)     (n-1,m)    (n-1,m-1)
             |           |           |
             +-----------+-----------+
                         |
                      minimum

If the characters are already equal:

                 Same characters
                        |
                        v
                   (n-1, m-1)

The answer is:

    minimum number of insertions,
    deletions, and replacements
    required to transform word1 into word2.
*/

// Version 3: Bottom-Up
class Solution {
    public:
        int minDistance(string word1, string word2) {
            int n = word1.size();
            int m = word2.size();
            vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    
            for(int i = 0; i <= n; i++) {
                for(int j = 0; j <= m; j++) {
                    if(i == 0 || j == 0) dp[i][j] = i + j;
                    else if(word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                    else {
                        int ins = 1 + dp[i][j - 1];
                        int del = 1 + dp[i - 1][j];
                        int rep = 1 + dp[i - 1][j - 1];
    
                        dp[i][j] = min({ins, del, rep});
                    }
                }
            }
    
            return dp[n][m];
        }
    };

/*
LeetCode 72. Edit Distance

Version 3: Bottom-Up Dynamic Programming

Approach:
---------

We use Dynamic Programming to find the minimum number of
operations required to convert word1 into word2.

We are allowed 3 operations:

    1. Insert a character
    2. Delete a character
    3. Replace a character

Instead of using recursion, we build the entire DP table
iteratively from smaller subproblems to larger subproblems.

------------------------------------------------------------

DP Definition:
--------------

    dp[i][j]

represents the minimum number of operations required to convert:

    word1[0 ... i-1]

into:

    word2[0 ... j-1]

In other words:

    i = number of characters considered from word1
    j = number of characters considered from word2

Therefore:

    dp[n][m]

contains the answer for the complete strings.

------------------------------------------------------------

Why do we use n + 1 and m + 1?
------------------------------

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

We use n + 1 rows and m + 1 columns because we also need to
represent the case where one of the strings is empty.

For example:

    dp[0][0]

means:

    "" -> ""

    dp[i][0]

means:

    word1[0 ... i-1] -> ""

    dp[0][j]

means:

    "" -> word2[0 ... j-1]

The extra row and column represent these empty-string cases.

------------------------------------------------------------

Base Cases:
-----------

    if(i == 0 || j == 0)
        dp[i][j] = i + j;

If one of the strings is empty, the answer is simply the number
of remaining characters.

Case 1:
-------

    i == 0

word1 is empty.

To create word2 with j characters, we need to insert all j
characters.

Therefore:

    dp[0][j] = j

Case 2:
-------

    j == 0

word2 is empty.

To convert word1 with i characters into an empty string, we need
to delete all i characters.

Therefore:

    dp[i][0] = i

Both cases are represented by:

    i + j

because one of i or j is zero.

------------------------------------------------------------

When Characters Are Equal:
---------------------------

    else if(word1[i - 1] == word2[j - 1])
        dp[i][j] = dp[i - 1][j - 1];

The current characters are:

    word1[i - 1]
    word2[j - 1]

If they are equal, we do not need any operation.

For example:

    word1 = "abc"
    word2 = "adc"

When processing the last character:

    'c' == 'c'

So the last characters can be matched directly.

We simply solve the remaining prefixes:

    word1[0 ... i-2]
    word2[0 ... j-2]

Therefore:

    dp[i][j] = dp[i - 1][j - 1]

Notice that there is NO +1 because no operation is required.

------------------------------------------------------------

When Characters Are Different:
------------------------------

If:

    word1[i - 1] != word2[j - 1]

we have three possible operations:

    Insert
    Delete
    Replace

We calculate the cost of all three and take the minimum.

------------------------------------------------------------

1. INSERT
----------

    int ins = 1 + dp[i][j - 1];

We want to insert the character:

    word2[j - 1]

into word1.

After inserting it, the current character of word2 is matched,
but we have not removed a character from word1.

Therefore:

    i remains the same
    j decreases by 1

So:

    insert = 1 + dp[i][j - 1]

The +1 represents the insertion operation.

Example:

    word1 = "abc"
    word2 = "abcd"

We can insert 'd' into word1.

------------------------------------------------------------

2. DELETE
----------

    int del = 1 + dp[i - 1][j];

We delete the current character:

    word1[i - 1]

from word1.

After deleting it, we still need to match the same number of
characters from word2.

Therefore:

    i decreases by 1
    j remains the same

So:

    delete = 1 + dp[i - 1][j]

The +1 represents the deletion operation.

Example:

    word1 = "abcd"
    word2 = "abc"

We can delete 'd' from word1.

------------------------------------------------------------

3. REPLACE
-----------

    int rep = 1 + dp[i - 1][j - 1];

The current characters are different, so we can replace:

    word1[i - 1]

with:

    word2[j - 1]

After replacing them, both current characters are handled.

Therefore:

    i decreases by 1
    j decreases by 1

So:

    replace = 1 + dp[i - 1][j - 1]

The +1 represents the replacement operation.

------------------------------------------------------------

Choosing the Minimum:
----------------------

After calculating all three possibilities:

    int ins = 1 + dp[i][j - 1];
    int del = 1 + dp[i - 1][j];
    int rep = 1 + dp[i - 1][j - 1];

we choose the operation requiring the minimum number of
operations:

    dp[i][j] = min({ins, del, rep});

------------------------------------------------------------

Bottom-Up Order:
----------------

We iterate:

    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= m; j++)

This works because dp[i][j] depends only on already calculated
smaller states:

    dp[i - 1][j]       -> previous row
    dp[i][j - 1]       -> previous column
    dp[i - 1][j - 1]   -> diagonal

So when calculating dp[i][j], all required states have already
been calculated.

------------------------------------------------------------

DP Table Example:
-----------------

Suppose:

    word1 = "abc"
    word2 = "ac"

The DP table represents:

             ""   a   c
         ""   0   1   2
         a    1   0   1
         b    2   1   1
         c    3   2   1

For example:

    dp[1][1]

compares:

    'a' with 'a'

They are equal, so:

    dp[1][1] = dp[0][0] = 0

Now:

    dp[2][2]

compares:

    'b' with 'c'

They are different.

We try:

    Insert:
        1 + dp[2][1]

    Delete:
        1 + dp[1][2]

    Replace:
        1 + dp[1][1]

and choose the minimum.

------------------------------------------------------------

Important Index Difference:
----------------------------

The DP indices represent LENGTHS, while string indices are
0-based.

Therefore, when we are at:

    dp[i][j]

the corresponding characters are:

    word1[i - 1]
    word2[j - 1]

NOT:

    word1[i]
    word2[j]

This is because row 0 and column 0 represent the empty string.

------------------------------------------------------------

Algorithm:
----------

    1. Let n = word1.size() and m = word2.size().

    2. Create a DP table of size:

           (n + 1) x (m + 1)

    3. Fill the first row and first column:

           dp[i][0] = i
           dp[0][j] = j

       because converting to/from an empty string requires
       only insertions or deletions.

    4. For every remaining cell:

       If characters are equal:

           dp[i][j] = dp[i - 1][j - 1]

       Otherwise:

           insert  = 1 + dp[i][j - 1]
           delete  = 1 + dp[i - 1][j]
           replace = 1 + dp[i - 1][j - 1]

           dp[i][j] = min(insert, delete, replace)

    5. Return:

           dp[n][m]

------------------------------------------------------------

Why Bottom-Up DP?
-----------------

The previous recursive solution used:

    solve(n, m)

and recursively calculated smaller states.

Here, we calculate those smaller states first and directly store
their results in the table.

So instead of:

    solve(n, m)
       |
       +--> solve(n-1, m)
       +--> solve(n, m-1)
       +--> solve(n-1, m-1)

we build:

    smaller states
          |
          v
    larger states
          |
          v
       dp[n][m]

This avoids recursion and makes the DP dependencies explicit.

------------------------------------------------------------

Time Complexity:
----------------

There are:

    (n + 1) * (m + 1)

DP states.

Each state performs constant work.

Therefore:

    O(n * m)

------------------------------------------------------------

Space Complexity:
-----------------

The DP table contains:

    (n + 1) * (m + 1)

elements.

Therefore:

    O(n * m)

------------------------------------------------------------

Core Idea:
----------

                word1[i-1] == word2[j-1]
                         |
                         v
                  No operation
                         |
                         v
                  dp[i-1][j-1]


                word1[i-1] != word2[j-1]
                         |
              +----------+----------+
              |          |          |
              v          v          v
           Insert     Delete     Replace
              |          |          |
          dp[i][j-1] dp[i-1][j] dp[i-1][j-1]
              |          |          |
              +----------+----------+
                         |
                         v
                       +1
                         |
                         v
                    Take minimum


The final answer is:

    dp[n][m]

which represents the minimum number of insertions, deletions,
and replacements required to transform word1 into word2.
*/