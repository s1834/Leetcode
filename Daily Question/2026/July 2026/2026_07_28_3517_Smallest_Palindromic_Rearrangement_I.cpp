class Solution {
    public:
        string smallestPalindrome(string s) {
            map<char, int> mp;
            for(auto x : s) mp[x]++;
    
            int start = 0, end = s.size() - 1;
            for(auto &x : mp) {
                while(x.second >= 2) {
                    s[start] = x.first;
                    s[end] = x.first;
                    x.second -= 2;
                    start++;
                    end--;
                }
            }
            return s;
        }
    };

/*

Idea:
------
Since the given string is already guaranteed to be a palindrome,

its character frequencies satisfy the following property:

• Every character appears an even number of times,
  except possibly one character (for odd-length strings).

To obtain the lexicographically smallest palindromic
rearrangement,

we should place the smallest available characters at the
beginning of the palindrome.

Because a palindrome is symmetric,

whenever we place a character at the left end, we must
place the same character at the corresponding position on
the right end.

------------------------------------------------------------

Key Observation:
----------------

The left half of a palindrome completely determines the
right half.

Therefore,

to make the entire palindrome lexicographically smallest,

it is sufficient to make its left half as small as
possible.

This is achieved by always using the smallest available
character first.

------------------------------------------------------------

Why a Map?
----------

A map stores characters in

ascending lexicographical order.

For example,

'a'

↓

'b'

↓

'c'

↓

...

↓

'z'

Thus,

iterating over the map naturally processes characters
from smallest to largest.

------------------------------------------------------------

Algorithm:
----------

Step 1

Count the frequency of every character.

------------------------------------------------------------

Step 2

Maintain two pointers

start

(beginning of the string)

and

end

(end of the string).

------------------------------------------------------------

Step 3

Traverse the characters in increasing alphabetical order.

------------------------------------------------------------

Step 4

While the current character appears at least twice,

place one occurrence at

start

and one occurrence at

end.

Decrease its frequency by

2.

Move both pointers inward.

------------------------------------------------------------

Step 5

If the string has odd length,

one character will have frequency

1.

Since the input string is already a palindrome,

this character naturally remains in the middle position.

------------------------------------------------------------

Step 6

Return the modified string.

------------------------------------------------------------

Why Does This Work?
-------------------

A palindrome requires matching characters on both ends.

Whenever we have two copies of a character,

they must occupy symmetric positions.

To obtain the smallest lexicographical order,

the earliest positions in the string should contain the
smallest possible characters.

Since the map processes characters in sorted order,

the smallest characters are always placed at the outermost
positions first.

Larger characters are placed only after all smaller
characters have been exhausted.

Thus,

the left half becomes lexicographically minimal.

Since the right half is completely determined by symmetry,

the entire palindrome is also lexicographically smallest.

------------------------------------------------------------

Example:
--------

Input

s = "babab"

Frequency

a → 2

b → 3

--------------------------------

Initially

start = 0

end = 4

--------------------------------

Character 'a'

Frequency = 2

Place

a _ _ _ a

Frequency becomes

0

--------------------------------

Character 'b'

Frequency = 3

Place

a b _ b a

Frequency becomes

1

The remaining

'b'

stays in the middle.

Result

"abbba"

------------------------------------------------------------

Example:
--------

Input

s = "daccad"

Frequency

a → 2

c → 2

d → 2

--------------------------------

Place

a _ _ _ _ a

↓

a c _ _ c a

↓

a c d d c a

Result

"acddca"

------------------------------------------------------------

Mathematical Explanation:
-------------------------

Let the sorted characters be

c₁ < c₂ < ... < cₖ.

For every character,

we place all possible pairs before considering the next
larger character.

Suppose a larger character

c₂

is placed before a smaller character

c₁

at some left position.

Swapping them keeps the palindrome valid because both
characters are swapped together with their symmetric
counterparts.

The first differing position now contains

c₁ < c₂,

making the resulting palindrome lexicographically smaller.

Therefore,

every optimal palindrome must place all possible pairs of
smaller characters before any larger character.

This is exactly what the algorithm does.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm always constructs the
lexicographically smallest palindromic rearrangement.

At every step,

the algorithm selects the smallest available character
that still has at least two remaining occurrences.

These two occurrences are placed at the current outermost
positions.

Assume there exists another valid palindrome that is
lexicographically smaller.

Then,

at the first position where the two palindromes differ,

that palindrome must contain a character smaller than the
one chosen by the algorithm.

However,

the algorithm always chooses the smallest available
character at every step.

Therefore,

such a smaller character cannot exist.

This contradicts the assumption.

Hence,

the constructed palindrome is lexicographically smallest.

------------------------------------------------------------

Time Complexity:
----------------

Let

n

be the length of the string.

Counting frequencies

O(n)

--------------------------------

Iterating over the map

O(26)

(for lowercase English letters)

--------------------------------

Placing all character pairs

O(n)

Overall Time Complexity

O(n)

------------------------------------------------------------

Space Complexity:
-----------------

Frequency map

O(26)

which is constant for lowercase English letters.

Overall Auxiliary Space

O(1)

*/