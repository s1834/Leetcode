class Solution {
    public:
        int firstStableIndex(vector<int>& nums, int k) {
            int n = nums.size();
            vector<pair<int, int>> scores(n);
    
            int mx = INT_MIN;
            for(int i = 0; i < n; i++) {
                mx = max(mx, nums[i]);
                scores[i] = {mx, INT_MAX};
            }
    
            int mn = INT_MAX;
            for(int i = n - 1; i >= 0; i--) {
                mn = min(mn, nums[i]);
                scores[i] = {scores[i].first, mn};
            }
    
            for(int i = 0; i < n; i++) {
                if(scores[i].first - scores[i].second <= k) return i;
            }
    
            return -1;
        }
    };


/*
LeetCode 3904. Smallest Stable Index II

Approach:
---------

For every index i, we need to determine whether the difference
between:

    1. The maximum value from index 0 to i
    2. The minimum value from index i to n - 1

is less than or equal to k.

In other words:

    max(nums[0 ... i]) - min(nums[i ... n - 1]) <= k

If this condition is satisfied, index i is stable.

We need to return the FIRST index that satisfies this condition.

------------------------------------------------------------

Brute Force Approach:
---------------------

For every index i, we could:

    1. Find the maximum element from 0 to i.
    2. Find the minimum element from i to n - 1.
    3. Check if their difference is <= k.

However, calculating these values separately for every index would
take O(n²) time.

We can optimize this using:

    Prefix Maximum
    +
    Suffix Minimum

------------------------------------------------------------

Step 1: Calculate Prefix Maximum
--------------------------------

For every index i, calculate:

    prefixMax[i] = maximum element from index 0 to i

Example:

    nums = [4, 2, 7, 3, 5]

Prefix maximum:

    Index:       0  1  2  3  4
    nums:        4  2  7  3  5
    prefixMax:   4  4  7  7  7

We maintain:

    mx = maximum value seen so far

For every element:

    mx = max(mx, nums[i]);

The value of mx represents the maximum element from:

    nums[0 ... i]

------------------------------------------------------------

Step 2: Calculate Suffix Minimum
--------------------------------

For every index i, calculate:

    suffixMin[i] = minimum element from index i to n - 1

Example:

    nums = [4, 2, 7, 3, 5]

Suffix minimum:

    Index:       0  1  2  3  4
    nums:        4  2  7  3  5
    suffixMin:   2  2  3  3  5

We maintain:

    mn = minimum value seen so far while traversing from right
         to left.

For every element:

    mn = min(mn, nums[i]);

The value of mn represents the minimum element from:

    nums[i ... n - 1]

------------------------------------------------------------

Step 3: Check Every Index
-------------------------

After calculating the prefix maximum and suffix minimum for every
index, check:

    prefixMax[i] - suffixMin[i] <= k

If this condition is true:

    return i;

Since we traverse from left to right, the first index satisfying
the condition is automatically the answer.

------------------------------------------------------------

Example:
--------

    nums = [4, 2, 7, 3, 5]

Suppose:

    k = 4

First calculate:

    Index:         0  1  2  3  4

    Prefix Max:    4  4  7  7  7

    Suffix Min:    2  2  3  3  5


Now calculate:

    prefixMax[i] - suffixMin[i]


Index 0:

    4 - 2 = 2

    2 <= 4

Therefore:

    index 0 is stable.

Return:

    0

------------------------------------------------------------

Why Store Both Values?
----------------------

For every index i, we need two values:

    Maximum from the left:

        max(nums[0 ... i])

    Minimum from the right:

        min(nums[i ... n - 1])

The code stores both values inside:

    scores[i]

Where:

    scores[i].first

represents:

    maximum from 0 to i


And:

    scores[i].second

represents:

    minimum from i to n - 1

Therefore:

    scores[i] = {prefixMaximum, suffixMinimum}

------------------------------------------------------------

Algorithm:
----------

    1. Create an array to store the prefix maximum and suffix
       minimum for every index.

    2. Traverse from left to right.

       Maintain the maximum element seen so far.

       Store it for every index.

    3. Traverse from right to left.

       Maintain the minimum element seen so far.

       Store it for every index.

    4. Traverse from left to right again.

    5. For every index i, check:

           prefixMax[i] - suffixMin[i] <= k

    6. Return the first index satisfying the condition.

    7. If no index satisfies the condition:

           return -1

------------------------------------------------------------

Time Complexity:
----------------

First traversal for prefix maximum:

    O(n)

Second traversal for suffix minimum:

    O(n)

Third traversal to find the first stable index:

    O(n)

Total:

    O(n)

------------------------------------------------------------

Space Complexity:
-----------------

We store two values for every index:

    prefix maximum
    suffix minimum

Therefore:

    O(n)

------------------------------------------------------------

Core Idea:
----------

For every index i:

    Find maximum on the left side
                |
                v
        prefixMax[i]

                -

        suffixMin[i]

                ^
                |
    Find minimum on the right side


If:

    prefixMax[i] - suffixMin[i] <= k

Then:

    i is a stable index


Return the first such index.
*/