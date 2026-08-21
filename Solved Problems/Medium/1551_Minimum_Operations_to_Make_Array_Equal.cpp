class Solution {
    public:
        int minOperations(int n) {
            vector<int> v(n);
            for(int i = 0; i < n; i++) v[i] = (2 * i) + 1;
            
            int target = v[n / 2];
            if(n % 2 == 0) target--; 
            
            int ans = 0;
            for(int i = 0; i < n / 2; i++) ans += abs(v[i] - target);
            return ans;
        }
    };

/*
LeetCode 1551. Minimum Operations to Make Array Equal

Approach:
---------

The array is:

    [1, 3, 5, 7, ..., 2n - 1]

We need to make every element equal.

In one operation, we can:

    increase one element by 1
    AND
    decrease another element by 1

So one operation moves 1 unit from a larger element to a smaller
element.

------------------------------------------------------------

Key Observation:
----------------

The array contains consecutive odd numbers:

    1, 3, 5, 7, ...

Since the array is already sorted and symmetric around its
middle, the minimum number of operations is obtained by making
all elements equal to the middle value.

For example:

    n = 5

    [1, 3, 5, 7, 9]

The target is:

    5

We need to move:

    5 - 1 = 4
    5 - 3 = 2

units from the larger elements to the smaller elements.

So:

    answer = 4 + 2 = 6

We only calculate the left half because the right half provides
exactly the same amount of excess.

------------------------------------------------------------

Create the Array:
-----------------

    vector<int> v(n);

    for(int i = 0; i < n; i++)
        v[i] = (2 * i) + 1;

This generates:

    i = 0 -> 1
    i = 1 -> 3
    i = 2 -> 5
    i = 3 -> 7
    ...

So:

    v = [1, 3, 5, ..., 2n - 1]

------------------------------------------------------------

Finding the Target:
-------------------

    int target = v[n / 2];

For odd n, the middle element is exactly the target.

Example:

    n = 5

    v = [1, 3, 5, 7, 9]

    n / 2 = 2

    target = v[2] = 5

------------------------------------------------------------

Why target-- for Even n?
-------------------------

For even n, there are two middle elements.

Example:

    n = 4

    v = [1, 3, 5, 7]

The two middle values are:

    3 and 5

There is no single middle element.

The optimal target lies between them:

    4

But the code uses:

    target = v[n / 2] = v[2] = 5

and then:

    if(n % 2 == 0)
        target--;

So:

    target = 4

This is the correct optimal target.

------------------------------------------------------------

Why Is the Middle the Optimal Target?
--------------------------------------

The array is symmetric:

    1, 3, 5, 7, 9

Distances from the middle value 5 are:

    4, 2, 0, 2, 4

If we choose a target that is too small, we need more
increments from the larger elements.

If we choose a target that is too large, we need more
decrements from the smaller elements.

Therefore, the middle point minimizes the total amount of
movement.

For even n, the optimal target is between the two middle
elements.

------------------------------------------------------------

Only Calculate the Left Half:
-----------------------------

    for(int i = 0; i < n / 2; i++)
        ans += abs(v[i] - target);

We only process:

    i < n / 2

because the array is symmetric around the target.

For every element on the left, there is a corresponding element
on the right that needs exactly the same amount of adjustment.

Example:

    [1, 3, 5, 7, 9]
           target = 5

Left side:

    |1 - 5| = 4
    |3 - 5| = 2

Right side:

    |7 - 5| = 2
    |9 - 5| = 4

The two sides contribute equally.

So instead of counting both sides, we count only the left side.

------------------------------------------------------------

Why Does Each Difference Represent Operations?
-----------------------------------------------

Suppose:

    [1, 3, 5, 7, 9]

target:

    5

The element 1 needs:

    5 - 1 = 4

additional units.

The element 9 has:

    9 - 5 = 4

extra units.

We can transfer these units between the two elements:

    1 -> 2
    9 -> 8

then:

    2 -> 3
    8 -> 7

then:

    3 -> 4
    7 -> 6

then:

    4 -> 5
    6 -> 5

This takes:

    4 operations

for this pair.

So the difference between the smaller element and target is
exactly the number of operations contributed by that pair.

------------------------------------------------------------

Example:
--------

n = 6

Array:

    [1, 3, 5, 7, 9, 11]

Middle values:

    5 and 7

Optimal target:

    6

Left half:

    1, 3, 5

Differences:

    |1 - 6| = 5
    |3 - 6| = 3
    |5 - 6| = 1

Total:

    5 + 3 + 1 = 9

So:

    answer = 9

The right half has:

    |7 - 6| = 1
    |9 - 6| = 3
    |11 - 6| = 5

which is the same total.

------------------------------------------------------------

Overall Flow:
-------------

        Create odd-number array
                  |
                  ↓
        Find middle target
                  |
                  ↓
      Adjust target for even n
                  |
                  ↓
      Calculate differences for
          only left half
                  |
                  ↓
              answer

------------------------------------------------------------

Complexity:
-----------

Creating the array takes:

    O(n)

The loop also takes:

    O(n)

Therefore:

    Time Complexity: O(n)

The array stores n elements:

    Space Complexity: O(n)

------------------------------------------------------------

Main Idea to Remember:
----------------------

The array:

    [1, 3, 5, ..., 2n - 1]

is symmetric.

The optimal value to make every element equal to is the middle
value (or the value between the two middle elements when n is
even).

Because the array is symmetric, we only need to calculate the
cost for the left half:

    ans += abs(v[i] - target)

The corresponding elements on the right require exactly the same
number of operations, so they are already accounted for.

Key pattern:

    Find the median/middle target
        +
    Calculate movement from one side
        =
    Minimum number of operations
*/