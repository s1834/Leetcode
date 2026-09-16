class Solution {
    public:
        string longestPalindrome(string s) {
            int n = s.size();
            string ans = "";
            vector<vector<bool>> dp(n, vector<bool>(n));
            
            for(int l = 1; l <= n; l++) {
                for(int i = 0; i + l - 1 < n; i++) {
                    int j = i + l - 1;
    
                    if(i == j) dp[i][j] = true;
                    else if(i + 1 == j) dp[i][j] = (s[i] == s[j]);
                    else dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
                    
                    if(dp[i][j] && (j - i + 1 > ans.size())) ans = s.substr(i, j - i + 1);
                }
            }
    
            return ans;
        }
    };

/*
LeetCode 5. Longest Palindromic Substring

Approach:
---------

We use Dynamic Programming to determine whether every substring
s[i...j] is a palindrome.

Once we know which substrings are palindromes, we keep track of
the longest palindromic substring found so far.

The main idea is:

    A substring is a palindrome if:

        1. Its first and last characters are equal.
        2. The substring inside them is also a palindrome.

------------------------------------------------------------

DP Definition:
-------------

    dp[i][j] = true
               if the substring s[i...j] is a palindrome.

Otherwise:

    dp[i][j] = false

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

The substring inside the first and last characters must
also be a palindrome.

For example:

    s = "babad"

For substring:

    "bab"

we have:

    s[0] == s[2] -> true

and:

    dp[1][1] -> true

Therefore:

    dp[0][2] = true

So "bab" is a palindrome.

------------------------------------------------------------

Why Do We Iterate by Length?
----------------------------

We iterate over substring lengths:

    l = 1
    l = 2
    l = 3
    ...
    l = n

This ensures that when we calculate:

    dp[i][j]

the smaller substring:

    dp[i + 1][j - 1]

has already been calculated.

For example:

    dp[i][j]

depends on:

    dp[i + 1][j - 1]

which has length:

    l - 2

So we calculate shorter substrings first.

------------------------------------------------------------

Finding i and j:
-----------------

For every substring length l:

    i = starting index

    j = i + l - 1

For example:

    s = "abcde"

    l = 3
    i = 1

then:

    j = 1 + 3 - 1
      = 3

So the substring is:

    s[1...3] = "bcd"

------------------------------------------------------------

Finding the Longest Palindrome:
-------------------------------

Whenever:

    dp[i][j] == true

we know that:

    s[i...j]

is a palindrome.

We calculate its length:

    j - i + 1

If this palindrome is longer than the current answer:

    if(dp[i][j] && (j - i + 1 > ans.size()))

we update:

    ans = s.substr(i, j - i + 1);

This keeps the longest palindromic substring found so far.

------------------------------------------------------------

Why Use j - i + 1?
-------------------

The substring starts at index i and ends at index j.

Therefore its length is:

    j - i + 1

For example:

    i = 2
    j = 5

Length:

    5 - 2 + 1
    = 4

The substring is:

    s[2...5]

------------------------------------------------------------

Example:
--------

    s = "babad"

Consider:

    "bab"

Characters:

    b == b

Inner substring:

    "a"

which is a palindrome.

Therefore:

    "bab" -> palindrome

Later:

    "aba"

is also found as a palindrome.

Both have length 3.

The code keeps the first longest palindrome found because
the update condition uses:

    >

instead of:

    >=

Therefore the answer can be:

    "bab"

which is a valid longest palindromic substring.

------------------------------------------------------------

Another Example:
-----------------

    s = "cbbd"

Length 1:

    "c" -> palindrome
    "b" -> palindrome
    "b" -> palindrome
    "d" -> palindrome

Length 2:

    "cb" -> false
    "bb" -> true
    "bd" -> false

So:

    ans = "bb"

Length 3 and 4 do not produce a longer palindrome.

Return:

    "bb"

------------------------------------------------------------

Difference From LeetCode 647:
------------------------------

In LeetCode 647, we count every substring for which:

    dp[i][j] == true

Here, instead of counting them, we maintain the longest
palindromic substring found so far.

So the DP logic is the same:

    dp[i][j] = whether s[i...j] is a palindrome

but the final operation is different.

647:

    count++

5:

    update ans if current palindrome is longer

------------------------------------------------------------

Algorithm:
----------

    1. Create an n x n DP table.

    2. Iterate over all substring lengths from 1 to n.

    3. For every substring s[i...j]:

           If length == 1:
               palindrome

           Else if length == 2:
               check s[i] == s[j]

           Else:
               check:
                   s[i] == s[j]
                   AND
                   dp[i + 1][j - 1]

    4. If the substring is a palindrome and its length is
       greater than the current answer:

           update ans

    5. Return ans.

------------------------------------------------------------

Time Complexity:
----------------

There are O(n²) possible substrings.

For every substring, we perform O(1) DP work.

Therefore:

    O(n²)

Note:

    s.substr(...)

is performed only when a new longest palindrome is found.
The total practical cost remains within the expected
O(n²) solution for the given constraints.

------------------------------------------------------------

Space Complexity:
-----------------

The DP table contains:

    n × n

boolean values.

Therefore:

    O(n²)

------------------------------------------------------------

Core Idea:
----------

Instead of checking every substring from scratch, we reuse
the result of its inner substring.

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
              dp[i][j] = true

So:

    Palindrome(i, j)
        =
    s[i] == s[j]
        &&
    Palindrome(i + 1, j - 1)

Whenever a palindrome is found, compare its length with the
current answer and keep the longest one.
*/