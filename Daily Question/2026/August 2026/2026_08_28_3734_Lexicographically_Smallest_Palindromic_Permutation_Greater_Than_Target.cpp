class Solution {
    private:
        string result = "";
        char midChar = '$';
        int halfLen;
    
        bool solve(string& curr, vector<int>& count, string& target, int idx, bool greater) {
            // reached half of string
            if(curr.size() == halfLen) {
                // store string so you dont modify the address of curr
                string temp = curr;
                string revCurr = curr;
                reverse(revCurr.begin(), revCurr.end());
    
                // if odd
                if(midChar != '$') temp += midChar;
    
                // add reverse
                temp += revCurr;
    
                // if found greater palindrome
                if(temp > target) {
                    result = temp;
                    return true;
                }
    
                return false;
            }
    
            for(char ch = 'a'; ch <= 'z'; ch++) {
                if(count[ch - 'a'] == 0) continue; // if curr char didnt exist in 's' (i.e. count(char) = 0)
                if(greater == false && ch < target[idx]) continue; // if char is less than desired target[idx]
    
                // Do
                curr.push_back(ch);
                count[ch - 'a']--;
    
                bool isGreater = greater || ch > target[idx]; // mark greater if already greater or current char is greater than target
                
                // Explore
                if(solve(curr, count, target, idx + 1, isGreater)) return true;  // recursively build remaining string; return true if a valid greater permutation is found
                
                // Backtrack
                curr.pop_back();
                count[ch - 'a']++;
            }
    
            return false;
        }
    
    public:
        string lexPalindromicPermutation(string s, string target) {
            int n = s.size();
    
            vector<int> count(26, 0); // count of char of all 26 alphabets
            for(auto &x : s) count[x - 'a']++; // add count of each char
    
            // count number of odd freqency char
            int oddCount = 0;
            for(int i = 0; i < 26; i++) {
                if(count[i] % 2) {
                    oddCount++;
                    midChar = i + 'a';
                }
            }
            
            // if more than one odd freq char, then palindrome not possible
            if (oddCount > 1) return "";
    
            // for left half of palindrome
            for(int i = 0; i < 26; i++) {
                count[i] /= 2;
            }
    
            // half length of s
            halfLen = n / 2;
            
            string curr;
            solve(curr, count, target, 0, false);
    
            return result;
        }
    };

/*
LeetCode 3734. Lexicographically Smallest Palindromic Permutation

Approach:
---------

We need to rearrange the characters of s to form a palindrome
which is strictly greater than target.

Among all possible palindromes, we need the lexicographically
smallest one.

The key observation is:

    A palindrome is completely determined by its first half
    and, if the length is odd, its middle character.

For example:

    left half = "abc"
    middle   = "d"

Then the complete palindrome is:

    "abc" + "d" + "cba"
       ↓
    "abcdcba"

Therefore, instead of generating the entire palindrome, we only
need to generate its first half.

We use:

    Frequency Array + Backtracking + Greedy Ordering

------------------------------------------------------------

Step 1: Count Character Frequencies
-----------------------------------

    vector<int> count(26, 0);

We count how many times every character appears in s.

For example:

    s = "aabbc"

frequency:

    a -> 2
    b -> 2
    c -> 1

A palindrome requires characters to appear symmetrically.

------------------------------------------------------------

Step 2: Check Whether a Palindrome Is Possible
-----------------------------------------------

For a string to be rearranged into a palindrome:

    - Every character must have an even frequency.
    - If the length is odd, exactly one character may have
      an odd frequency.

So we count:

    oddCount

using:

    if(count[i] % 2)

If more than one character has an odd frequency:

    if(oddCount > 1) return "";

then it is impossible to construct any palindrome.

------------------------------------------------------------

Finding the Middle Character:
------------------------------

If there is an odd-frequency character:

    midChar = i + 'a';

That character must appear exactly once in the center of the
palindrome.

For example:

    s = "aabbc"

The frequency of c is odd:

    a -> 2
    b -> 2
    c -> 1

Therefore:

    midChar = 'c'

and every other character is split equally between the left
and right halves.

The '$' value is used initially to indicate that there is no
middle character.

------------------------------------------------------------

Step 3: Build Only Half of the Palindrome
------------------------------------------

Once we know the frequencies, we only need half of each
character's occurrences:

    for(int i = 0; i < 26; i++)
        count[i] /= 2;

For:

    a -> 2
    b -> 2
    c -> 1

we get:

    a -> 1
    b -> 1
    c -> 0

The left half will contain:

    "ab"

and the complete palindrome will be:

    "ab" + "c" + "ba"

which gives:

    "abcba"

------------------------------------------------------------

Why Can We Only Build the Left Half?
-------------------------------------

Suppose the left half is:

    "abc"

Then the right half is forced:

    "cba"

There is no independent choice for the right half.

So instead of generating:

    abc + middle + cba

we only generate:

    abc

and construct the remaining part automatically.

This reduces the search space significantly.

------------------------------------------------------------

halfLen:
---------

    halfLen = n / 2;

This is the number of characters we need to put into the left
half.

For example:

    n = 6 -> halfLen = 3

    n = 7 -> halfLen = 3

For an odd-length string, the extra character is handled
separately using:

    midChar

------------------------------------------------------------

Backtracking State:
-------------------

    solve(curr, count, target, idx, greater)

where:

    curr
        = left half constructed so far

    count
        = remaining characters available for the left half

    target
        = target string

    idx
        = current position of the left half

    greater
        = whether the left half has already become greater than
          the corresponding prefix of target

The important part is that we build the palindrome from
left to right.

------------------------------------------------------------

Why Do We Need greater?
-----------------------

The lexicographical comparison between two palindromes is
decided by their first differing character.

Since both strings are palindromes, if their left halves differ
at some position, the complete palindrome is also decided at
that position.

For example:

    palindrome 1 = "abcba"
    palindrome 2 = "abdba"

They first differ at:

    index 2

and:

    'c' < 'd'

so:

    "abcba" < "abdba"

Therefore, while building the left half, we can compare it with
the corresponding prefix of target.

------------------------------------------------------------

If greater == false:
---------------------

We are still equal to target so far.

Therefore, we cannot choose:

    ch < target[idx]

because that would immediately make the final palindrome
smaller than target.

So:

    if(greater == false && ch < target[idx])
        continue;

For example:

    target = "abcdcba"

Suppose we have constructed:

    curr = "ab"

At the next position:

    target[idx] = 'c'

If we choose:

    'b'

then our palindrome will definitely be smaller than target.

No future character can fix this because the first difference
has already made our string smaller.

So we skip that branch.

------------------------------------------------------------

Three Possibilities:
---------------------

When:

    greater == false

we have three cases.

    ch < target[idx]
        -> palindrome will be smaller
        -> skip

    ch == target[idx]
        -> still equal
        -> continue with greater = false

    ch > target[idx]
        -> palindrome becomes greater
        -> continue with greater = true

If:

    greater == true

then the left half is already greater than target.

From that point onward, any remaining characters are allowed.

------------------------------------------------------------

Choose Character:
-----------------

    curr.push_back(ch);
    count[ch - 'a']--;

We use one occurrence of ch in the left half.

For example:

    count['a'] = 2

After choosing 'a':

    curr = "a"
    count['a'] = 1

We decrease the frequency because that character occurrence
has been consumed.

------------------------------------------------------------

Update greater:
---------------

    bool isGreater = greater || ch > target[idx];

There are two ways we can already be greater.

1. We were already greater before this position:

       greater == true

   Once greater becomes true, it can never become false.

2. We were equal so far, but the current character is larger:

       ch > target[idx]

Therefore:

    isGreater = greater || ch > target[idx];

------------------------------------------------------------

Recursive Exploration:
-----------------------

    if(solve(curr, count, target, idx + 1, isGreater))
        return true;

We recursively choose the next character for the left half.

If a valid palindrome is eventually constructed, return true
immediately.

There is no need to search for another answer because we try
characters in increasing alphabetical order.

------------------------------------------------------------

Backtracking:
-------------

If the current choice cannot produce a valid answer:

    curr.pop_back();
    count[ch - 'a']++;

We undo the choice.

This restores the previous state so we can try the next possible
character.

The pattern is:

    Choose
       ↓
    Explore
       ↓
    Undo
       ↓
    Try next character

------------------------------------------------------------

Base Case:
----------

    if(curr.size() == halfLen)

At this point, the complete left half has been constructed.

Now we build the complete palindrome.

First:

    string temp = curr;

This starts with the left half.

Then:

    string revCurr = curr;
    reverse(revCurr.begin(), revCurr.end());

This creates the right half.

For example:

    curr = "abc"

then:

    revCurr = "cba"

------------------------------------------------------------

Odd Length:
-----------

If:

    midChar != '$'

then the original string had one character with an odd
frequency.

That character must be placed in the middle:

    if(midChar != '$')
        temp += midChar;

For example:

    curr = "ab"
    midChar = 'c'

then:

    temp = "abc"

------------------------------------------------------------

Add the Right Half:
--------------------

    temp += revCurr;

Now the complete palindrome is constructed.

For example:

    curr     = "abc"
    midChar  = 'd'
    revCurr  = "cba"

gives:

    temp = "abcdcba"

------------------------------------------------------------

Check If Palindrome Is Greater:
--------------------------------

    if(temp > target)

At this point we have a complete palindrome.

We check whether it is strictly greater than target.

If yes:

    result = temp;
    return true;

If not:

    return false;

This also handles the case where the constructed palindrome is
exactly equal to target.

We need:

    temp > target

not:

    temp >= target

because the answer must be strictly greater.

------------------------------------------------------------

Why Do We Check the Complete Palindrome Here?
-----------------------------------------------

Although we maintain:

    greater

while constructing the left half, the final check:

    temp > target

is used to guarantee correctness.

The palindrome is now fully constructed, so we directly compare
the actual answer against target.

This is especially useful because the middle character and
mirrored right half are not explicitly considered during the
backtracking comparison.

------------------------------------------------------------

Why Characters Are Tried from 'a' to 'z':
-----------------------------------------

    for(char ch = 'a'; ch <= 'z'; ch++)

We always try the smallest possible character first.

Our goal is not just:

    any palindrome > target

but:

    the lexicographically smallest palindrome > target

Suppose both are possible:

    "abddba"
    "acccca"

Since:

    'b' < 'c'

we want:

    "abddba"

Because we try 'a', then 'b', then 'c', etc., the first valid
complete palindrome we find is the lexicographically smallest.

------------------------------------------------------------

Important Greedy Idea:
----------------------

Suppose at some position:

    target[idx] = 'c'

and we can choose:

    'd'

or:

    'e'

If choosing 'd' can eventually produce a valid palindrome,
then every palindrome beginning with 'd' is lexicographically
smaller than every palindrome beginning with 'e'.

Therefore, we must completely explore the 'd' branch before
trying 'e'.

Our loop naturally does exactly this:

    'a' -> 'b' -> 'c' -> 'd' -> ... -> 'z'

------------------------------------------------------------

Example:
--------

Suppose:

    s = "aabbcc"
    target = "abcabc"

The frequencies are:

    a -> 2
    b -> 2
    c -> 2

So the left half must contain:

    a, b, c

Possible left halves include:

    "abc"
    "acb"
    "bac"
    ...

The corresponding palindromes are:

    "abccba"
    "acbbca"
    "baccab"
    ...

We start with the smallest possible left half.

If:

    "abccba" > target

then it is immediately the answer.

If not, we backtrack and try the next smallest possibility.

------------------------------------------------------------

Why the Left Half Determines Lexicographical Order:
------------------------------------------------------

Consider two palindromes:

    P1 = "abcxcba"
    P2 = "abdydba"

Their left halves are:

    P1 left = "abc"
    P2 left = "abd"

At the first differing position:

    'c' < 'd'

therefore:

    P1 < P2

The middle and right half do not change this ordering.

So finding the lexicographically smallest valid left half is
enough to find the lexicographically smallest palindrome.

------------------------------------------------------------

One Important Difference From Normal Permutation:
---------------------------------------------------

Normally, if we wanted the smallest permutation greater than
target, we would use all characters directly.

Here, we cannot freely arrange all characters.

A palindrome forces:

    left half == reverse(right half)

Therefore, character frequencies must be split:

    frequency / 2

for the two halves.

If the frequency is odd, that character goes in the middle.

So the problem becomes:

    Find the smallest valid left half
    +
    construct its forced mirror.

------------------------------------------------------------

Complete Flow:
--------------

                Count frequencies
                       |
                       ↓
             Count odd frequencies
                       |
                +------+------+
                |             |
             > 1 odd       <= 1 odd
                |             |
             return ""    split frequencies
                              |
                              ↓
                     Build left half
                              |
                              ↓
                    Try 'a' -> 'z'
                              |
                              ↓
                    Compare with target
                              |
                 +------------+------------+
                 |                         |
             smaller/equal              greater
                 |                         |
               prune                  greater = true
                                           |
                                           ↓
                                      recurse
                                           |
                                  half completed?
                                           |
                                           ↓
                                  build palindrome
                                           |
                                           ↓
                                   temp > target?
                                      /       \
                                    yes       no
                                    |          |
                                 result      backtrack

------------------------------------------------------------

Example of Backtracking:
------------------------

Suppose the required left half length is 3.

We might explore:

    "aaa"
       ↓
    invalid / unavailable

    "aab"
       ↓
    palindrome not > target
       ↓
    backtrack

    "aac"
       ↓
    palindrome not > target
       ↓
    backtrack

    "aba"
       ↓
    palindrome > target
       ↓
    return

Because candidates are explored in lexicographical order, the
first successful palindrome is the smallest possible answer.

------------------------------------------------------------

Why Frequency Is Restored During Backtracking:
-----------------------------------------------

Suppose:

    count['a'] = 1

We choose 'a':

    count['a'] = 0

If that branch fails, we must restore:

    count['a'] = 1

Otherwise, future branches would incorrectly believe that no
'a' is available.

So every:

    count[ch]--;

must eventually have:

    count[ch]++;

when that branch is abandoned.

------------------------------------------------------------

Role of the '$' Character:
--------------------------

    char midChar = '$';

'$' is not a lowercase English character.

It is simply used as a marker meaning:

    "There is no middle character."

If the original string has odd length, exactly one character
has odd frequency and:

    midChar = that character

Otherwise:

    midChar == '$'

and no middle character is inserted.

------------------------------------------------------------

Complexity:
-----------

Let:

    n = s.size()

The backtracking explores possible arrangements of the n/2
characters in the left half.

In the worst case, when the characters are mostly distinct, the
number of possible arrangements is factorial:

    O((n/2)!)

At each complete candidate we construct/reverse a string of
length O(n), so the worst-case complexity is approximately:

    O(n * (n/2)!)

The recursion stack and current string require:

    O(n)

space.

The frequency array uses:

    O(26)

additional space.

------------------------------------------------------------

Main Idea to Remember:
----------------------

This problem looks like a permutation problem, but the palindrome
property gives us a major simplification:

    Palindrome
       =
    Left Half
    + Middle
    + Reverse(Left Half)

So:

    1. Count character frequencies.
    2. If more than one odd frequency exists, palindrome is
       impossible.
    3. Divide every frequency by 2 to get characters for the
       left half.
    4. Store the odd-frequency character as the middle.
    5. Backtrack to construct the left half.
    6. Try characters from 'a' to 'z' so the first valid answer
       is lexicographically smallest.
    7. Once the left half is complete, construct the full
       palindrome.
    8. Check:

           temp > target

    9. If it fails, backtrack and try the next permutation.

The two most important ideas are:

    Palindrome = left + middle + reverse(left)

and:

    Try characters in increasing order
    + backtrack
    = lexicographically smallest valid answer.
*/