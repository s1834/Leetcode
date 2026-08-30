class Solution {
    public:
        int minimumDeletions(vector<int>& nums) {
            int mx = 0, mn = 0, n = nums.size();
            for(int i = 1; i < n; i++) {
                if (nums[mx] < nums[i]) mx = i;
                if (nums[mn] > nums[i]) mn = i;
            }
            
            int front = max(mx, mn) + 1;
            int back = max(n - mx, n - mn);
            int both = min(mx, mn) + 1 + min(n - mx, n - mn);
            
            return min(both, min(front, back));
        }
    };

/*
LeetCode 2091. Removing Minimum and Maximum From Array

Approach:
---------

We need to remove both the minimum and maximum elements from nums.

The important observation is that we can only delete elements from:

    1. The front of the array
    2. The back of the array
    3. A combination of both front and back

So after finding the indices of the minimum and maximum elements,
we calculate the number of deletions required for all three
possibilities and return the minimum.

------------------------------------------------------------

1. Find the Indices of Minimum and Maximum
-------------------------------------------

    int mx = 0, mn = 0;

mx stores the index of the maximum element.

mn stores the index of the minimum element.

We start both at index 0 and traverse the remaining array.

    if(nums[mx] < nums[i]) mx = i;

If the current number is greater than the current maximum,
update the maximum index.

    if(nums[mn] > nums[i]) mn = i;

If the current number is smaller than the current minimum,
update the minimum index.

For example:

    nums = [2, 10, 7, 5, 1]

Indexes:

      0   1  2  3  4
    [ 2, 10, 7, 5, 1 ]

Maximum:

    10 -> index 1

Minimum:

    1 -> index 4

So:

    mx = 1
    mn = 4

------------------------------------------------------------

2. Remove Both Elements From the Front
--------------------------------------

If we remove elements only from the front, we must remove until
we reach whichever of min or max appears later in the array.

Therefore:

    front = max(mx, mn) + 1;

Why +1?

Because indices are 0-based.

For example:

    mx = 1
    mn = 4

The farther element is at index 4.

We must remove:

    index 0
    index 1
    index 2
    index 3
    index 4

Total:

    4 + 1 = 5

So:

    front = max(1, 4) + 1
          = 5

------------------------------------------------------------

3. Remove Both Elements From the Back
-------------------------------------

If we remove elements only from the back, we must remove until
we reach whichever of min or max is closer to the front.

The number of elements needed to remove an element at index i
from the back is:

    n - i

Therefore:

    back = max(n - mx, n - mn);

For example:

    n = 5
    mx = 1
    mn = 4

Removing maximum from back:

    n - mx
    = 5 - 1
    = 4

Removing minimum from back:

    n - mn
    = 5 - 4
    = 1

To remove both from the back, we need:

    max(4, 1)
    = 4

So:

    back = 4

------------------------------------------------------------

4. Remove One From the Front and One From the Back
---------------------------------------------------

Instead of removing both elements from the same side, we can
remove one from the front and the other from the back.

There are effectively two possibilities:

    Case 1:
        Remove the earlier index from the front
        Remove the later index from the back

    Case 2:
        Remove the later index from the front
        Remove the earlier index from the back

We only need the smaller option.

The earlier index is:

    min(mx, mn)

To remove it from the front:

    min(mx, mn) + 1

The later index is:

    max(mx, mn)

To remove it from the back:

    n - max(mx, mn)

So:

    both = min(mx, mn) + 1
           + n - max(mx, mn)

Your code writes this equivalently as:

    min(mx, mn) + 1
    + min(n - mx, n - mn);

Why?

The element with the larger index is closer to the back.

Therefore:

    min(n - mx, n - mn)

gives the number of deletions needed to remove the later element
from the back.

------------------------------------------------------------

Example:
--------

    nums = [2, 10, 7, 5, 1]

Indexes:

      0   1  2  3  4
    [ 2, 10, 7, 5, 1 ]
          ↑           ↑
         max         min

    mx = 1
    mn = 4
    n = 5

Option 1: Remove Everything From Front

    front = max(1, 4) + 1
          = 5

    Delete:

    [2, 10, 7, 5, 1]

    Answer = 5

--------------------------------

Option 2: Remove Everything From Back

    back = max(5 - 1, 5 - 4)
         = max(4, 1)
         = 4

    Delete from back:

    1, 5, 7, 10

    Answer = 4

--------------------------------

Option 3: Remove From Both Sides

Remove maximum from the front:

    mx + 1
    = 1 + 1
    = 2

Remove minimum from the back:

    n - mn
    = 5 - 4
    = 1

Total:

    2 + 1
    = 3

So:

    both = 3

Final answer:

    min(front, back, both)

    min(5, 4, 3)

    = 3

------------------------------------------------------------

Why Are These Three Cases Enough?
---------------------------------

Every deletion can only happen from one of two sides.

To remove both min and max, there are only three meaningful
strategies:

    1. Remove both from the front.

    2. Remove both from the back.

    3. Remove one from each side.

There is no fourth strategy that can produce a different minimum.

Therefore, checking these three possibilities guarantees the
optimal answer.

------------------------------------------------------------

Time Complexity:
----------------

Finding minimum and maximum:

    O(n)

Calculating the three possibilities:

    O(1)

Total:

    O(n)

------------------------------------------------------------

Space Complexity:
-----------------

We only use a few variables:

    mx
    mn
    front
    back
    both

Therefore:

    O(1)

------------------------------------------------------------

Final Idea:
-----------

First find:

    index of minimum
    index of maximum

Then calculate:

    front -> remove both from front

    back -> remove both from back

    both -> remove one from front and one from back

Finally return:

    minimum of all three options

This gives the minimum number of deletions needed to remove both
the minimum and maximum elements from the array.
*/