// Version 1: Recursion + Memoization
// class Solution {
//     private:
//         int n;
//         vector<vector<int>> dp;
    
//         bool isPalindrome(string& s, int i, int j) {
//             while(i < j) {
//                 if(s[i] != s[j]) return false;
//                 i++;
//                 j--;
//             }
//             return true;
//         }
    
//         int solve(string& s, int& k, int i, int j) {
//             if(j >= n) return 0;
    
//             if(dp[i][j] != -1) return dp[i][j];
    
//             if(isPalindrome(s, i, j)) {
//                 int take =  1 + solve(s, k, j + 1, j + k);
//                 int grow = solve(s, k, i, j + 1);
//                 int slide = solve(s, k, i + 1, j + 1);
    
//                 return dp[i][j] = max({take, grow, slide});
//             }
            
//             int grow = solve(s, k, i, j + 1);
//             int slide = solve(s, k, i + 1, j + 1);
    
//             return dp[i][j] = max(grow, slide);
//         }
    
//     public:
//         int maxPalindromes(string s, int k) {
//             n = s.size();
//             if(k == 1) return n;
    
//             dp.assign(n, vector<int>(n, -1));
            
//             return solve(s, k, 0, k - 1);
//         }
//     };

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

// Version 2: Bottom-Up
class Solution {
    private:
        bool isPalindrome(string& s, int i, int j) {
            while(i < j) {
                if(s[i] != s[j]) return false;
                i++;
                j--;
            }
            return true;
        }
    
    public:
        int maxPalindromes(string s, int k) {
            int n = s.size();
            if(k == 1) return n;
    
            vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
            
            for(int i = n - 1; i >= 0; i--) {
                for(int j = n - 1; j >= 0; j--) {
                    if(isPalindrome(s, i, j)) {
                        int take =  1 + (j + k <= n ? dp[j + 1][j + k] : 0);
                        int grow = dp[i][j + 1];
                        int slide = dp[i + 1][j + 1];
    
                        dp[i][j] = max({take, grow, slide});
                    }
                    
                    int grow = dp[i][j + 1];
                    int slide = dp[i + 1][j + 1];
    
                    dp[i][j] = max({dp[i][j], grow, slide});
                }
            }
    
            return dp[0][k - 1];
        }
    };

/*
LeetCode 2472. Maximum Number of Non-overlapping Palindrome Substrings

Approach:
---------

We use Dynamic Programming with a Bottom-Up approach.

The goal is to find the maximum number of non-overlapping
palindromic substrings of length at least k.

Instead of using recursion + memoization, we build the DP table
iteratively from the bottom/right side of the string.

The main idea is the same as the recursive version:

    1. TAKE  -> take s[i...j] as a palindrome.
    2. GROW  -> increase j and consider a larger substring.
    3. SLIDE -> move both i and j forward.

------------------------------------------------------------

isPalindrome():
---------------

    bool isPalindrome(string& s, int i, int j)

This function checks whether the substring:

    s[i...j]

is a palindrome.

We compare characters from both ends:

    s[i] <-> s[j]

If they are different, return false.

Otherwise, move towards the center:

    i++
    j--

If all characters match, return true.

------------------------------------------------------------

DP Definition:
--------------

    dp[i][j]

represents the maximum number of valid, non-overlapping
palindromic substrings that can be obtained starting from
the current state [i, j].

The table has size:

    (n + 1) x (n + 1)

The extra row and column allow us to safely access states such as:

    dp[i + 1][j + 1]
    dp[i][j + 1]

when i or j reaches n.

All states are initially 0.

------------------------------------------------------------

Why do we iterate from right to left?
--------------------------------------

Our transitions depend on states with larger indices:

    dp[i][j + 1]
    dp[i + 1][j + 1]
    dp[j + 1][j + k]

Therefore, these states must already be calculated before
calculating dp[i][j].

So we iterate:

    i = n - 1 -> 0
    j = n - 1 -> 0

This guarantees that the required future states are already
available.

------------------------------------------------------------

Special Case: k == 1
--------------------

    if(k == 1) return n;

If k = 1, every individual character is itself a palindrome.

For example:

    s = "abcde"

We can choose:

    "a", "b", "c", "d", "e"

All of them are non-overlapping.

Therefore, the maximum number of palindromes is simply:

    n

------------------------------------------------------------

Main DP Loop:
-------------

    for(int i = n - 1; i >= 0; i--) {
        for(int j = n - 1; j >= 0; j--) {

We consider every possible state [i, j].

For every state, we first check whether:

    s[i...j]

is a palindrome.

------------------------------------------------------------

Case 1: Current substring is a palindrome
------------------------------------------

    if(isPalindrome(s, i, j))

If s[i...j] is a palindrome, we have the option to TAKE it.

There are three possible choices.

------------------------------------------------------------

Choice 1: TAKE
--------------

    int take = 1 + (j + k <= n ? dp[j + 1][j + k] : 0);

We select:

    s[i...j]

as one palindrome.

Therefore:

    +1

is added to the answer.

After selecting this palindrome, the next palindrome cannot
overlap with it.

So we move to:

    j + 1

and start considering the next range from there.

The next state is:

    dp[j + 1][j + k]

The range:

    [j + 1, j + k]

has length k, which is the minimum allowed palindrome length.

If:

    j + k > n

there are not enough characters remaining for another
length-k range, so we use:

    0

instead.

Therefore:

    take = 1 + next valid answer

------------------------------------------------------------

Choice 2: GROW
--------------

    int grow = dp[i][j + 1];

We keep the same starting index i but increase j.

Current range:

    [i ........ j]

becomes:

    [i .......... j + 1]

This allows us to consider a larger substring.

For example:

    "aba"

can be extended to:

    "abac"
    "abacc"
    ...

This is useful because even if the current palindrome is valid,
a better answer may be obtained by considering a different
larger range.

------------------------------------------------------------

Choice 3: SLIDE
---------------

    int slide = dp[i + 1][j + 1];

We move both i and j forward:

    [i, j]

becomes:

    [i + 1, j + 1]

This shifts the current window one position to the right.

This allows us to ignore the current starting position and
search for a better palindrome later in the string.

------------------------------------------------------------

Choose the Best Option:
-----------------------

    dp[i][j] = max({take, grow, slide});

If s[i...j] is a palindrome, we consider all three possibilities:

    TAKE
    GROW
    SLIDE

and store the maximum result.

------------------------------------------------------------

Important: GROW and SLIDE are checked again
---------------------------------------------

After the palindrome-specific block, we have:

    int grow = dp[i][j + 1];
    int slide = dp[i + 1][j + 1];

    dp[i][j] = max({dp[i][j], grow, slide});

This ensures that even if s[i...j] is NOT a palindrome,
we can still continue searching.

So there are effectively two cases:

If s[i...j] is a palindrome:

    dp[i][j] =
        max(
            take,
            grow,
            slide
        );

If s[i...j] is NOT a palindrome:

    dp[i][j] =
        max(
            grow,
            slide
        );

The second max is also useful when the palindrome exists because
it makes sure that TAKE is not forced just because the current
substring is a palindrome.

------------------------------------------------------------

Why do we start from dp[0][k - 1]?
-----------------------------------

The smallest valid palindrome must have length k.

Therefore, the initial range is:

    i = 0
    j = k - 1

because:

    j - i + 1
    = k - 1 - 0 + 1
    = k

So:

    return dp[0][k - 1];

gives the maximum number of valid non-overlapping palindromes
starting from the first possible length-k window.

------------------------------------------------------------

Why are the chosen palindromes non-overlapping?
------------------------------------------------

Suppose we choose:

    s[i...j]

as a palindrome.

The TAKE transition moves to:

    dp[j + 1][j + k]

Therefore, the next selected palindrome starts strictly after j.

So:

    First palindrome:
        [i ........ j]

    Next palindrome:
                  [j+1 ........]

There is no common index.

Hence, the selected palindromes are guaranteed to be
non-overlapping.

------------------------------------------------------------

Bottom-Up DP Flow:
------------------

The DP is essentially converting the recursive decisions into
table lookups.

Recursive version:

    take  -> solve(j + 1, j + k)
    grow  -> solve(i, j + 1)
    slide -> solve(i + 1, j + 1)

Bottom-Up version:

    take  -> dp[j + 1][j + k]
    grow  -> dp[i][j + 1]
    slide -> dp[i + 1][j + 1]

So instead of recursively calling solve(), we directly read
the already-computed values from dp.

------------------------------------------------------------

Example:
--------

Suppose:

    s = "abaccdbbd"
    k = 3

Initial state:

    dp[0][2]

because the first candidate has length:

    2 - 0 + 1 = 3

The substring is:

    "aba"

which is a palindrome.

Therefore, we can:

    TAKE:
        select "aba"
        +1
        then continue after index 2

or:

    GROW:
        consider a larger substring

or:

    SLIDE:
        move the window forward

The DP evaluates all these possibilities and keeps the maximum.

------------------------------------------------------------

Why do we need dp[n][*] and dp[*][n]?
--------------------------------------

The DP table is created as:

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

The extra row/column provide valid boundary states.

For example:

    dp[i][n]
    dp[n][j]

represent states where we have moved beyond the string.

Since there are no more characters to process, their value is:

    0

This allows transitions such as:

    dp[i][j + 1]

and:

    dp[i + 1][j + 1]

without going out of bounds.

------------------------------------------------------------

Overall Algorithm:
------------------

    1. If k == 1:
           return n.

    2. Create an (n + 1) x (n + 1) DP table initialized to 0.

    3. Iterate i from n - 1 down to 0.

    4. For every i, iterate j from n - 1 down to 0.

    5. Check whether s[i...j] is a palindrome.

    6. If it is a palindrome:
           calculate TAKE.

    7. Calculate GROW and SLIDE.

    8. Store the maximum of all valid choices in dp[i][j].

    9. Return:

           dp[0][k - 1]

------------------------------------------------------------

Time Complexity:
----------------

There are:

    O(n²)

DP states.

For every state, isPalindrome() can take:

    O(n)

in the worst case.

Therefore:

    O(n³)

overall time complexity.

------------------------------------------------------------

Space Complexity:
-----------------

The DP table contains:

    (n + 1) × (n + 1)

elements.

Therefore:

    O(n²)

space complexity.

------------------------------------------------------------

Core Idea:
----------

For every state [i, j]:

                s[i ........ j]
                       |
                Is it palindrome?
                       |
             +---------+---------+
             |                   |
            YES                  NO
             |                   |
       +-----+-----+         GROW / SLIDE
       |     |     |
     TAKE  GROW  SLIDE
       |
       v
   +1 palindrome
       |
       v
   jump to j + 1

The DP stores the maximum number of non-overlapping
palindromic substrings that can be selected.
*/