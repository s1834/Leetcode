class Solution {
    public:
        vector<int> largestDivisibleSubset(vector<int>& nums) {
            sort(nums.begin(), nums.end()); // sort so we have to only check nums[i] % nums[j] == 0, not each number
    
            int n = nums.size();
            vector<int> dp(n, 1); // max lis till a index
            vector<int> prevIdx(n, -1); // prevIdx of longes subset till i
            int lastChosenIdx = 0; // index of largest subset found soo far
            int maxL = 1; // length of largest subset found soo far
            
            // ending element
            for(int i = 1; i < n; i++) {
                // previous elements to i
                for(int j = 0; j < i; j++) { 
                    if(nums[i] % nums[j] == 0) {
                        // update dp[i] if using j gives us larger subset
                        if(dp[i] < dp[j] + 1) { 
                            dp[i] = dp[j] + 1;
                            prevIdx[i] = j;
                        }
    
                        // keep track of longest subset found
                        if(dp[i] > maxL) { 
                            maxL = dp[i];
                            lastChosenIdx = i;
                        }
                    }
                }
            }
    
            // reconstruct subset by following prevIdex backwards
            vector<int> ans;
            while(lastChosenIdx != -1) {
                ans.push_back(nums[lastChosenIdx]);
                lastChosenIdx = prevIdx[lastChosenIdx];
            }
    
            return ans;
        }
    };

/*
LeetCode 368. Largest Divisible Subset

Approach:
---------

We need to find the largest subset such that for every pair of
elements (a, b) in the subset:

    a % b == 0
    OR
    b % a == 0

The key idea is to first sort the array and then use a DP
approach similar to LIS (Longest Increasing Subsequence).

------------------------------------------------------------

Why Sort?
---------

    sort(nums.begin(), nums.end());

After sorting:

    nums[0] <= nums[1] <= nums[2] ...

Now, if we want nums[i] to come after nums[j] where:

    j < i

then:

    nums[j] <= nums[i]

Therefore, for them to be divisible, we only need to check:

    nums[i] % nums[j] == 0

We don't need to check both:

    nums[i] % nums[j] == 0
    nums[j] % nums[i] == 0

because nums[i] is greater than or equal to nums[j].

This makes the problem similar to LIS:

    LIS:
        nums[j] < nums[i]

    Divisible Subset:
        nums[i] % nums[j] == 0

------------------------------------------------------------

Example:
--------

nums = [1, 2, 4, 8]

Already sorted.

We can build:

    1 -> 2 -> 4 -> 8

because:

    2 % 1 = 0
    4 % 2 = 0
    8 % 4 = 0

So:

    [1, 2, 4, 8]

is a valid divisible subset.

------------------------------------------------------------

DP Array:
---------

    vector<int> dp(n, 1);

Here:

    dp[i]

represents the length of the largest divisible subset whose
last/largest element is:

    nums[i]

Every individual number can form a subset by itself, so
initially:

    dp[i] = 1

For example:

    nums = [1, 2, 3, 6]

Initially:

    dp = [1, 1, 1, 1]

------------------------------------------------------------

prevIdx Array:
--------------

    vector<int> prevIdx(n, -1);

dp tells us only the LENGTH of the best subset.

But we also need to reconstruct the actual subset.

For that, we store:

    prevIdx[i]

which represents the index of the previous element in the
best divisible subset ending at i.

For example:

    [1, 2, 4]

If:

    prevIdx[2] = 1
    prevIdx[1] = 0

then we can reconstruct:

    4 -> 2 -> 1

by following the previous indices backwards.

------------------------------------------------------------

lastChosenIdx:
--------------

    int lastChosenIdx = 0;

This stores the index where the largest divisible subset
currently ends.

For example, if:

    dp[4] = 5

is the largest value found so far, then:

    lastChosenIdx = 4

This gives us the starting point for reconstructing the answer.

------------------------------------------------------------

maxL:
------

    int maxL = 1;

This stores the length of the largest divisible subset found
so far.

Initially every number by itself is a valid subset, so:

    maxL = 1

------------------------------------------------------------

Building the DP:
----------------

We consider each element as the ending element of a subset:

    for(int i = 1; i < n; i++)

For every nums[i], we check all previous elements:

    for(int j = 0; j < i; j++)

So:

    j

represents a possible previous element, and:

    i

is the current ending element.

------------------------------------------------------------

Check Divisibility:
-------------------

    if(nums[i] % nums[j] == 0)

If this is true, nums[i] can be added after nums[j].

For example:

    nums[j] = 4
    nums[i] = 12

Since:

    12 % 4 == 0

we can extend a divisible subset ending at 4 by adding 12.

------------------------------------------------------------

Updating dp[i]:
---------------

    if(dp[i] < dp[j] + 1)

If we add nums[i] after nums[j], the resulting subset has:

    dp[j] + 1

elements.

If that is better than our current best subset ending at i:

    dp[i]

we update it:

    dp[i] = dp[j] + 1;

For example:

    dp[j] = 3

means there is a divisible subset of length 3 ending at nums[j].

If nums[i] is divisible by nums[j], we can add nums[i]:

    3 + 1 = 4

So:

    dp[i] = 4

------------------------------------------------------------

Store Previous Index:
---------------------

When we update dp[i], we also need to remember WHERE this
best subset came from:

    prevIdx[i] = j;

For example:

    nums = [1, 2, 4]

When processing 4:

    dp[1] = 2      // [1, 2]

Since:

    4 % 2 == 0

we can extend it:

    dp[2] = 3

and store:

    prevIdx[2] = 1

This tells us:

    4 came after 2

------------------------------------------------------------

Tracking the Longest Subset:
-----------------------------

After updating dp[i]:

    if(dp[i] > maxL)

we have found a new largest subset.

So we update:

    maxL = dp[i];
    lastChosenIdx = i;

Now:

    lastChosenIdx

points to the last element of the largest subset found so far.

------------------------------------------------------------

Why Do We Need lastChosenIdx?
------------------------------

Suppose:

    nums = [1, 2, 3, 4, 6, 12]

and the largest subset is:

    [1, 2, 4, 12]

The DP array might tell us:

    dp[5] = 4

But simply knowing the length 4 is not enough.

We need to know where this subset ends.

So:

    lastChosenIdx = 5

allows us to start reconstruction from:

    nums[5] = 12

------------------------------------------------------------

Reconstructing the Answer:
--------------------------

After the DP is complete:

    vector<int> ans;

We start from:

    lastChosenIdx

and repeatedly follow:

    prevIdx

using:

    while(lastChosenIdx != -1) {
        ans.push_back(nums[lastChosenIdx]);
        lastChosenIdx = prevIdx[lastChosenIdx];
    }

For example:

    nums = [1, 2, 4, 8]

The previous indices might be:

    prevIdx:
        [-1, 0, 1, 2]

Starting from:

    lastChosenIdx = 3

we get:

    8
    ↓
    prevIdx[3] = 2

    4
    ↓
    prevIdx[2] = 1

    2
    ↓
    prevIdx[1] = 0

    1
    ↓
    prevIdx[0] = -1

So we build:

    [8, 4, 2, 1]

which is the correct subset, just in reverse order.

------------------------------------------------------------

Why Is the Answer Returned in Reverse Order?
---------------------------------------------

The reconstruction starts from the largest/last element and
follows the chain backwards.

So the result naturally becomes:

    largest -> previous -> previous -> ...

For example:

    [8, 4, 2, 1]

The problem does not require the subset to be returned in a
specific order, so this is still a valid answer.

------------------------------------------------------------

Important DP Interpretation:
----------------------------

The key meaning to remember is:

    dp[i]
        = longest divisible subset ending at nums[i]

and:

    prevIdx[i]
        = previous index used to obtain that best subset

The recurrence is:

    if(nums[i] % nums[j] == 0)

        dp[i] = max(dp[i], dp[j] + 1)

This is essentially LIS with a different condition.

------------------------------------------------------------

Example:
--------

nums:

    [1, 2, 3, 4]

Start:

    dp = [1, 1, 1, 1]

For 2:

    2 % 1 == 0

so:

    dp[1] = dp[0] + 1 = 2

subset:

    [1, 2]

For 3:

    3 % 1 == 0

so:

    dp[2] = 2

subset:

    [1, 3]

For 4:

    4 % 1 == 0
    4 % 2 == 0

Using 2 gives:

    dp[1] + 1 = 3

which is better.

So:

    dp[3] = 3
    prevIdx[3] = 1

The subset is:

    [1, 2, 4]

------------------------------------------------------------

Why Does Sorting Make the Pairwise Condition Enough?
------------------------------------------------------

The original requirement says that for every pair:

    a % b == 0
    OR
    b % a == 0

After sorting, suppose:

    a <= b

Then:

    b % a == 0

is the only possible divisibility direction, except when
a == b.

So when processing a larger element after a smaller element,
we only check:

    larger % smaller == 0

This is the main reason sorting is important.

------------------------------------------------------------

Overall Flow:
-------------

        Sort nums
           |
           ↓
    Initialize dp = 1
    Initialize prevIdx = -1
           |
           ↓
    For every nums[i]
           |
     Check every j < i
           |
           ↓
    nums[i] % nums[j] == 0 ?
           |
       +---+---+
       |       |
      YES      NO
       |
       ↓
  Can extend dp[j]
       |
       ↓
  dp[i] = dp[j] + 1
       |
       ↓
  prevIdx[i] = j
       |
       ↓
 Track largest dp
       |
       ↓
 Reconstruct using prevIdx
       |
       ↓
     Answer

------------------------------------------------------------

Complexity:
-----------

Sorting:

    O(n log n)

The nested loops:

    for i
        for j < i

take:

    O(n²)

Reconstruction takes:

    O(n)

Therefore:

    Time Complexity: O(n²)

The DP arrays:

    dp
    prevIdx

both use:

    O(n)

space.

So:

    Space Complexity: O(n)

excluding the space used by the input array.

------------------------------------------------------------

Main Pattern to Remember:
--------------------------

This problem is essentially:

    Sort + LIS-style DP + Path Reconstruction

The most important pieces are:

    dp[i]
        = longest divisible subset ending at i

    prevIdx[i]
        = previous element used in that subset

Transition:

    if(nums[i] % nums[j] == 0)

        dp[i] = max(dp[i], dp[j] + 1)

Then keep:

    lastChosenIdx

to know where the best subset ends.

Finally, follow:

    prevIdx[lastChosenIdx]

backwards to reconstruct the actual subset.

The key recognition is:

    "After sorting, this becomes an LIS-style problem where
     the normal increasing condition is replaced by
     nums[i] % nums[j] == 0."

*/