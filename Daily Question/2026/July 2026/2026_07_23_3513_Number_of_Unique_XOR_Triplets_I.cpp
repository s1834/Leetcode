class Solution {
    public:
        int uniqueXorTriplets(vector<int>& nums) {
            int n = nums.size();
            if(n == 1 || n == 2) return n;
            int ans = 1;
            while(ans <= n) ans *= 2;
            return ans;
        }
    };

/*

Idea:
------
The array is a permutation of

[1, n].

Instead of generating every possible triplet,

observe the range of possible XOR values using bit
properties.

The answer depends only on

n,

not on the actual ordering of the permutation.

------------------------------------------------------------

Key Bit Manipulation Observation:
---------------------------------

Every number in the array lies in the range

[1, n].

Suppose

n = 13

Binary

1   = 0001

13  = 1101

The largest number determines the maximum number of bits
needed.

If

n

requires

k

bits,

then every number in the array also fits within those

k

bits.

------------------------------------------------------------

Property of XOR:
----------------

XOR works independently on each bit.

For every bit position,

0 XOR 0 = 0

0 XOR 1 = 1

1 XOR 0 = 1

1 XOR 1 = 0

Most importantly,

XOR never creates a new higher-order bit.

For example,

5 = 0101

6 = 0110

5 XOR 6 = 0011

The answer still fits within the same number of bits.

Similarly,

a XOR b XOR c

also remains within those same

k

bits.

Therefore,

every possible XOR value must lie in the range

0

to

2^k - 1.

So there can be at most

2^k

distinct XOR values.

------------------------------------------------------------

Why Is Every k-bit Value Obtainable?
------------------------------------

For

n ≥ 3,

the permutation contains enough distinct numbers to
generate every possible

k-bit

value using the XOR of three elements.

Thus,

all integers in the range

0

to

2^k - 1

are achievable.

Hence,

the number of unique XOR triplets is exactly

2^k.

------------------------------------------------------------

Why Special Cases for n = 1 and n = 2?
--------------------------------------

n = 1

Numbers

[1]

Possible XOR

1 XOR 1 XOR 1 = 1

Only one unique value.

Answer = 1

--------------------------------

n = 2

Numbers

[1,2]

Possible XOR values

1

2

Only two unique values.

Answer = 2

The property that every

k-bit

value is achievable starts only when

n ≥ 3.

------------------------------------------------------------

How the Code Computes 2^k:
--------------------------

Initially,

ans = 1

Repeatedly double

ans

until

ans > n.

Suppose

n = 5

ans

1 → 2 → 4 → 8

The loop stops at

8,

which is the smallest power of two strictly greater than

5.

Since

8 = 2³,

this means numbers up to

5

require

3

bits.

Hence,

there are

2³ = 8

possible XOR values.

Similarly,

n = 13

ans

1 → 2 → 4 → 8 → 16

The answer becomes

16 = 2⁴,

because

13

requires

4

bits.

------------------------------------------------------------

Example:
--------

n = 3

Numbers

[1,2,3]

Binary

1 = 01

2 = 10

3 = 11

Maximum bits = 2

Possible XOR values

0

1

2

3

Total unique values

2² = 4

------------------------------------------------------------

Example:
--------

n = 5

Maximum number

5 = 101

Requires

3

bits.

Every XOR result also fits within

3

bits.

Possible values

0

1

2

3

4

5

6

7

Total

2³ = 8

------------------------------------------------------------

Why Does This Work?
-------------------

The largest element determines the number of bits needed
to represent every number in the array.

XOR never increases the number of required bits.

Therefore,

every XOR result must lie within the

k-bit

range.

For

n ≥ 3,

every possible

k-bit

integer can be formed as the XOR of three elements from
the permutation.

Thus,

the answer is simply the total number of

k-bit

integers,

which equals

2^k.

The loop computes exactly this value by finding the
smallest power of two greater than

n.

------------------------------------------------------------

Time Complexity:
----------------

O(log n)

The loop doubles

ans

until it exceeds

n.

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

Only one integer variable is used.

*/