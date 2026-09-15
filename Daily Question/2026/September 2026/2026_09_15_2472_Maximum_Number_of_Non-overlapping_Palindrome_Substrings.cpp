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
    
        int solve(string& s, int& k, int i, int j) {
            if(j >= n) return 0;
    
            if(dp[i][j] != -1) return dp[i][j];
    
            if(isPalindrome(s, i, j)) {
                int take =  1 + solve(s, k, j + 1, j + k);
                int grow = solve(s, k, i, j + 1);
                int slide = solve(s, k, i + 1, j + 1);
    
                return dp[i][j] = max({take, grow, slide});
            }
            
            int grow = solve(s, k, i, j + 1);
            int slide = solve(s, k, i + 1, j + 1);
    
            return dp[i][j] = max(grow, slide);
        }
    
    public:
        int maxPalindromes(string s, int k) {
            n = s.size();
            if(k == 1) return n;
    
            dp.assign(n, vector<int>(n, -1));
            
            return solve(s, k, 0, k - 1);
        }
    };

/*
LeetCode 2472. Maximum Number of Non-overlapping Palindrome Substrings

Approach:
---------

We use Dynamic Programming + Recursion + Memoization.

The goal is to find the maximum number of non-overlapping
palindromic substrings of length at least k.

The important observation is that while scanning the string,
for every pair of indices (i, j), we have three possible choices:

    1. Take s[i...j] if it is a palindrome of length >= k.
    2. Grow the current substring by moving j.
    3. Slide the starting index forward by moving i.

The DP state is:

    dp[i][j]

which represents the maximum number of valid palindromes that can
be obtained while considering the substring/range starting at i
and ending at j.

------------------------------------------------------------

isPalindrome():
---------------

    bool isPalindrome(string& s, int i, int j)

This function checks whether s[i...j] is a palindrome.

We compare characters from both ends:

    s[i] <-> s[j]

If they are different, the substring is not a palindrome.

Otherwise, move both pointers towards the center:

    i++
    j--

If all characters match, return true.

Example:

    s = "ababa"

    i = 0, j = 4

    a == a
    b == b
    a == a

Therefore:

    "ababa" is a palindrome.

------------------------------------------------------------

solve():
---------

    solve(s, k, i, j)

The function tries to find the maximum number of valid
non-overlapping palindromes using the current range [i, j].

------------------------------------------------------------

Base Case:
----------

    if(j >= n) return 0;

If j reaches the end of the string, there are no more characters
to process.

Therefore, no more palindrome can be selected:

    return 0;

------------------------------------------------------------

Memoization:
------------

    if(dp[i][j] != -1) return dp[i][j];

If the answer for state (i, j) has already been calculated,
return the stored answer instead of solving it again.

This avoids repeatedly solving the same states.

------------------------------------------------------------

Case 1: s[i...j] is a Palindrome
--------------------------------

First we check:

    if(isPalindrome(s, i, j))

If s[i...j] is a palindrome, we have the option to select it.

But there is an important condition:

    The selected palindrome must have length >= k.

The recursion starts with:

    solve(s, k, 0, k - 1)

so initially:

    j - i + 1 = k

Therefore, every substring considered for "take" has length at
least k.

------------------------------------------------------------

Choice 1: Take the Palindrome
-----------------------------

    int take = 1 + solve(s, k, j + 1, j + k);

We select:

    s[i...j]

as one palindrome.

Therefore:

    +1

to the answer.

After taking this palindrome, we must not use any character from
this substring again.

The next possible palindrome starts after j:

    j + 1

The new range is:

    [j + 1, j + k]

This makes sure the selected palindromes do not overlap.

Example:

    s = "abacdc"
         ^^^

Suppose:

    s[0...2] = "aba"

is selected.

The next palindrome must start from:

    index 3

and cannot use indices 0, 1, or 2 again.

------------------------------------------------------------

Choice 2: Grow the Current Range
--------------------------------

    int grow = solve(s, k, i, j + 1);

We keep the same starting index i but extend j.

So:

    [i, j]

becomes:

    [i, j + 1]

This allows us to consider a larger substring.

Example:

    Current:

        [i.........j]

    Grow:

        [i...........j+1]

This is useful because the current substring might not be the
best palindrome to select.

For example, if:

    s[i...j]

is a palindrome, we still might get a better answer by considering
a larger range.

------------------------------------------------------------

Choice 3: Slide the Starting Index
----------------------------------

    int slide = solve(s, k, i + 1, j + 1);

We move both i and j forward.

This effectively shifts the window to the right:

    [i, j]

becomes:

    [i + 1, j + 1]

This allows us to explore palindromes that start later in the
string.

This is important because the optimal answer may not use any
palindrome beginning at i.

------------------------------------------------------------

Take the Best Choice
--------------------

When s[i...j] is a palindrome:

    return dp[i][j] = max({take, grow, slide});

We choose whichever option produces the maximum number of
palindromes.

Therefore:

    dp[i][j] =
        max(
            take,
            grow,
            slide
        );

------------------------------------------------------------

Case 2: s[i...j] is NOT a Palindrome
-------------------------------------

If:

    isPalindrome(s, i, j) == false

we cannot take this substring.

Therefore, only two choices remain:

    1. Grow j
    2. Slide i and j

    int grow = solve(s, k, i, j + 1);
    int slide = solve(s, k, i + 1, j + 1);

Then:

    return dp[i][j] = max(grow, slide);

We simply ignore the current non-palindromic substring and
continue searching.

------------------------------------------------------------

Why do we use j + 1 in both transitions?
-----------------------------------------

The initial call is:

    solve(0, k - 1)

which represents the smallest possible substring of length k.

As we move through the string, j represents the right boundary
of the current candidate.

Therefore, increasing j allows us to consider longer substrings.

The slide operation:

    solve(i + 1, j + 1)

moves the entire range one position forward while keeping the
same window length.

------------------------------------------------------------

Why is "take" guaranteed to have length >= k?
----------------------------------------------

The first call is:

    solve(s, k, 0, k - 1)

So the initial range has:

    j - i + 1
    = (k - 1) - 0 + 1
    = k

When we take a palindrome:

    solve(j + 1, j + k)

The next range also has:

    (j + k) - (j + 1) + 1
    = k

Therefore, every candidate considered for "take" starts with
at least k characters.

As j grows using the "grow" operation, the candidate becomes
even longer.

------------------------------------------------------------

Why are the selected palindromes non-overlapping?
------------------------------------------------

Suppose we take:

    s[i...j]

Then the next recursive call starts from:

    j + 1

Therefore, the next palindrome can only use characters after j.

So the two selected ranges are:

    [i ........ j]
               |
               v
             j + 1
               |
               v
    [j+1 ...... ...]

There is no shared index between them.

Hence, the selected palindromes are non-overlapping.

------------------------------------------------------------

Special Case: k == 1
--------------------

    if(k == 1) return n;

If k = 1, every individual character is itself a palindrome.

Therefore, we can select every character:

    "abcde"

as:

    "a" "b" "c" "d" "e"

giving:

    n

palindromes.

So we immediately return n.

------------------------------------------------------------

Example:
--------

Suppose:

    s = "abaccdbbd"
    k = 3

We start with:

    solve(0, 2)

which considers:

    "aba"

Since "aba" is a palindrome, we can take it.

Then we continue from:

    index 3

Alternatively, we can grow the current range:

    "abac"
    "abacc"
    ...

or slide the range forward to search for another palindrome.

The recursion explores these possibilities and stores the best
answer for every (i, j) state.

------------------------------------------------------------

DP State:
---------

    dp[i][j]

stores:

    Maximum number of non-overlapping valid palindromic substrings
    that can be obtained from the current state [i, j].

------------------------------------------------------------

Overall Algorithm:
------------------

    1. Handle k == 1 separately.

    2. Create the DP table initialized with -1.

    3. Start recursion from:

           solve(0, k - 1)

       because the minimum allowed palindrome length is k.

    4. For every state [i, j]:

           If s[i...j] is a palindrome:
               
               take  -> select it
               grow  -> extend j
               slide -> move to the next starting position

           Otherwise:

               grow  -> extend j
               slide -> move forward

    5. Store the maximum result in dp[i][j].

    6. Return the maximum number of non-overlapping palindromes.

------------------------------------------------------------

Time Complexity:
----------------

There are O(n²) possible states:

    (i, j)

For every state, isPalindrome() can take O(n) time in the
worst case because it may scan the entire substring.

Therefore, the worst-case complexity is:

    O(n³)

------------------------------------------------------------

Space Complexity:
-----------------

The DP table contains:

    n × n

states.

Therefore:

    O(n²)

Additionally, recursion uses O(n) stack space in the worst case.

So the total auxiliary space is:

    O(n²)

------------------------------------------------------------

Core Idea:
----------

For every range [i, j]:

                 [ i ........ j ]
                   /      |      \
                  /       |       \
               TAKE      GROW    SLIDE
                |          |       |
                |          |       |
             +1 and      extend   move
             jump past   range    range
             palindrome

If the range is not a palindrome:

                    [i ........ j]
                       /       \
                    GROW      SLIDE

The DP chooses the maximum number of valid non-overlapping
palindromes among these possibilities.
*/