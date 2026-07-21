class Solution {
    public:
        int maxActiveSectionsAfterTrade(string s) {
            vector<int> zeros;
            int one = 0, zero = 0;
            for(auto x : s) {
                if(x == '0') zero++;
                else {
                    one++;
                    if(zero) zeros.push_back(zero);
                    zero = 0;
                }
            }
    
            if(zero) zeros.push_back(zero);
    
            int n = zeros.size(), mx = 0;
            for(int i = 0; i < n - 1; i++) mx = max(mx, zeros[i] + zeros[i + 1]);
    
            return mx + one;
        }
    };

/*

Idea:
------
The trade consists of two operations:

1.

Convert one contiguous block of

'1'

(surrounded by '0's)

into

'0's.

2.

Then convert one contiguous block of

'0'

(surrounded by '1's)

into

'1's.

Instead of simulating every possible trade,

observe what actually increases the number of active
sections.

------------------------------------------------------------

Key Observation:
----------------

Suppose a valid block of

'1'

is surrounded by two blocks of zeros.

Example

000111000

↓

Remove

111

↓

000000000

Now the two neighboring zero blocks merge into one
larger zero block.

If the left zero block has length

L

and the right zero block has length

R,

then after removing the middle

'1'

block,

they become one zero block of length

L + R + length(removed ones).

When this merged zero block is converted into

'1',

the gain in active sections is exactly

L + R,

because the removed

'1'

block is restored during the second operation.

Therefore,

the only additional active sections we gain come from the
two neighboring zero blocks.

Hence,

we only need to maximize

L + R.

------------------------------------------------------------

Algorithm:
----------

1.

Count the total number of

'1'

characters.

This is the number of active sections before any trade.

------------------------------------------------------------

2.

Traverse the string and record the length of every zero
block in a vector.

For example,

"100010010"

Zero blocks

[3,2,1]

------------------------------------------------------------

3.

For every pair of consecutive zero blocks,

compute

zeros[i] + zeros[i + 1]

because these two blocks can be merged by removing the
single

'1'

block between them.

------------------------------------------------------------

4.

The maximum possible gain is the largest value of

zeros[i] + zeros[i + 1].

------------------------------------------------------------

5.

Final Answer

=

initial number of

'1'

+

maximum gain.

------------------------------------------------------------

Why Does This Work?
-------------------

A valid trade always removes one

'1'

block that lies between two zero blocks.

Removing it merges those two zero blocks.

When this merged zero block is converted back into

'1',

the removed

'1'

block is recovered, so there is no net loss from deleting
it.

The only extra active sections come from converting the
two neighboring zero blocks into

'1'.

Therefore,

maximizing

leftZeroBlock + rightZeroBlock

directly maximizes the total number of active sections.

------------------------------------------------------------

Example:
--------

s =

"1000100"

Total active sections

= 2

Zero blocks

[3,2]

--------------------------------

Possible gain

3 + 2 = 5

--------------------------------

Final Answer

2 + 5 = 7

------------------------------------------------------------

Another Example:
----------------

s =

"01010"

Active sections

= 2

Zero blocks

[1,1,1]

--------------------------------

Possible gains

1 + 1 = 2

1 + 1 = 2

Maximum gain = 2

--------------------------------

Final Answer

2 + 2 = 4

------------------------------------------------------------

Time Complexity:
----------------

O(n)

The string is traversed once to count active sections
and zero blocks, followed by one pass over the zero
blocks.

------------------------------------------------------------

Space Complexity:
-----------------

O(z)

where

z

is the number of zero blocks stored.

In the worst case,

z = O(n).

*/