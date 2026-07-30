class Solution {
    public:
        string gcdOfStrings(string str1, string str2) {
            // Check if both of them match
            if (str1 + str2 != str2 + str1) return "";
    
            // substring of gcd of both the lengths divides both of them
            return str1.substr(0, gcd(str1.size(), str2.size()));
        }
    };

/*

Idea:
------
We need to find the

largest string

that can repeatedly concatenate to form

both

input strings.

This is exactly analogous to finding the

Greatest Common Divisor (GCD)

of two numbers.

Instead of numbers,

we are finding the largest common repeating

pattern

of two strings.

The solution consists of two important observations.

1.

Both strings must be constructed from the same repeating
pattern.

2.

The length of the largest possible repeating pattern is the

GCD

of the two string lengths.

------------------------------------------------------------

Key Observation 1:
------------------

Suppose a string

X

is the common divisor of both strings.

Then

str1 = X repeated k times

str2 = X repeated m times

Since both strings are generated from the same base pattern,

their concatenations must satisfy

str1 + str2

=

str2 + str1

If this condition is false,

no common repeating pattern can exist.

------------------------------------------------------------

Why Does

str1 + str2 == str2 + str1

Matter?
----------------------------------

Suppose

str1 = "ABCABC"

str2 = "ABC"

Then

str1 + str2

=

ABCABCABC

str2 + str1

=

ABCABCABC

Equal

Therefore,

both strings come from the same repeating block.

------------------------------------------------------------

Counter Example

str1 = "ABAB"

str2 = "ABBA"

str1 + str2

=

ABABABBA

str2 + str1

=

ABBAABAB

Not Equal

Therefore,

no common repeating string exists.

Return

"".

------------------------------------------------------------

Key Observation 2:
------------------

If both strings are made from the same repeating pattern,

then

the largest possible repeating block must have length equal
to

gcd(length(str1), length(str2))

Why?

Suppose

str1

has length

12

and

str2

has length

18.

The common block length must divide

12

and

18.

The largest such length is

gcd(12,18)

=

6.

Therefore,

the answer must have length

6.

------------------------------------------------------------

Why GCD of Lengths?
-------------------

Suppose

str1 = "ABCABCABCABC"

Length

12

--------------------------------

str2 = "ABCABCABCABCABCABC"

Length

18

Both are repetitions of

"ABCABC"

whose length is

6.

Notice

6

is exactly

gcd(12,18).

Any larger length cannot divide both strings.

Any smaller length would not be the greatest common
divisor.

------------------------------------------------------------

Algorithm:
----------

Step 1

Check whether

str1 + str2

equals

str2 + str1.

------------------------------------------------------------

Step 2

If they are different,

return

""

because no common repeating string exists.

------------------------------------------------------------

Step 3

Compute

gcd(str1.length(), str2.length()).

------------------------------------------------------------

Step 4

Take the first

gcdLength

characters from

str1.

This substring is the largest possible common divisor
string.

------------------------------------------------------------

Step 5

Return the substring.

------------------------------------------------------------

Example 1:
----------

str1

=

"ABCABC"

str2

=

"ABC"

Concatenation

ABCABCABC

ABCABCABC

Equal

--------------------------------

Lengths

6

3

gcd

=

3

Take first

3

characters

"ABC"

Answer

"ABC"

------------------------------------------------------------

Example 2:
----------

str1

=

"ABABAB"

str2

=

"ABAB"

Concatenation

ABABABABAB

ABABABABAB

Equal

--------------------------------

Lengths

6

4

gcd

=

2

Take first

2

characters

"AB"

Answer

"AB"

------------------------------------------------------------

Example 3:
----------

str1

=

"LEET"

str2

=

"CODE"

Concatenation

LEETCODE

CODELEET

Not Equal

Therefore,

no repeating pattern exists.

Answer

""

------------------------------------------------------------

Mathematical Explanation:
-------------------------

Suppose

str1 = X repeated a times

str2 = X repeated b times

If

|X|

is the length of the repeating block,

then

|str1| = a × |X|

|str2| = b × |X|

Therefore,

|X|

must divide both string lengths.

Hence,

|X|

must be a common divisor of

|str1|

and

|str2|.

The largest possible value satisfying this is

gcd(|str1|, |str2|).

Thus,

the largest divisor string has length equal to the GCD of
the two lengths.

------------------------------------------------------------

Visualization:
--------------

str1

ABCABCABCABC

↓

ABCABC

ABCABC

--------------------------------

str2

ABCABC

↓

ABCABC

Largest repeating block

↓

ABCABC

Length

↓

gcd(12,6)

=

6

------------------------------------------------------------

Why Does This Work?
-------------------

The concatenation check guarantees that both strings are
constructed from the same repeating pattern.

If this condition fails,

no divisor string can generate both strings.

Once this condition is satisfied,

the divisor string's length must divide both string lengths.

Therefore,

its maximum possible length is exactly the

greatest common divisor

of the two lengths.

Taking the prefix of this length produces the largest
possible repeating pattern shared by both strings.

------------------------------------------------------------

Correctness Proof:
------------------

We prove that the algorithm returns the largest common
divisor string.

First,

if

str1 + str2

is not equal to

str2 + str1,

then the strings cannot be generated by repeating the same
base pattern.

Hence,

no common divisor string exists,

and returning the empty string is correct.

Otherwise,

both strings are repetitions of the same primitive pattern.

Any divisor string must have a length that divides both

|str1|

and

|str2|.

Therefore,

its length must be a common divisor of the two lengths.

The largest possible such length is

gcd(|str1|, |str2|).

The prefix of

str1

having this length generates both strings by repeated
concatenation,

making it the largest common divisor string.

Thus,

the algorithm is correct.

------------------------------------------------------------

Time Complexity:
----------------

Let

n = |str1|

m = |str2|

Concatenation Comparison

O(n + m)

--------------------------------

GCD Computation

O(log(min(n,m)))

--------------------------------

Substring Extraction

O(gcdLength)

Worst Case

O(min(n,m))

Overall Time Complexity

O(n + m)

------------------------------------------------------------

Space Complexity:
-----------------

Ignoring the returned string,

only a few variables are used.

Auxiliary Space

O(1)

Including the returned substring,

Space Complexity

O(gcdLength)

------------------------------------------------------------

Note:
-----

The elegant part of this solution is the observation that
a string problem can be reduced to the mathematical concept
of the

Greatest Common Divisor (GCD).

The concatenation equality check verifies whether a common
base pattern exists,

while the GCD of the lengths determines the maximum size of
that pattern.

*/