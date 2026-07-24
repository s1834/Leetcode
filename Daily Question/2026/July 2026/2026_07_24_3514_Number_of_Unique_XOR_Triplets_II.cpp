class Solution {
    public:
        int uniqueXorTriplets(vector<int>& nums) {
            int n = nums.size();
    
            unordered_set<int> s1, s2;
            // Store all Pair XORs
            for(int i = 0; i < n; i++) {
                for(int j = i; j < n; j++) {
                    s1.insert(nums[i] ^ nums[j]);
                }
            }
    
            // find all triplet XORs
            for(auto x : s1) {
                for(auto y : nums) {
                    s2.insert(x ^ y);
                }
            }
    
            return s2.size();
        }
    };

/*

Idea:
------
We need to find the number of distinct values that can be
obtained by

nums[i] ^ nums[j] ^ nums[k]

where

i <= j <= k.

Instead of checking every triplet directly,

we break the computation into two stages:

1.

Compute all possible XOR values of every pair.

2.

Combine each pair XOR with every array element to obtain
all possible triplet XORs.

Using hash sets automatically removes duplicate values.

------------------------------------------------------------

Mathematical Observation:
-------------------------

XOR is associative and commutative.

That is,

(a ^ b) ^ c

=

a ^ (b ^ c)

=

a ^ b ^ c

Also,

the order of XOR operations does not matter.

Therefore,

we can first compute

pairXor = nums[i] ^ nums[j]

and later compute

pairXor ^ nums[k]

instead of calculating all three numbers together.

------------------------------------------------------------

Algorithm:
----------

Step 1:

Generate all possible pair XOR values.

For every

i

For every

j >= i

Compute

nums[i] ^ nums[j]

and insert it into

s1.

Since

s1

is a hash set,

duplicate XOR values are stored only once.

------------------------------------------------------------

Step 2:

Generate all possible triplet XOR values.

For every value

x

in

s1

For every element

y

in

nums

Compute

x ^ y

and insert it into

s2.

Again,

duplicates are automatically removed.

------------------------------------------------------------

Step 3:

Return

s2.size()

which represents the number of distinct triplet XOR
values.

------------------------------------------------------------

Why Does This Work?
-------------------

Every triplet XOR can be written as

(nums[i] ^ nums[j]) ^ nums[k]

The first stage generates every possible value of

nums[i] ^ nums[j].

The second stage combines each of these values with every
possible third element.

Therefore,

every valid triplet XOR is generated.

Since hash sets store only unique values,

the final size of

s2

is exactly the number of distinct triplet XOR results.

------------------------------------------------------------

Example:
--------

nums =

[1,2,3]

--------------------------------

Step 1

Pair XORs

1 ^ 1 = 0

1 ^ 2 = 3

1 ^ 3 = 2

2 ^ 2 = 0

2 ^ 3 = 1

3 ^ 3 = 0

Unique Pair XORs

s1 =

{0,1,2,3}

--------------------------------

Step 2

Combine every pair XOR with every element.

0 ^ {1,2,3}

=

{1,2,3}

--------------------------------

1 ^ {1,2,3}

=

{0,3,2}

--------------------------------

2 ^ {1,2,3}

=

{3,0,1}

--------------------------------

3 ^ {1,2,3}

=

{2,1,0}

--------------------------------

Distinct Triplet XORs

{0,1,2,3}

Answer = 4

------------------------------------------------------------

Why Use Hash Sets?
------------------

The same XOR value may be produced by many different
pairs or triplets.

Using

unordered_set

ensures that each XOR value is stored only once,

allowing us to directly count the number of unique
results.

------------------------------------------------------------

Time Complexity:
----------------

Generating all pair XORs:

O(n²)

--------------------------------

Generating all triplet XOR values:

There are at most

|s1|

unique pair XOR values.

For each,

we iterate over all

n

elements.

Time:

O(|s1| × n)

In the worst case,

|s1| = O(n²),

giving

O(n³)

------------------------------------------------------------

Space Complexity:
-----------------

O(|s1| + |s2|)

where

|s1|

is the number of distinct pair XOR values,

and

|s2|

is the number of distinct triplet XOR values.

In the worst case,

both can be

O(n²).

*/