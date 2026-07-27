class Solution {
    public:
        int maxProduct(vector<int>& nums) {
            sort(nums.begin(), nums.end(), greater<int>());
            return (nums[0] - 1) * (nums[1] - 1);
        }
    };

/*

Idea:
------
We need to choose two different elements such that

(nums[i] - 1) × (nums[j] - 1)

is maximized.

Since subtracting

1

from both numbers preserves their relative ordering,

the maximum product is obtained by choosing the two
largest numbers in the array.

After sorting the array in descending order,

the first two elements are the largest values.

------------------------------------------------------------

Key Observation:
----------------

Suppose

a > b > c

Then

(a - 1) ≥ (b - 1) ≥ (c - 1)

Since all numbers are positive
(nums[i] ≥ 1),

multiplying larger values always produces a product that
is at least as large as multiplying smaller values.

Therefore,

the optimal pair must consist of the two largest
elements.

------------------------------------------------------------

Why Sorting Works:
------------------

Sorting the array in descending order gives

Largest

↓

nums[0]

Second Largest

↓

nums[1]

Every other element is less than or equal to

nums[1].

Hence,

no pair involving another element can produce a larger
value than

(nums[0] - 1) × (nums[1] - 1).

------------------------------------------------------------

Algorithm:
----------

Step 1

Sort the array in descending order.

------------------------------------------------------------

Step 2

Take the two largest elements

nums[0]

and

nums[1].

------------------------------------------------------------

Step 3

Compute

(nums[0] - 1)

×

(nums[1] - 1)

------------------------------------------------------------

Step 4

Return the result.

------------------------------------------------------------

Why Does This Work?
-------------------

Subtracting

1

from every element simply shifts every value by the same
amount.

The ordering of the numbers remains unchanged.

Since all adjusted values

(nums[i] - 1)

are non-negative,

their product is maximized by choosing the two largest
adjusted values,

which correspond exactly to the two largest original
numbers.

Thus,

sorting the array and selecting the first two elements
always gives the maximum possible product.

------------------------------------------------------------

Example:
--------

nums =

[3,4,5,2]

Sorted

↓

[5,4,3,2]

Compute

(5 - 1)

×

(4 - 1)

=

4 × 3

=

12

Answer = 12

------------------------------------------------------------

Example:
--------

nums =

[1,5,4,5]

Sorted

↓

[5,5,4,1]

Compute

(5 - 1)

×

(5 - 1)

=

4 × 4

=

16

Answer = 16

------------------------------------------------------------

Example:
--------

nums =

[3,7]

Sorted

↓

[7,3]

Compute

(7 - 1)

×

(3 - 1)

=

6 × 2

=

12

Answer = 12

------------------------------------------------------------

Mathematical Explanation:
-------------------------

Let

a ≥ b ≥ c ≥ ...

be the array after sorting.

Then

(a - 1) ≥ (b - 1) ≥ (c - 1)

Since every adjusted value is non-negative,

for any

x ≤ a - 1

and

y ≤ b - 1,

we have

x × y

≤

(a - 1) × (b - 1)

Therefore,

choosing the two largest elements always produces the
maximum product.

------------------------------------------------------------

Time Complexity:
----------------

Sorting the array takes

O(n log n)

Computing the final product takes

O(1)

Overall Time Complexity:

O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

The sorting is performed in-place (ignoring the sorting
algorithm's internal recursion stack).

Auxiliary Space:

O(1)

------------------------------------------------------------

Note:
-----

An optimal solution exists in

O(n)

time by scanning the array once and keeping track of the
largest and second-largest elements without sorting.

*/