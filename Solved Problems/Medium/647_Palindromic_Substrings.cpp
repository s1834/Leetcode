// Version 1: Recursion + Memoization
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

// Version 2: Bottom-Up
class Solution {
    public:
        int countSubstrings(string s) {
            int n = s.size();
            int count = 0;
            vector<vector<bool>> dp(n, vector<bool>(n));
            
            for(int l = 1; l <= n; l++) {
                for(int i = 0; i + l - 1 < n; i++) {
                    int j = i + l - 1;
    
                    if(i == j) dp[i][j] = true;
                    else if(i + 1 == j) dp[i][j] = (s[i] == s[j]);
                    else dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
                    
                    if(dp[i][j]) count++;
                }
            }
    
            return count;
        }
    };

/*
LeetCode 647. Palindromic Substrings

Approach:
---------

We use Dynamic Programming to determine whether every substring
s[i...j] is a palindrome.

The main idea is:

    A substring is a palindrome if:

        1. Its first and last characters are equal.
        2. The substring inside them is also a palindrome.

So:

    dp[i][j] = true
        if s[i...j] is a palindrome.

------------------------------------------------------------

DP Definition:
-------------

    dp[i][j] = whether the substring from index i to index j
               is a palindrome.

For example:

    s = "abcba"

    dp[0][4] represents:

        "abcba"

Since:

    s[0] == s[4]

and:

    dp[1][3] represents "bcb"

which is also a palindrome,

therefore:

    dp[0][4] = true

------------------------------------------------------------

Base Case 1: Length = 1
-----------------------

Every single character is a palindrome.

For example:

    "a"
    "b"
    "c"

So when:

    i == j

we set:

    dp[i][j] = true;

------------------------------------------------------------

Base Case 2: Length = 2
-----------------------

For a substring containing exactly two characters,
it is a palindrome only when both characters are equal.

For example:

    "aa" -> palindrome
    "ab" -> not a palindrome

Therefore:

    else if(i + 1 == j)
        dp[i][j] = (s[i] == s[j]);

------------------------------------------------------------

General Case:
-------------

For length >= 3:

    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);

There are two conditions:

    1. s[i] == s[j]

The first and last characters must be equal.

    2. dp[i + 1][j - 1]

The substring excluding the first and last characters
must also be a palindrome.

For example:

    s = "abcba"

    i = 0
    j = 4

    s[0] == s[4]
       |
       v
      'a' == 'a'

and:

    dp[1][3] = true

because:

    "bcb"

is a palindrome.

Therefore:

    dp[0][4] = true

------------------------------------------------------------

Why Do We Iterate by Length?
----------------------------

We calculate:

    l = 1 -> substrings of length 1
    l = 2 -> substrings of length 2
    l = 3 -> substrings of length 3
    ...

This is important because the general transition:

    dp[i][j] = s[i] == s[j] && dp[i + 1][j - 1]

depends on a smaller substring:

    dp[i + 1][j - 1]

which has length:

    l - 2

Therefore, smaller substrings must already be calculated.

------------------------------------------------------------

Finding i and j:
-----------------

For every substring length l:

    i = starting index

    j = i + l - 1

For example, if:

    l = 3

and:

    i = 2

then:

    j = 2 + 3 - 1
      = 4

So the substring is:

    s[2...4]

------------------------------------------------------------

Counting Palindromic Substrings:
---------------------------------

Every time:

    dp[i][j] == true

the substring s[i...j] is a palindromic substring.

Therefore:

    if(dp[i][j]) count++;

We count every occurrence separately.

For example:

    s = "aaa"

The palindromic substrings are:

    "a"   -> index 0
    "a"   -> index 1
    "a"   -> index 2
    "aa"  -> index 0...1
    "aa"  -> index 1...2
    "aaa" -> index 0...2

Total:

    6

------------------------------------------------------------

Example:
--------

    s = "aaa"

Length = 1:

    "a" -> palindrome
    "a" -> palindrome
    "a" -> palindrome

count = 3

Length = 2:

    "aa" -> palindrome
    "aa" -> palindrome

count = 5

Length = 3:

    "aaa" -> palindrome

count = 6

Return:

    6

------------------------------------------------------------

Dry Run:
--------

For:

    s = "aba"

Initially:

    dp = false for every substring

Length = 1:

    dp[0][0] = true    -> "a"
    dp[1][1] = true    -> "b"
    dp[2][2] = true    -> "a"

count = 3

Length = 2:

    dp[0][1] = (a == b) = false
    dp[1][2] = (b == a) = false

count = 3

Length = 3:

    i = 0
    j = 2

    s[0] == s[2] -> true
    dp[1][1]      -> true

Therefore:

    dp[0][2] = true

"aba" is a palindrome.

count = 4

Return:

    4

------------------------------------------------------------

Algorithm:
----------

    1. Create a 2D DP table.

    2. Iterate over all possible substring lengths
       from 1 to n.

    3. For each substring s[i...j]:

           If length == 1:
               palindrome

           Else if length == 2:
               check s[i] == s[j]

           Else:
               check:
                   s[i] == s[j]
                   AND
                   dp[i + 1][j - 1]

    4. Whenever dp[i][j] is true, increment count.

    5. Return count.

------------------------------------------------------------

Time Complexity:
----------------

There are O(n²) possible substrings.

For every substring, we perform O(1) work because the
palindrome result of the inner substring is already stored
in dp.

Therefore:

    O(n²)

------------------------------------------------------------

Space Complexity:
-----------------

The DP table contains:

    n × n

entries.

Therefore:

    O(n²)

------------------------------------------------------------

Core Idea:
----------

Instead of checking every substring character-by-character,
we reuse the result of the inner substring.

                s[i] == s[j]
                     |
                     v
              +-------------+
              |             |
              | dp[i+1][j-1]|
              |             |
              +-------------+
                     |
                     v
              dp[i][j]

So:

    Palindrome(i, j)
        =
    s[i] == s[j]
        &&
    Palindrome(i + 1, j - 1)

This allows us to solve the problem in O(n²) time.
*/