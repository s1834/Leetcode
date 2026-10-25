class Solution {
    public:
        int calculateScore(int a, int b) {
            int s1 = __builtin_popcount(a);
            int s2 = __builtin_popcount(b);
            if(s1 >= s2) return s1 * s2;
            return s2 / s1;
        }
    };

/*
Approach: Brian Kernighan Alternative / Built-in Popcount

Intuition:
----------
The score depends on the number of set bits (bits equal to 1) in the
binary representations of a and b.

We calculate:
- s1 = number of set bits in a.
- s2 = number of set bits in b.

Then apply the given scoring rules:
- If s1 >= s2, return s1 * s2.
- Otherwise, return s2 / s1 using integer division.

1. Count Set Bits
-----------------
int s1 = __builtin_popcount(a);
int s2 = __builtin_popcount(b);

__builtin_popcount(x) is a GCC/Clang built-in function that returns
the number of set bits in the binary representation of an integer x.

Example:
a = 14
Binary representation: 1110
Set bits = 3
Therefore, s1 = 3.

b = 6
Binary representation: 110
Set bits = 2
Therefore, s2 = 2.

2. Calculate the Score
----------------------
if(s1 >= s2) return s1 * s2;

If a has at least as many set bits as b, multiply their set-bit counts.

For the example above:
s1 = 3, s2 = 2
Score = 3 * 2 = 6.

Otherwise:
return s2 / s1;

If a has fewer set bits than b, divide s2 by s1.

C++ performs integer division here, so any fractional part is discarded.

Example:
a = 5  -> binary 101  -> s1 = 2
b = 15 -> binary 1111 -> s2 = 4

Since s1 < s2:
Score = 4 / 2 = 2.

3. Example Where Both Counts Are Equal
--------------------------------------
a = 10 -> binary 1010 -> s1 = 2
b = 12 -> binary 1100 -> s2 = 2

Since s1 >= s2:
Score = 2 * 2 = 4.

Notice that equality follows the multiplication branch.

4. Why This Works
-----------------
The problem defines the score entirely in terms of the number of set
bits in a and b.

__builtin_popcount() obtains these counts directly, and the conditional
statement applies exactly the corresponding scoring rule.

Since a and b are positive, both s1 and s2 are at least 1, so the
division s2 / s1 cannot divide by zero.

Complexity Analysis:
--------------------
Time Complexity: O(1) for the given integer constraints, since each
integer has a bounded number of bits.

Space Complexity: O(1), because only two integer variables are used.

Core Idea:
----------
Count the set bits of both integers using __builtin_popcount(), then
multiply the counts if s1 >= s2; otherwise, return s2 / s1.
*/