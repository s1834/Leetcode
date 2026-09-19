// Version 1:
class Solution {
    public:
        bool checkInclusion(string s1, string s2) {
            int m = s1.size(), n = s2.size();
            if(m > n) return false;
    
            unordered_map<char, int> mp1, mp2;
            for(auto x : s1) mp1[x]++;
    
            for(int i = 0; i < m; i++) {
                if(mp1.find(s2[i]) != mp1.end()) mp2[s2[i]]++;
            }
    
            int left = 0, right = m - 1;
            while(right < n) {
                if(mp1.size() == mp2.size()) {
                    int flag = true;
                    for(auto x : mp1) {
                        if(x.second != mp2[x.first]) {
                            flag = false;
                            break;
                        }
                    }
                    if(flag) return true;
                }
    
                if(mp1.find(s2[left]) != mp1.end()) {
                    mp2[s2[left]]--;
                    if(mp2[s2[left]] == 0) mp2.erase(s2[left]);
                }
                left++;
                right++;
                if(right < n && mp1.find(s2[right]) != mp1.end()) mp2[s2[right]]++;
    
            }
            return false;
        }
    };

/*

Idea:
------
We need to determine whether any substring of

s2

is a permutation of

s1.

A permutation contains exactly the same characters with
the same frequencies.

Instead of generating every permutation of

s1,

we slide a window of length

|s1|

over

s2

and compare the character frequencies.

If any window has the same frequency distribution as

s1,

then that window is a permutation of

s1.

------------------------------------------------------------

Algorithm:
----------

1.

Store the frequency of every character in

s1

using

mp1.

------------------------------------------------------------

2.

Build the frequency map

mp2

for the first window of length

m

in

s2.

Only characters that exist in

mp1

are stored since all other characters are irrelevant.

------------------------------------------------------------

3.

Maintain a sliding window of size

m

using two pointers

left

and

right.

------------------------------------------------------------

4.

For every window,

first check whether both maps contain the same number of
distinct characters.

If not,

they cannot be equal.

------------------------------------------------------------

5.

If the sizes are equal,

compare the frequency of every character in

mp1

with

mp2.

If every frequency matches,

a permutation has been found.

Return

true.

------------------------------------------------------------

6.

Slide the window by one position.

• Remove the character leaving the window.

• If its frequency becomes zero,

erase it from

mp2

to keep the map compact.

• Add the new character entering the window.

------------------------------------------------------------

7.

Repeat until every window has been processed.

If no matching window is found,

return

false.

------------------------------------------------------------

Why Does This Work?
-------------------

Every permutation of

s1

must have exactly

m

characters.

Therefore,

only substrings of length

m

need to be considered.

The sliding window ensures that every such substring is
processed exactly once.

If a window has exactly the same character frequencies
as

s1,

then rearranging its characters would produce

s1,

which means that window is a valid permutation.

------------------------------------------------------------

Example:
--------

s1 =

"ab"

s2 =

"eidbaooo"

Frequency of

s1

a → 1

b → 1

--------------------------------

Window

"ei"

No matching frequencies.

--------------------------------

Window

"id"

No match.

--------------------------------

Window

"db"

b → 1

Need

a

also.

No match.

--------------------------------

Window

"ba"

a → 1

b → 1

Frequencies match.

Return

true.

------------------------------------------------------------

Why Ignore Other Characters?
----------------------------

Suppose

s1 = "abc"

Current window

"xab"

Character

'x'

does not exist in

s1,

so it can never contribute toward forming a valid
permutation.

Ignoring such characters keeps

mp2

smaller while still allowing correct frequency
comparisons.

------------------------------------------------------------

Time Complexity:
----------------

Building the frequency maps:

O(m)

Sliding the window:

O(n)

For each window,

at most the distinct characters of

s1

are compared.

Overall:

O(n × d)

where

d

is the number of distinct characters in

s1.

Since lowercase English letters are limited to 26,

this is effectively

O(n).

------------------------------------------------------------

Space Complexity:
-----------------

O(d)

where

d

is the number of distinct characters in

s1.

In the worst case,

d ≤ 26,

so the extra space is constant.

*/

// Version 2:
class Solution {
    public:
        bool checkInclusion(string s1, string s2) {
            int n = s1.size(), m = s2.size();
            if(n > m) return false;
    
            unordered_map<char, int> mp1;
            for(auto x : s1) mp1[x]++;
    
            for(int i = 0; i < m - n + 1; i++) {
                unordered_map<char, int> mp2;
                for(int j = i; j < i + n; j++) mp2[s2[j]]++;
                if(mp1 == mp2) return true;
            }    
    
            return false;
        }
    };

/*
    LeetCode 567 - Permutation in String
    ------------------------------------------------------------

    Approach:
    ------------------------------------------------------------

    We need to determine whether s2 contains a substring that is a
    permutation of s1.

    A permutation changes only the order of characters.

    Therefore, two strings are permutations of each other if and only if
    they contain exactly the same frequency of every character.

    So the problem can be converted into:

        Does s2 contain a substring of length n whose character-frequency
        map is exactly the same as the frequency map of s1?

    where:

        n = s1.size()


    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    Every permutation of s1 has exactly the same length as s1.

    Therefore, we only need to check substrings of s2 having length:

        n = s1.size()

    For example:

        s1 = "ab"

    Its permutations are:

        "ab"
        "ba"

    Both contain:

        a -> 1
        b -> 1

    So instead of generating permutations, we can simply compare
    character-frequency maps.


    ------------------------------------------------------------
    Step 1: Handle Impossible Case
    ------------------------------------------------------------

    If:

        n > m

    where:

        n = s1.size()
        m = s2.size()

    then s2 cannot possibly contain a substring of length n.

    Therefore:

        if(n > m) return false;


    Example:

        s1 = "abc"
        s2 = "ab"

        n = 3
        m = 2

    There is no substring of s2 of length 3.

    So the answer is immediately false.


    ------------------------------------------------------------
    Step 2: Build Frequency Map for s1
    ------------------------------------------------------------

    We create:

        unordered_map<char, int> mp1;

    and count every character of s1:

        for(auto x : s1)
            mp1[x]++;


    Example:

        s1 = "abbc"

    Then:

        mp1:

        a -> 1
        b -> 2
        c -> 1


    Any substring that is a permutation of s1 must have exactly this
    frequency distribution.


    ------------------------------------------------------------
    Step 3: Check Every Length-n Window in s2
    ------------------------------------------------------------

    Since every permutation of s1 has length n, we check every substring
    of s2 having length n.

    The starting index ranges from:

        0

    to:

        m - n

    Therefore:

        for(int i = 0; i < m - n + 1; i++)


    For every starting position i, the corresponding window is:

        s2[i ... i+n-1]


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

        s1 = "ab"
        s2 = "eidbaooo"

    Here:

        n = 2
        m = 8

    The windows of length 2 are:

        "ei"
        "id"
        "db"
        "ba"
        "ao"
        "oo"
        "oo"


    We check each one.

    The window:

        "ba"

    has:

        b -> 1
        a -> 1

    which is exactly the same frequency distribution as:

        "ab"

    Therefore, "ba" is a permutation of s1 and we return true.


    ------------------------------------------------------------
    Step 4: Build Frequency Map for Current Window
    ------------------------------------------------------------

    For every starting index i, we create:

        unordered_map<char, int> mp2;

    Then we traverse the n characters of the current window:

        for(int j = i; j < i + n; j++)
            mp2[s2[j]]++;


    So mp2 represents the character frequencies of:

        s2[i ... i+n-1]


    ------------------------------------------------------------
    Step 5: Compare the Two Frequency Maps
    ------------------------------------------------------------

    We now compare:

        mp1 == mp2

    If they are equal, the current window contains exactly the same
    characters with exactly the same frequencies as s1.

    Therefore, the current window is a permutation of s1.

    So:

        if(mp1 == mp2)
            return true;


    If no window matches, we return:

        false


    ------------------------------------------------------------
    Why Comparing Frequency Maps Is Sufficient:
    ------------------------------------------------------------

    Consider:

        s1 = "abb"

    Its frequency map is:

        a -> 1
        b -> 2


    Possible permutations include:

        "abb"
        "bab"
        "bba"

    Every one of them has exactly:

        a -> 1
        b -> 2


    Therefore, we do not care about the ordering of characters.

    We only care about their frequencies.

    If a length-n substring has the same frequency map, it MUST be a
    permutation of s1.


    ------------------------------------------------------------
    Detailed Example:
    ------------------------------------------------------------

        s1 = "ab"
        s2 = "eidbaooo"


    First:

        mp1 = {
            a : 1,
            b : 1
        }


    Window 1:

        "ei"

        mp2 = {
            e : 1,
            i : 1
        }

        mp1 != mp2

        Continue.


    Window 2:

        "id"

        mp2 = {
            i : 1,
            d : 1
        }

        mp1 != mp2

        Continue.


    Window 3:

        "db"

        mp2 = {
            d : 1,
            b : 1
        }

        mp1 != mp2

        Continue.


    Window 4:

        "ba"

        mp2 = {
            b : 1,
            a : 1
        }

        mp1 == mp2

        Therefore:

            "ba" is a permutation of "ab"

        Return true.


    ------------------------------------------------------------
    Why Every Possible Answer Is Checked:
    ------------------------------------------------------------

    Any valid permutation of s1 must have length exactly n.

    Every length-n substring of s2 has exactly one starting index i in:

        [0, m-n]

    The outer loop checks every such starting index.

    Therefore, no possible permutation window can be skipped.


    ------------------------------------------------------------
    Meaning of the Two Maps:
    ------------------------------------------------------------

        mp1
        ----

    Stores the required character frequencies.

    It never changes because s1 never changes.


        mp2
        ----

    Stores the character frequencies of the current substring of s2.

    It is recreated for every starting position.


    So the comparison is essentially:

        Required frequencies
                 ==
        Current window frequencies

                 ↓

              true
                 ↓

        Found a permutation


    ------------------------------------------------------------
    Why We Do Not Generate Permutations:
    ------------------------------------------------------------

    A direct approach could try to generate all permutations of s1.

    But a string of length n can have up to:

        n!

    permutations.

    This becomes extremely expensive even for relatively small n.

    The frequency-map observation avoids this completely.

    Instead of asking:

        "Which permutation is this?"

    we ask:

        "Does this window contain the same characters with the same
         frequencies?"

    That is enough.


    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    Let:

        n = s1.size()
        m = s2.size()


    Building mp1:

        O(n)


    Number of windows in s2:

        m - n + 1


    For every window, we scan n characters to construct mp2:

        O(n)


    Therefore, the total complexity is:

        O(n + (m-n+1) * n)

    which is:

        O(m * n)


    The map comparison also depends on the number of distinct characters,
    but because the problem uses lowercase English letters, the number
    of possible distinct characters is bounded by 26.


    ------------------------------------------------------------
    Space Complexity:
    ------------------------------------------------------------

    We store two frequency maps:

        mp1
        mp2

    Since there are at most 26 lowercase English characters:

        O(26) = O(1)


    Therefore, auxiliary space is:

        O(1)


    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    A permutation does not change character frequencies.

    Therefore:

        permutation of s1
              ↓
        same character counts
              ↓
        check every length-|s1| window in s2


    The solution uses:

        1. Frequency map of s1
        2. Every fixed-size window of s2
        3. Frequency map of the current window
        4. Compare the two maps


    ------------------------------------------------------------
    Main Takeaway:
    ------------------------------------------------------------

    The important transformation is:

        "Is some permutation of s1 present in s2?"

    becomes:

        "Does any substring of s2 of length s1.size() have exactly
         the same character frequencies as s1?"

    This avoids generating permutations entirely.

    The current implementation uses a straightforward fixed-window
    approach:

        for every window
            build its frequency map
            compare with mp1

    So the solution is simple and directly follows from the definition
    of a permutation.
*/