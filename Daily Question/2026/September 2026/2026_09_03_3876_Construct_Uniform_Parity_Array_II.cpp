class Solution {
    public:
        bool uniformArray(vector<int>& nums1) {
            int smallest = *min_element(nums1.begin(), nums1.end());
            if(smallest % 2) return true; // smallest is odd
    
            // else check if all are even
             for(int &x : nums1) if(x % 2) return false;
    
             return true;
        }
    };

/*
LeetCode 3876. Uniform Array

Approach:
---------

The key observation is based on the parity (odd/even nature) of
the smallest element in the array.

There are two possible cases:

    1. The smallest element is odd.
    2. The smallest element is even.

------------------------------------------------------------

Case 1: Smallest Element Is Odd
-------------------------------

    if(smallest % 2) return true;

If the smallest element is odd, the array satisfies the required
condition immediately.

Therefore, we return:

    true

------------------------------------------------------------

Case 2: Smallest Element Is Even
--------------------------------

If the smallest element is even, then every element in the array
must also be even.

We check every element:

    for(int &x : nums1)
        if(x % 2)
            return false;

If we find even one odd element, the array is not uniform.

For example:

    nums = [2, 4, 7, 8]

The smallest element is:

    2 -> even

But:

    7 -> odd

Since an odd element exists while the smallest element is even,
the array does not satisfy the condition.

Therefore:

    return false;

------------------------------------------------------------

If All Elements Are Even
------------------------

If the smallest element is even and we finish checking the entire
array without finding an odd number:

    return true;

For example:

    nums = [2, 4, 6, 8]

Smallest element:

    2 -> even

All elements are even.

Therefore:

    true

------------------------------------------------------------

Example 1:
----------

    nums = [3, 8, 10]

Smallest:

    3

Since:

    3 % 2 != 0

The smallest element is odd.

Immediately return:

    true

------------------------------------------------------------

Example 2:
----------

    nums = [2, 4, 6, 8]

Smallest:

    2 -> even

Check every element:

    2 -> even
    4 -> even
    6 -> even
    8 -> even

All elements are even.

Return:

    true

------------------------------------------------------------

Example 3:
----------

    nums = [2, 4, 7, 8]

Smallest:

    2 -> even

Check every element:

    2 -> even
    4 -> even
    7 -> odd

An odd element is found.

Return:

    false

------------------------------------------------------------

Algorithm:
----------

    1. Find the smallest element.

    2. If the smallest element is odd:
           return true.

    3. Otherwise, check every element.

    4. If any element is odd:
           return false.

    5. Otherwise:
           return true.

------------------------------------------------------------

Time Complexity:
----------------

Finding the minimum:

    O(n)

Checking all elements:

    O(n)

Total:

    O(n)

------------------------------------------------------------

Space Complexity:
-----------------

We only use a few variables.

Therefore:

    O(1)

------------------------------------------------------------

Core Idea:
----------

    Smallest element is odd
            |
            v
        Return true

    Smallest element is even
            |
            v
    Check every element
            |
       +----+----+
       |         |
    Odd found  All even
       |         |
       v         v
    false       true
*/