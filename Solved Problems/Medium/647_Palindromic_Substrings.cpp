class Solution {
    private:
        int n;
        vector<vector<int>> dp;
    
        bool isPalindrome(string& s, int i, int j) {
            while(i < j) {
                if(s[i] != s[j]) return false;
                i++;
                j--;
            }
            return true;
        }
    
        int solve(string& s, int i, int j) {
            if(j >= n) return 0;
    
            if(dp[i][j] != -1) return 0;
    
            int take = isPalindrome(s, i, j) ? 1 : 0;
            int left = solve(s, i + 1, (i + 1 > j) ? j + 1 : j);
            int right = solve(s, i, j + 1);
    
            return dp[i][j] = take + left + right;
        }
    
    public:
        int countSubstrings(string s) {
            n = s.size();
            dp.assign(n + 1, vector<int>(n + 1, -1));
            return solve(s, 0, 0);
        }
    };

/*
LeetCode 647. Palindromic Substrings

Approach:
---------

We use Dynamic Programming + Recursion (Memoization).

The goal is to count all substrings of s that are palindromes.

A substring is identified by two indices:

    i = starting index
    j = ending index

So the recursive function:

    solve(s, i, j)

represents the number of palindromic substrings that can be counted
while considering the current range [i ... j].

------------------------------------------------------------

Palindrome Check:
-----------------

We use:

    isPalindrome(s, i, j)

to check whether the substring:

    s[i ... j]

is a palindrome.

We compare characters from both ends:

    s[i] and s[j]

If they are different:

    return false;

Otherwise, move both pointers towards the center:

    i++;
    j--;

If all characters match, the substring is a palindrome.

Example:

    s = "abcba"

    a b c b a
    ^       ^

    a == a
      ^   ^
      b == b
        ^
        c

Therefore:

    "abcba" is a palindrome.

------------------------------------------------------------

DP State:
---------

    dp[i][j]

stores the result for the state:

    solve(s, i, j)

This avoids recalculating the same state multiple times.

Initially:

    dp[i][j] = -1

means that the state has not been calculated yet.

------------------------------------------------------------

Base Case:
----------

If:

    j >= n

we have reached the end of the string.

There are no more substrings to consider:

    if(j >= n) return 0;

------------------------------------------------------------

Memoization:
------------

If the current state has already been calculated:

    if(dp[i][j] != -1)
        return 0;

The intended logic here is to return the stored DP value.

It should be:

    if(dp[i][j] != -1)
        return dp[i][j];

Returning 0 would discard the previously calculated answer and
would make memoization incorrect.

------------------------------------------------------------

Take:
-----

For the current substring:

    s[i ... j]

we first check whether it is a palindrome.

    int take = isPalindrome(s, i, j) ? 1 : 0;

If it is a palindrome:

    take = 1

because this substring contributes one palindromic substring.

Otherwise:

    take = 0

Example:

    s = "aba"

For:

    i = 0, j = 2

we have:

    s[0 ... 2] = "aba"

which is a palindrome.

Therefore:

    take = 1

------------------------------------------------------------

Left Transition:
----------------

We move the starting index forward:

    i + 1

The ending index remains j.

However, when:

    i + 1 > j

the starting index would move past the ending index.

In that case, we move j forward as well:

    (i + 1 > j) ? j + 1 : j

So:

    left = solve(
        s,
        i + 1,
        (i + 1 > j) ? j + 1 : j
    );

This allows us to continue considering the next valid substring
ranges.

------------------------------------------------------------

Right Transition:
-----------------

We can also move the ending index forward:

    j + 1

So:

    right = solve(s, i, j + 1);

This expands the current range towards the right.

------------------------------------------------------------

Combining the Results:
----------------------

For the current state:

    solve(i, j)

we have:

    take
        -> whether s[i ... j] itself is a palindrome

    left
        -> result after moving i forward

    right
        -> result after moving j forward

Therefore:

    dp[i][j] = take + left + right;

and we return:

    dp[i][j]

------------------------------------------------------------

Important DP Idea:
------------------

The recursion explores substrings by moving:

    i -> i + 1

and:

    j -> j + 1

while checking every relevant [i, j] range.

For every range:

    [i ... j]

we ask:

    Is s[i ... j] a palindrome?

If yes, add 1.

Then continue exploring the remaining ranges.

------------------------------------------------------------

Example:
--------

    s = "aaa"

All substrings are:

    "a"       -> palindrome
    "a"       -> palindrome
    "a"       -> palindrome

    "aa"      -> palindrome
    "aa"      -> palindrome

    "aaa"     -> palindrome

Total:

    6

So the answer is:

    6

The recursion checks each relevant range and adds 1 whenever
isPalindrome() returns true.

------------------------------------------------------------

Example of Take:
----------------

For:

    s = "abc"

Consider:

    i = 0, j = 1

Substring:

    "ab"

Since:

    'a' != 'b'

we get:

    take = 0

But for:

    i = 0, j = 0

substring:

    "a"

Every single character is a palindrome, so:

    take = 1

Similarly:

    "b"
    "c"

are also palindromes.

------------------------------------------------------------

Why Every Single Character Counts:
-----------------------------------

Any substring containing exactly one character is automatically
a palindrome.

For example:

    "a"

reads the same forwards and backwards.

Therefore, for a string of length n, there are always at least:

    n

palindromic substrings.

Longer palindromes are added on top of these.

------------------------------------------------------------

Algorithm:
----------

    1. Store the string length in n.

    2. Create a memoization table:

           dp[n + 1][n + 1]

       initialized with -1.

    3. Start recursion from:

           solve(s, 0, 0)

    4. For every [i, j]:

           Check whether s[i ... j] is a palindrome.

    5. If it is a palindrome, add 1.

    6. Continue exploring by moving:

           i -> i + 1

       and:

           j -> j + 1

    7. Store the result in dp[i][j].

    8. Return the total count.

------------------------------------------------------------

Time Complexity:
----------------

There are O(n²) possible (i, j) states.

For every state, isPalindrome() can take O(n) in the worst case.

Therefore, with the current implementation:

    Time = O(n³)

------------------------------------------------------------

Space Complexity:
-----------------

The DP table contains:

    O(n²)

states.

The recursion stack can also go up to:

    O(n)

Therefore:

    Space = O(n²)

------------------------------------------------------------

Important Code Issue:
---------------------

There is one typo/bug in the memoization check:

    if(dp[i][j] != -1) return 0;

It should be:

    if(dp[i][j] != -1) return dp[i][j];

Otherwise, whenever a state is already calculated, the function
returns 0 instead of the previously calculated result.

Correct version:

    if(dp[i][j] != -1)
        return dp[i][j];

The rest of the DP idea remains the same.

------------------------------------------------------------

Core Idea:
----------

              solve(i, j)
                  |
                  v
          Is s[i ... j]
           palindrome?
             /       \
           Yes        No
            |          |
         take = 1   take = 0
             \        /
              \      /
               +----+
                  |
        +---------+---------+
        |                   |
        v                   v
    move i forward      move j forward
        |                   |
        v                   v
      left                right
        \                   /
         \                 /
          +-------+-------+
                  |
                  v
        dp[i][j] = take + left + right

Final answer:

    solve(s, 0, 0)

which represents the total number of palindromic substrings.

*/