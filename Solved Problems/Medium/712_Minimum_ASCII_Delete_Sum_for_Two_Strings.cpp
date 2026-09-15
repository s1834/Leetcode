class Solution {
    private:
        int m, n;
        vector<vector<int>> dp;
    
        int solve(string& word1, string& word2, int i, int j) {
            if(i == m) {
                int sum = 0;
                while(j != n) {
                    sum += word2[j];
                    j++;
                }
                return sum;
            } else if(j == n) {
                int sum = 0;
                while(i != m) {
                    sum += word1[i];
                    i++;
                }
                return sum;
            }
    
            if(dp[i][j] != -1) return dp[i][j];
            
            if(word1[i] == word2[j]) return dp[i][j] = solve(word1, word2, i + 1, j + 1);
            else {
                int remove1 = word1[i] + solve(word1, word2, i + 1, j);
                int remove2 = word2[j] + solve(word1, word2, i, j + 1);
                return dp[i][j] = min(remove1, remove2);
            }
        }
    
    public:
        int minimumDeleteSum(string s1, string s2) {
            m = s1.size();
            n = s2.size();
            dp.assign(m + 1, vector<int>(n + 1, -1));
            return solve(s1, s2, 0, 0);
        }
    };

/*
LeetCode 712. Minimum ASCII Delete Sum for Two Strings

Approach:
---------

We use Dynamic Programming with recursion + memoization.

The goal is to make word1 and word2 equal by deleting characters.
Unlike LeetCode 583, where every deletion has cost 1, here the
cost of deleting a character is its ASCII value.

Therefore, we want to minimize the TOTAL ASCII SUM of all deleted
characters.

------------------------------------------------------------

DP Definition:
--------------

    dp[i][j] = minimum ASCII delete sum required to make

               word1[i ... m-1]
               word2[j ... n-1]

               equal.

So:

    solve(word1, word2, i, j)

returns the minimum ASCII deletion cost for the remaining suffixes
starting at indices i and j.

The final answer is:

    solve(word1, word2, 0, 0)

------------------------------------------------------------

Base Case 1: word1 Is Finished
-------------------------------

    if(i == m)

word1 has no characters left.

The only way to make both strings equal is to delete every remaining
character from word2.

For example:

    word1 = ""
    word2 = "abc"

We must delete:

    'a' + 'b' + 'c'

So we calculate:

    sum = word2[j] + word2[j + 1] + ...

and return that ASCII sum.

------------------------------------------------------------

Base Case 2: word2 Is Finished
-------------------------------

    else if(j == n)

word2 has no characters left.

Therefore, every remaining character in word1 must be deleted.

For example:

    word1 = "abc"
    word2 = ""

We must delete:

    'a' + 'b' + 'c'

So we return the ASCII sum of the remaining characters in word1.

------------------------------------------------------------

Memoization:
------------

    if(dp[i][j] != -1)
        return dp[i][j];

The same pair of indices (i, j) can be reached through multiple
different deletion choices.

Instead of solving the same state repeatedly, we store its answer
in dp[i][j].

This reduces the exponential recursive solution to O(m * n) states.

------------------------------------------------------------

Case 1: Characters Are Equal
----------------------------

If:

    word1[i] == word2[j]

both characters can remain in the final strings because they already
match.

Therefore, we do not need to delete either character.

We simply move both pointers:

    dp[i][j] = solve(word1, word2, i + 1, j + 1);

For example:

    word1 = "sea"
    word2 = "eat"

If the current characters are both 'a':

    'a' == 'a'

we keep both and move to the next characters.

------------------------------------------------------------

Case 2: Characters Are Different
---------------------------------

If:

    word1[i] != word2[j]

the two current characters cannot both remain because they are
different.

We have exactly two useful choices:

    1. Delete word1[i]
    2. Delete word2[j]

We calculate the cost of both choices and take the minimum.

------------------------------------------------------------

Choice 1: Delete From word1
---------------------------

    int remove1 =
        word1[i] + solve(word1, word2, i + 1, j);

We delete word1[i].

The cost of this deletion is its ASCII value:

    word1[i]

Then we continue with:

    word1[i + 1 ...]
    word2[j ...]

Therefore:

    remove1 = ASCII(word1[i]) + remaining optimal cost

------------------------------------------------------------

Choice 2: Delete From word2
---------------------------

    int remove2 =
        word2[j] + solve(word1, word2, i, j + 1);

We delete word2[j].

The cost of this deletion is:

    word2[j]

Then we continue with:

    word1[i ...]
    word2[j + 1 ...]

Therefore:

    remove2 = ASCII(word2[j]) + remaining optimal cost

------------------------------------------------------------

Choose Minimum:
---------------

Since we want the minimum total ASCII deletion cost:

    dp[i][j] = min(remove1, remove2);

So:

    if(word1[i] != word2[j]) {
        int remove1 =
            word1[i] + solve(word1, word2, i + 1, j);

        int remove2 =
            word2[j] + solve(word1, word2, i, j + 1);

        return dp[i][j] = min(remove1, remove2);
    }

------------------------------------------------------------

Example:
--------

    word1 = "sea"
    word2 = "eat"

One possible solution is:

    "sea" -> "ea"
    "eat" -> "ea"

We delete:

    's' from word1
    't' from word2

ASCII values:

    's' = 115
    't' = 116

Total:

    115 + 116 = 231

So the answer is:

    231

The DP explores both possibilities whenever characters differ and
chooses the minimum total ASCII deletion cost.

------------------------------------------------------------

Why Do We Only Delete One Character When They Differ?
------------------------------------------------------------

Suppose:

    word1[i] != word2[j]

At least one of these two characters must be deleted.

There is no benefit to keeping both because they are different.

Therefore, the optimal solution must be one of:

    Delete word1[i]
            OR
    Delete word2[j]

The recursive calls then handle all remaining characters optimally.

------------------------------------------------------------

Why Can We Keep Both When They Are Equal?
------------------------------------------

If:

    word1[i] == word2[j]

we can keep both characters without performing any deletion.

Keeping matching characters is always optimal because deleting either
one would only add an unnecessary positive ASCII cost.

Therefore:

    solve(i + 1, j + 1)

is sufficient.

------------------------------------------------------------

Algorithm:
----------

    1. Start from i = 0 and j = 0.

    2. If word1 is finished:
           delete all remaining characters of word2.

    3. If word2 is finished:
           delete all remaining characters of word1.

    4. If current characters are equal:
           keep both and move i and j forward.

    5. If current characters are different:
           try deleting word1[i].
           try deleting word2[j].
           take the minimum ASCII cost.

    6. Memoize every (i, j) state.

------------------------------------------------------------

Important Difference From LeetCode 583:
-----------------------------------------

LeetCode 583:

    Every deletion costs 1.

So when characters differ:

    1 + min(remove from word1, remove from word2)

Here, deletion cost depends on the character.

For example:

    deleting 'a' costs 97
    deleting 'z' costs 122

Therefore:

    delete word1[i]:
        word1[i] + recursive answer

    delete word2[j]:
        word2[j] + recursive answer

This is why the transition uses the ASCII values directly.

------------------------------------------------------------

Time Complexity:
----------------

There are:

    m * n

possible (i, j) states.

Each state performs O(1) work apart from the base-case suffix sum.

Therefore, with the given implementation, the DP portion is:

    O(m * n)

------------------------------------------------------------

Space Complexity:
-----------------

The memoization table contains:

    (m + 1) * (n + 1)

states.

Additionally, recursion uses O(m + n) stack space.

Therefore:

    Space = O(m * n)

------------------------------------------------------------

Core Idea:
----------

        word1[i] == word2[j]
                 |
                 v
            Keep both
                 |
                 v
          solve(i + 1, j + 1)


        word1[i] != word2[j]
                 |
            +----+----+
            |         |
            v         v
      Delete word1  Delete word2
            |         |
      cost = word1[i] cost = word2[j]
            |         |
            +----+----+
                 |
                 v
              minimum

------------------------------------------------------------

Code Mapping:
-------------

    dp[i][j]

    = minimum ASCII deletion cost for
      word1[i...] and word2[j...]


    word1[i] + solve(i + 1, j)

    = delete current character from word1


    word2[j] + solve(i, j + 1)

    = delete current character from word2


    solve(i + 1, j + 1)

    = current characters are equal,
      so keep both
*/

// Version 2: Recursion + Memoization 2
class Solution {
    private:
        vector<vector<int>> dp;
    
        int solve(string& word1, string& word2, int m, int n) {
            if(m == 0) {
                int sum = 0;
                while(n != 0) {
                    sum += word2[n -1];
                    n--;
                }
                return sum;
            } else if(n == 0) {
                int sum = 0;
                while(m != 0) {
                    sum += word1[m - 1];
                    m--;
                }
                return sum;
            }
    
            if(dp[m][n] != -1) return dp[m][n];
            
            if(word1[m - 1] == word2[n - 1]) return dp[m][n] = solve(word1, word2, m - 1, n - 1);
            else {
                int remove1 = word1[m - 1] + solve(word1, word2, m - 1, n);
                int remove2 = word2[n - 1] + solve(word1, word2, m, n - 1);
                return dp[m][n] = min(remove1, remove2);
            }
        }
    
    public:
        int minimumDeleteSum(string s1, string s2) {
            int m = s1.size();
            int n = s2.size();
            dp.assign(m + 1, vector<int>(n + 1, -1));
            return solve(s1, s2, m, n);
        }
    };

/*
LeetCode 712. Minimum ASCII Delete Sum for Two Strings

Approach:
---------

We use Dynamic Programming with Recursion + Memoization.

The goal is to make word1 and word2 equal by deleting characters.

Unlike LeetCode 583, where every deletion costs 1, here the cost
of deleting a character is its ASCII value.

Therefore, we need to minimize the TOTAL ASCII value of all deleted
characters.

------------------------------------------------------------

DP Definition:
--------------

    dp[m][n] = minimum ASCII delete sum required to make

               first m characters of word1
               first n characters of word2

               equal.

Here m and n represent the LENGTHS of the prefixes we are
currently considering.

Therefore:

    solve(word1, word2, m, n)

means:

    Make word1[0 ... m-1]
    and word2[0 ... n-1]

    equal using minimum ASCII deletion cost.

The final answer is:

    solve(word1, word2, m, n)

------------------------------------------------------------

Base Case 1: word1 Is Empty
----------------------------

    if(m == 0)

There are no characters left in word1.

Therefore, every remaining character of word2 must be deleted.

For example:

    word1 = ""
    word2 = "abc"

We must delete:

    'a' + 'b' + 'c'

So we calculate the ASCII sum of the remaining characters:

    while(n != 0) {
        sum += word2[n - 1];
        n--;
    }

and return that sum.

For example:

    ASCII('a') = 97
    ASCII('b') = 98
    ASCII('c') = 99

Total:

    97 + 98 + 99 = 294

------------------------------------------------------------

Base Case 2: word2 Is Empty
----------------------------

    else if(n == 0)

There are no characters left in word2.

Therefore, every remaining character of word1 must be deleted.

For example:

    word1 = "abc"
    word2 = ""

We must delete all characters:

    'a' + 'b' + 'c'

So:

    while(m != 0) {
        sum += word1[m - 1];
        m--;
    }

returns the total ASCII deletion cost.

------------------------------------------------------------

Memoization:
------------

    if(dp[m][n] != -1)
        return dp[m][n];

The same state (m, n) can be reached through different sequences
of deletions.

Instead of solving the same state repeatedly, we store its answer
in:

    dp[m][n]

This avoids repeated calculations.

------------------------------------------------------------

Case 1: Last Characters Are Equal
---------------------------------

If:

    word1[m - 1] == word2[n - 1]

then the last characters of both prefixes are already equal.

We do not need to delete either character.

Therefore, we can keep both characters and solve the remaining
prefixes:

    solve(word1, word2, m - 1, n - 1)

So:

    dp[m][n] = dp[m - 1][n - 1]

For example:

    word1 = "abc"
    word2 = "xbc"

The last characters are:

    'c' == 'c'

So we keep both 'c's and solve:

    "ab" and "xb"

------------------------------------------------------------

Case 2: Last Characters Are Different
--------------------------------------

If:

    word1[m - 1] != word2[n - 1]

then the two characters cannot both remain in the final equal
strings.

At least one of them must be deleted.

There are two choices.

------------------------------------------------------------

Choice 1: Delete From word1
---------------------------

    int remove1 =
        word1[m - 1] + solve(word1, word2, m - 1, n);

We delete:

    word1[m - 1]

The cost of deleting it is its ASCII value:

    word1[m - 1]

After deleting it, we still need to make:

    first (m - 1) characters of word1
    first n characters of word2

equal.

Therefore:

    remove1 =
        ASCII(word1[m - 1])
        + solve(m - 1, n)

------------------------------------------------------------

Choice 2: Delete From word2
---------------------------

    int remove2 =
        word2[n - 1] + solve(word1, word2, m, n - 1);

We delete:

    word2[n - 1]

The cost is:

    word2[n - 1]

Then we need to make:

    first m characters of word1
    first (n - 1) characters of word2

equal.

Therefore:

    remove2 =
        ASCII(word2[n - 1])
        + solve(m, n - 1)

------------------------------------------------------------

Choose Minimum:
---------------

We want the minimum total ASCII deletion cost.

Therefore:

    dp[m][n] = min(remove1, remove2);

So:

    if(word1[m - 1] != word2[n - 1]) {

        int remove1 =
            word1[m - 1] + solve(word1, word2, m - 1, n);

        int remove2 =
            word2[n - 1] + solve(word1, word2, m, n - 1);

        return dp[m][n] = min(remove1, remove2);
    }

------------------------------------------------------------

Example:
--------

    word1 = "sea"
    word2 = "eat"

One optimal solution is:

    "sea" -> "ea"
    "eat" -> "ea"

We delete:

    's' from word1
    't' from word2

ASCII values:

    's' = 115
    't' = 116

Total:

    115 + 116 = 231

Therefore:

    answer = 231

The DP considers both deletion possibilities whenever the current
characters are different and chooses the minimum total cost.

------------------------------------------------------------

Why Do We Only Delete One Character When Characters Differ?
------------------------------------------------------------

Suppose:

    word1[m - 1] != word2[n - 1]

The two characters are different.

Since the final strings must be equal, these two characters cannot
both remain in their current positions.

Therefore, at least one of them must be deleted.

The two possible useful choices are:

    Delete word1[m - 1]
            OR
    Delete word2[n - 1]

We try both and choose the cheaper option.

The recursive calls then solve the remaining prefixes optimally.

------------------------------------------------------------

Why Do We Keep Both When Characters Are Equal?
-----------------------------------------------

If:

    word1[m - 1] == word2[n - 1]

both characters can remain because they already match.

Deleting either character would introduce an unnecessary positive
ASCII deletion cost.

Therefore, the optimal choice is to keep both:

    solve(m - 1, n - 1)

------------------------------------------------------------

Why Use m - 1 and n - 1?
-------------------------

Here m and n represent the NUMBER OF CHARACTERS being considered,
not the current zero-based indexes.

For example:

    m = 3

means we are considering:

    word1[0], word1[1], word1[2]

Therefore, the last character is:

    word1[m - 1]

After removing/handling that character, the remaining prefix has
length:

    m - 1

The same logic applies to word2.

------------------------------------------------------------

Algorithm:
----------

    1. Let m = word1.size() and n = word2.size().

    2. Create a memoization table:

           dp[m + 1][n + 1]

    3. Start from:

           solve(word1, word2, m, n)

    4. If m == 0:
           delete all remaining characters of word2.

    5. If n == 0:
           delete all remaining characters of word1.

    6. If the current characters are equal:
           keep both and solve:

               solve(m - 1, n - 1)

    7. Otherwise:
           try deleting the current character from word1
           and deleting the current character from word2.

    8. Take the minimum ASCII deletion cost.

    9. Memoize every state.

------------------------------------------------------------

Recursion Flow:
---------------

                solve(m, n)
                    |
             +------+------+
             |             |
        chars equal     chars different
             |             |
             v             v
       solve(m-1,n-1)   +--------+--------+
                        |                 |
                        v                 v
                  delete word1      delete word2
                        |                 |
                        v                 v
                  word1[m-1] +      word2[n-1] +
                  solve(m-1,n)      solve(m,n-1)
                        |                 |
                        +--------+--------+
                                 |
                                 v
                               min

------------------------------------------------------------

Difference From LeetCode 583:
-----------------------------

LeetCode 583 asks for the minimum NUMBER of deletions.

Therefore:

    delete word1 -> cost 1
    delete word2 -> cost 1

Here, the deletion cost depends on the character.

For example:

    deleting 'a' -> cost 97
    deleting 'z' -> cost 122

Therefore the transitions are:

    remove1 =
        word1[m - 1] + solve(m - 1, n)

    remove2 =
        word2[n - 1] + solve(m, n - 1)

------------------------------------------------------------

Time Complexity:
----------------

There are:

    (m + 1) * (n + 1)

different DP states.

Each state performs O(1) work, excluding the base-case sum.

Therefore:

    Time = O(m * n)

------------------------------------------------------------

Space Complexity:
-----------------

The memoization table contains:

    (m + 1) * (n + 1)

states.

The recursion stack can go up to:

    O(m + n)

Therefore:

    Space = O(m * n) + O(m + n)

which is:

    O(m * n)

------------------------------------------------------------

Core Idea:
----------

        word1[m-1] == word2[n-1]
                    |
                    v
               Keep both
                    |
                    v
             solve(m-1, n-1)


        word1[m-1] != word2[n-1]
                    |
              +-----+-----+
              |           |
              v           v
       Delete word1   Delete word2
              |           |
       cost = word1   cost = word2
              |           |
              +-----+-----+
                    |
                    v
                  minimum

------------------------------------------------------------

Code Mapping:
-------------

    dp[m][n]

    = minimum ASCII deletion cost for
      word1[0 ... m-1] and word2[0 ... n-1]


    word1[m - 1]

    = last character of the current word1 prefix


    word2[n - 1]

    = last character of the current word2 prefix


    solve(m - 1, n)

    = delete the last character of word1


    solve(m, n - 1)

    = delete the last character of word2


    solve(m - 1, n - 1)

    = current characters are equal,
      so keep both
*/

// Version 3: Bottom-Up
class Solution {
    public:
        int minimumDeleteSum(string s1, string s2) {
            int m = s1.size();
            int n = s2.size();
            vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
            // s2 is empty, so delete all characters from s1
            for(int i = 1; i <= m; i++) dp[i][0] = s1[i - 1] + dp[i - 1][0];
    
            // s1 is empty, so delete all characters from s2
            for(int j = 1; j <= n; j++) dp[0][j] = s2[j - 1] + dp[0][j - 1];
    
            for(int i = 1; i <= m; i++) {
                for(int j = 1; j <= n; j++) {
                    if(s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                    else {
                        int remove1 = s1[i - 1] + dp[i - 1][j];
                        int remove2 = s2[j - 1] + dp[i][j - 1];
                        dp[i][j] = min(remove1, remove2);
                    }
                }
            }
    
            return dp[m][n];
        }
    };

/*
LeetCode 712. Minimum ASCII Delete Sum for Two Strings

Approach:
---------

We use Dynamic Programming (DP).

The goal is to make s1 and s2 equal by deleting characters from either
string while minimizing the total ASCII value of all deleted characters.

------------------------------------------------------------

DP Definition:
--------------

    dp[i][j] = minimum ASCII delete sum required to make

               s1[0 ... i - 1]

               and

               s2[0 ... j - 1]

               equal.

So:

    dp[i][j]

represents the answer for the first i characters of s1 and the
first j characters of s2.

------------------------------------------------------------

Base Cases:
-----------

If s2 is empty:

    dp[i][0]

We have no characters in s2, so the only way to make both strings
equal is to delete all characters from s1.

Therefore:

    dp[i][0] = dp[i - 1][0] + ASCII(s1[i - 1])

For example:

    s1 = "ab"

    dp[1][0] = 'a'
    dp[2][0] = 'a' + 'b'

Similarly, if s1 is empty:

    dp[0][j]

we must delete all characters from s2.

Therefore:

    dp[0][j] = dp[0][j - 1] + ASCII(s2[j - 1])

------------------------------------------------------------

Transition:
-----------

For every pair of characters:

    s1[i - 1]
    s2[j - 1]

we have two cases.

------------------------------------------------------------

Case 1: Characters Are Equal
----------------------------

If:

    s1[i - 1] == s2[j - 1]

there is no reason to delete either character.

Both characters can remain in the final equal string.

So we simply solve the previous prefixes:

    dp[i][j] = dp[i - 1][j - 1]

Example:

    s1 = "a..."
    s2 = "a..."

Since both current characters are 'a', keep both.

    dp[i][j]
        |
        v
    dp[i-1][j-1]

------------------------------------------------------------

Case 2: Characters Are Different
---------------------------------

If:

    s1[i - 1] != s2[j - 1]

then the two characters cannot both remain as matching characters.

We have two choices:

    1. Delete s1[i - 1]
    2. Delete s2[j - 1]

------------------------------------------------------------

Choice 1: Delete Character From s1
-----------------------------------

Delete:

    s1[i - 1]

The cost of deleting it is its ASCII value.

After deleting it, we need to make:

    s1[0 ... i - 2]

and

    s2[0 ... j - 1]

equal.

Therefore:

    remove1 = s1[i - 1] + dp[i - 1][j]

------------------------------------------------------------

Choice 2: Delete Character From s2
-----------------------------------

Delete:

    s2[j - 1]

The cost is its ASCII value.

Then we need to make:

    s1[0 ... i - 1]

and

    s2[0 ... j - 2]

equal.

Therefore:

    remove2 = s2[j - 1] + dp[i][j - 1]

------------------------------------------------------------

Choose Minimum:
----------------

We want the minimum total deletion cost:

    dp[i][j] = min(remove1, remove2)

So the transition is:

    if(s1[i - 1] == s2[j - 1])
        dp[i][j] = dp[i - 1][j - 1];

    else {
        int remove1 = s1[i - 1] + dp[i - 1][j];
        int remove2 = s2[j - 1] + dp[i][j - 1];

        dp[i][j] = min(remove1, remove2);
    }

------------------------------------------------------------

Bottom-Up DP:
--------------

The table is filled from smaller prefixes to larger prefixes.

    dp[0][0] = 0

because two empty strings are already equal and require no deletion.

Then we initialize:

    dp[i][0]

and

    dp[0][j]

because one of the strings is empty.

After that, we calculate every:

    dp[i][j]

using previously calculated states.

Finally:

    dp[m][n]

contains the minimum ASCII deletion sum for the complete strings.

------------------------------------------------------------

Example:
---------

    s1 = "sea"
    s2 = "eat"

The common character 'e' can be kept.

Characters that need to be deleted can be:

    s1: 's'
    s2: 't'

ASCII values:

    's' = 115
    't' = 116

Total:

    115 + 116 = 231

Therefore:

    answer = 231

------------------------------------------------------------

Why Do We Only Consider Deleting One Character?
------------------------------------------------

When:

    s1[i - 1] != s2[j - 1]

at least one of these two characters must be deleted.

There is no benefit in keeping both because they are different
characters and cannot match each other at this position.

Therefore, we consider both possibilities:

    delete from s1
             OR
    delete from s2

and take the cheaper resulting solution.

------------------------------------------------------------

DP Table Meaning:
-----------------

For example:

        ""   a   b   c
    ""   0   a   a+b
    a    a   0   ...
    b   a+b  ...  ...
    c   ...  ...  ...

The first row represents:

    s1 = ""

The first column represents:

    s2 = ""

Every cell represents the minimum ASCII deletion cost for the
corresponding prefixes.

------------------------------------------------------------

Algorithm:
----------

    1. Let m = s1.size() and n = s2.size().

    2. Create a DP table:

           dp[m + 1][n + 1]

    3. Initialize dp[i][0] by deleting all characters from s1.

    4. Initialize dp[0][j] by deleting all characters from s2.

    5. For every i and j:

           If characters are equal:
               dp[i][j] = dp[i - 1][j - 1]

           Otherwise:
               delete s1[i - 1]
               OR
               delete s2[j - 1]

               take the minimum cost.

    6. Return:

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

We store the entire DP table:

    dp[m + 1][n + 1]

Therefore:

    Space = O(m * n)

------------------------------------------------------------

Core Idea:
----------

    Compare s1[i - 1] and s2[j - 1]

              |
        +-----+-----+
        |           |
      Same       Different
        |           |
        v           v
      Keep       Delete one
        |           |
        v       +---+---+
    dp[i-1][j-1] |     |
                 v     v
             Delete   Delete
              s1       s2
               |       |
               v       v
            dp[i-1][j] dp[i][j-1]
                 \     /
                  \   /
                   min
                    |
                    v
                 dp[i][j]

The final answer is:

    dp[m][n]
*/