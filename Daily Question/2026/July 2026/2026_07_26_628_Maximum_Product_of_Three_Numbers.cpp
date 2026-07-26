class Solution {
    public:
        int maximumProduct(vector<int>& nums) {
            sort(nums.begin(), nums.end(), greater<int>());
            return max(nums[0] * nums[1] * nums[2], nums[0] * nums[nums.size() - 1] * nums[nums.size() - 2]);
        }
    };

/*

Idea:
------
The maximum product of three numbers can come from only
two possible combinations after sorting the array.

1.

The three largest numbers.

2.

The largest positive number together with the two most
negative numbers.

After sorting,

we simply compute both products and return the larger
one.

------------------------------------------------------------

Key Observation:
----------------

Negative numbers play an important role.

Since

Negative × Negative = Positive,

two very small (highly negative) numbers can produce a
large positive product.

Therefore,

the maximum product is **not always** obtained using the
three largest values.

------------------------------------------------------------

Possible Cases:
---------------

Case 1

Three Largest Numbers

Example

[1,2,3,4]

Maximum Product

=

4 × 3 × 2

=

24

--------------------------------

Case 2

Largest Positive + Two Smallest Negatives

Example

[-10,-10,2,5]

Three largest numbers

5 × 2 × (-10)

=

-100

--------------------------------

Using two negatives

5 × (-10) × (-10)

=

500

which is much larger.

------------------------------------------------------------

Why Only These Two Cases?
-------------------------

After sorting in descending order,

nums[0]

is always the largest element.

To maximize the product,

this largest element should always be included.

The remaining two numbers can only be chosen in one of
two optimal ways:

1.

The next two largest numbers.

2.

The two smallest numbers (most negative).

Any other combination cannot produce a larger product.

Therefore,

checking only these two cases is sufficient.

------------------------------------------------------------

Algorithm:
----------

Step 1

Sort the array in descending order.

------------------------------------------------------------

Step 2

Compute the product of the three largest elements.

largestProduct

=

nums[0]

×

nums[1]

×

nums[2]

------------------------------------------------------------

Step 3

Compute the product of the largest element and the two
smallest elements.

negativeProduct

=

nums[0]

×

nums[n-1]

×

nums[n-2]

Since the array is sorted in descending order,

the last two elements are the most negative values.

------------------------------------------------------------

Step 4

Return the larger of these two products.

------------------------------------------------------------

Why Does This Work?
-------------------

Sorting arranges the numbers from largest to smallest.

The largest number should always be part of the maximum
product.

The remaining two numbers either

• maximize the product directly by being the next two
  largest values,

or

• maximize it indirectly by being two very negative
  numbers whose product becomes positive.

Since these are the only two possible optimal choices,

taking the maximum of their products always gives the
correct answer.

------------------------------------------------------------

Example:
--------

nums =

[1,2,3,4]

Sorted

[4,3,2,1]

--------------------------------

Three largest

4 × 3 × 2

=

24

--------------------------------

Largest + two smallest

4 × 1 × 2

=

8

Answer = 24

------------------------------------------------------------

Example:
--------

nums =

[-10,-10,2,5]

Sorted

[5,2,-10,-10]

--------------------------------

Three largest

5 × 2 × (-10)

=

-100

--------------------------------

Largest + two smallest

5 × (-10) × (-10)

=

500

Answer = 500

------------------------------------------------------------

Example:
--------

nums =

[-5,-4,-3]

Sorted

[-3,-4,-5]

--------------------------------

Three largest

(-3) × (-4) × (-5)

=

-60

--------------------------------

Largest + two smallest

(-3) × (-5) × (-4)

=

-60

Answer = -60

------------------------------------------------------------

Time Complexity:
----------------

Sorting the array takes

O(n log n)

All remaining computations are constant time.

Overall Time Complexity:

O(n log n)

------------------------------------------------------------

Space Complexity:
-----------------

The sorting is performed in-place (ignoring the sorting
algorithm's internal stack).

Auxiliary Space:

O(1)

*/