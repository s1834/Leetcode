class Solution {
    public:
        int longestOnes(vector<int>& nums, int k) {
            int n = nums.size(), l = 0, r = 0, zero = -1, mx = 0, count = 0, temp = k;
            while(r < n) {
                if(nums[r] == 1) count++;
                else if(temp > 0) {
                    if(zero == -1) zero = r;
                    temp--;
                    count++;
                }else if(temp == 0) {
                    temp = k;
                    mx = max(mx, count);
                    count = 0;
                    if(zero != -1) {
                        l = zero;
                        r = zero;
                        zero = -1;
                    }
                    l = r + 1;
                } 
                r++;
            } 
    
            return max(mx, count);
        }
    };

/*
LeetCode 1004. Max Consecutive Ones III

Approach:
---------

We use the Sliding Window / Two Pointer technique.

The goal is to find the longest subarray containing at most k zeros,
because we are allowed to flip at most k zeros into ones.

Instead of trying every possible subarray, we maintain a window:

    [l ... r]

where the window represents the current consecutive sequence of 1s
after using at most k flips.

------------------------------------------------------------

Variables:
----------

    l
        -> left boundary of the current window

    r
        -> right boundary of the current window

    zero
        -> stores the position of the first zero that was flipped
           in the current window

    temp
        -> number of zero flips still available

    count
        -> length of the current valid window

    mx
        -> maximum valid window length found so far

------------------------------------------------------------

Case 1: nums[r] == 1
---------------------

If the current element is already 1, we do not need to use a flip.

    if(nums[r] == 1)
        count++;

So the current window can simply be extended.

Example:

    nums = [1, 1, 0]
               ^
               r

The 1s can always remain in the window.

------------------------------------------------------------

Case 2: nums[r] == 0 and We Have Flips
---------------------------------------

If nums[r] is 0 and:

    temp > 0

we can flip this zero into a 1.

    else if(temp > 0) {
        if(zero == -1) zero = r;
        temp--;
        count++;
    }

The first flipped zero is stored in:

    zero

This is important because if we later encounter another zero when
we have no flips left, we need to move the window past this first
flipped zero.

Example:

    nums = [1, 0, 1, 0, 1]
             ^
             first flipped zero

    zero = 1

------------------------------------------------------------

Why Store Only the First Zero?
------------------------------

Suppose:

    nums = [1, 0, 1, 0, 1]
              ^
              zero = 1

and k = 1.

We can flip the zero at index 1.

When we encounter the zero at index 3, there are no flips remaining.

Instead of throwing away the entire window, we can remove the
previously flipped zero from the window.

So we move:

    l = zero

and restart the window from that position.

The next iteration will then move r forward.

This allows us to reuse as much of the previous window as possible.

------------------------------------------------------------

Case 3: nums[r] == 0 and No Flips Left
---------------------------------------

If:

    temp == 0

and nums[r] is 0, the current window cannot include this new zero.

Therefore, we first save the best window found so far:

    mx = max(mx, count);

Then we reset the flip budget:

    temp = k;

because we are going to construct a new window.

We also reset:

    count = 0;

If a flipped zero existed:

    if(zero != -1) {
        l = zero;
        r = zero;
        zero = -1;
    }

we restart from the position of the first flipped zero.

Why?

Because that first flipped zero can no longer be part of the new
window. Starting from there allows the next iteration to move past
it while preserving the elements after it.

If there was no previously flipped zero, we simply start after the
current zero:

    l = r + 1;

------------------------------------------------------------

Example:
--------

    nums = [1, 1, 0, 0, 1, 1]
    k = 1

Initially:

    temp = 1

Process:

    1 -> include
    1 -> include
    0 -> flip it

Current window:

    [1, 1, 0]

    count = 3
    temp = 0
    zero = 2

Now another zero is encountered.

We cannot flip it because:

    temp = 0

So we save:

    mx = 3

and restart from the first flipped zero.

This allows us to move the window forward without unnecessarily
discarding all previous elements.

------------------------------------------------------------

Why Does This Work?
-------------------

At any point, the window contains at most k zeros that have been
treated as flipped.

Whenever we encounter a zero and still have a flip available,
we include it.

When we encounter a zero but have no flips left, the current window
cannot remain valid.

So we move the window past the earliest flipped zero and reuse the
remaining portion of the previous window.

This effectively maintains the longest possible window with at
most k zeros.

------------------------------------------------------------

Important Observation:
----------------------

The problem can be viewed as:

    Find the longest subarray containing at most k zeros.

Because every zero inside the window can be flipped into a one.

For example:

    [1, 0, 1, 0, 1]

contains two zeros.

If:

    k = 2

we can flip both zeros:

    [1, 1, 1, 1, 1]

So the entire window is valid.

------------------------------------------------------------

Edge Case: k = 0
-----------------

When:

    k = 0

we cannot flip any zero.

Therefore, the answer is simply the longest consecutive sequence
of existing 1s.

The same logic still works because:

    temp = 0

and every zero forces the current window to restart.

------------------------------------------------------------

Final Answer:
-------------

During the loop, mx stores the best window found before a reset.

However, the longest window might be the final window, and it may
never enter the reset condition.

Therefore we return:

    max(mx, count)

This ensures both the previous best window and the final window
are considered.

------------------------------------------------------------

Algorithm:
----------

    1. Initialize the left and right pointers.

    2. Traverse the array using r.

    3. If nums[r] == 1:
           extend the current window.

    4. If nums[r] == 0 and a flip is available:
           flip it and extend the window.

    5. If nums[r] == 0 and no flip is available:
           save the current maximum,
           reset the flip count,
           and restart from the first flipped zero.

    6. Return the maximum of:
           mx
           count

------------------------------------------------------------

Time Complexity:
----------------

The right pointer moves through the array.

The left/reset positions also move forward through the array.

Therefore, the overall complexity is:

    O(n)

------------------------------------------------------------

Space Complexity:
-----------------

Only a few variables are used.

Therefore:

    O(1)

------------------------------------------------------------

Core Idea:
----------

        Maintain a window [l ... r]

                 |
                 v

        Count zeros in window
                 |
        +--------+--------+
        |                 |
    zeros <= k         zeros > k
        |                 |
        v                 v
   Expand window      Move past the
                      first flipped zero
        |                 |
        +--------+--------+
                 |
                 v
        Track maximum length

The key observation is:

    Longest consecutive 1s after at most k flips
                    =
    Longest subarray containing at most k zeros
*/