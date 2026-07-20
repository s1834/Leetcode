class Solution {
    public:
        int minSubArrayLen(int target, vector<int>& nums) {
            int left = 0, n = nums.size(), mn = INT_MAX;
            long long sum = 0;
    
            for (int right = 0; right < n; right++) {
                sum += nums[right];
    
                while (sum >= target) {
                    mn = min(mn, right - left + 1);
                    sum -= nums[left];
                    left++;
                }
            }
    
            return (mn == INT_MAX) ? 0 : mn;
        }
    };

/*

Idea:
------
We need to find the minimum length of a contiguous
subarray whose sum is at least

target.

Since all numbers in the array are positive,

expanding the window always increases the sum, while
shrinking the window always decreases the sum.

This property allows us to use the Sliding Window
(Two Pointer) technique efficiently.

------------------------------------------------------------

Why Does Sliding Window Work?
-----------------------------

Because every element is positive,

• Adding a new element to the right can only increase
  the current sum.

• Removing an element from the left can only decrease
  the current sum.

Therefore,

once the current window satisfies

sum ≥ target,

we can safely try shrinking it from the left to obtain a
smaller valid window.

------------------------------------------------------------

Algorithm:
----------

1.

Initialize

left = 0

sum = 0

minimumLength = INT_MAX

------------------------------------------------------------

2.

Expand the window by moving

right

from left to right.

For every position,

add

nums[right]

to the current sum.

------------------------------------------------------------

3.

Whenever

sum ≥ target,

the current window is valid.

Update the minimum length.

------------------------------------------------------------

4.

Try to shrink the window.

Remove

nums[left]

from the current sum.

Increment

left.

Continue shrinking while the window still satisfies

sum ≥ target.

------------------------------------------------------------

5.

Repeat until every element has been processed.

------------------------------------------------------------

6.

If no valid window was found,

return

0.

Otherwise,

return the minimum window length.

------------------------------------------------------------

Why Does This Work?
-------------------

The window always contains a contiguous subarray.

Whenever its sum becomes at least

target,

it is a valid candidate.

Instead of stopping,

we continue removing elements from the left until the
window is no longer valid.

This guarantees that every valid window is minimized
before moving on.

Since each element enters and leaves the window at most
once,

every possible candidate is considered efficiently.

------------------------------------------------------------

Example:
--------

nums =

[2,3,1,2,4,3]

target = 7

Initially

left = 0

sum = 0

--------------------------------

Add 2

sum = 2

Not enough.

--------------------------------

Add 3

sum = 5

Not enough.

--------------------------------

Add 1

sum = 6

Not enough.

--------------------------------

Add 2

sum = 8

Valid window

[2,3,1,2]

Length = 4

Remove 2

sum = 6

--------------------------------

Add 4

sum = 10

Valid window

[3,1,2,4]

Length = 4

Remove 3

sum = 7

Still valid

Window

[1,2,4]

Length = 3

Remove 1

sum = 6

--------------------------------

Add 3

sum = 9

Valid window

[2,4,3]

Length = 3

Remove 2

sum = 7

Still valid

Window

[4,3]

Length = 2

Remove 4

sum = 3

Finished.

Minimum Length = 2

------------------------------------------------------------

Time Complexity:
----------------

O(n)

Each element enters the window once and leaves the
window at most once.

------------------------------------------------------------

Space Complexity:
-----------------

O(1)

Only a few variables are used.

*/