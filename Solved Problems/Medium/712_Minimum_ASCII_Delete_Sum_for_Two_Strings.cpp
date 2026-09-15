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