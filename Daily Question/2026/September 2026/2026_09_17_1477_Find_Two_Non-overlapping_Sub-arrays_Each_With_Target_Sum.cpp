class Solution {
    public:
        int minSumOfLengths(vector<int>& arr, int target) {
            int n = arr.size(), i = 0, j = 0, currSum = 0;
            vector<int> minBestLenTillIdx(n, INT_MAX);
            int bestMinLen = INT_MAX;
            int result = INT_MAX;
    
            while(j < n) {
                currSum += arr[j];
                while(i < j && currSum > target) currSum -= arr[i++];
    
                if(currSum == target) {
                    int len = j - i + 1;
                    if(i > 0 && minBestLenTillIdx[i - 1] != INT_MAX) result = min(result, len + minBestLenTillIdx[i - 1]);
                    bestMinLen = min(bestMinLen, len);
                }
    
                minBestLenTillIdx[j] = bestMinLen;
                j++;
            }
    
            return (result != INT_MAX) ? result : -1;
        }
    };

/*
LeetCode 1477. Find Two Non-overlapping Sub-arrays Each With Target Sum

Approach:
---------

We use a Sliding Window / Two Pointer approach to find every
subarray whose sum is exactly equal to target.

At the same time, we maintain information about the shortest
valid subarray found so far so that whenever we find another
valid subarray, we can immediately check whether it can be
combined with a previous non-overlapping subarray.

The important observation is that all elements are positive,
so we can use a sliding window:

    Expand the window by moving j forward.

    If the sum becomes greater than target,
    move i forward and remove elements from the sum.

Because all numbers are positive, increasing i always
decreases the current sum.

------------------------------------------------------------

Variables:
----------

    i
        Left boundary of the current sliding window.

    j
        Right boundary of the current sliding window.

    currSum
        Sum of the current window [i ... j].

    minBestLenTillIdx[j]
        Shortest valid subarray found completely within
        indices [0 ... j].

    bestMinLen
        Shortest valid subarray found so far while scanning
        from left to right.

    result
        Minimum total length of two non-overlapping valid
        subarrays found so far.

------------------------------------------------------------

Finding a Valid Subarray:
-------------------------

We maintain:

    currSum = sum of arr[i ... j]

Whenever we add:

    arr[j]

we do:

    currSum += arr[j];

If:

    currSum > target

we repeatedly remove elements from the left:

    while(i < j && currSum > target)
        currSum -= arr[i++];

Because all array elements are positive, this process
monotonically decreases the sum until:

    currSum <= target

or the window can no longer be reduced.

If:

    currSum == target

then:

    arr[i ... j]

is a valid subarray.

Its length is:

    len = j - i + 1

------------------------------------------------------------

Why Sliding Window Works:
-------------------------

The positivity of the elements is critical.

If:

    currSum > target

then adding more elements can only make the sum larger.

Therefore, the only useful operation is to move the left
pointer forward.

Similarly, if:

    currSum < target

we extend the window by moving j forward.

Thus both pointers only move forward throughout the
algorithm.

------------------------------------------------------------

Combining Two Non-overlapping Subarrays:
-----------------------------------------

Suppose the current valid subarray is:

    [i ... j]

To combine it with another valid subarray, the previous
subarray must end before i.

Therefore, it must be completely contained inside:

    [0 ... i - 1]

This is exactly why we use:

    minBestLenTillIdx[i - 1]

If it is not INT_MAX, then there exists a previous valid
subarray that does not overlap with the current one.

So:

    result = min(result,
                 len + minBestLenTillIdx[i - 1]);

------------------------------------------------------------

Why minBestLenTillIdx Is Needed:
--------------------------------

We don't just need to know whether a previous valid subarray
exists.

We need the SHORTEST previous valid subarray because our goal
is to minimize the total length of the two subarrays.

For every index j:

    minBestLenTillIdx[j]

stores the shortest valid subarray found completely within
the prefix:

    arr[0 ... j]

This allows us to combine the current subarray with the best
possible previous subarray in O(1) time.

------------------------------------------------------------

Meaning of bestMinLen:
----------------------

Whenever we find a valid subarray:

    bestMinLen = min(bestMinLen, len);

This represents:

    shortest valid subarray encountered so far

up to the current position.

Then after processing index j:

    minBestLenTillIdx[j] = bestMinLen;

So the array effectively stores prefix minimum lengths.

For example:

    valid subarray lengths encountered:

        5
        3
        4
        2

Then:

    bestMinLen

becomes:

        5 -> 3 -> 3 -> 2

Therefore:

    minBestLenTillIdx

contains the shortest valid length available in every
prefix.

------------------------------------------------------------

Important Ordering:
-------------------

Consider the current valid subarray:

    [i ... j]

We check:

    minBestLenTillIdx[i - 1]

before updating the prefix information for index j.

This guarantees that the previous subarray ends before i.

Therefore:

    previous subarray
    [ ... i-1 ]

and:

    current subarray
    [i ... j]

are guaranteed to be non-overlapping.

------------------------------------------------------------

Example:
--------

    arr = [3, 2, 2, 4, 3]
    target = 3

Valid subarrays include:

    [3]       -> length 1
    [3]       -> length 1

Suppose the first [3] occurs before the second [3].

When the second valid subarray is found, the prefix
information tells us that the shortest valid subarray
ending before its starting position has length 1.

Therefore:

    total length = 1 + 1
                 = 2

and:

    result = 2

------------------------------------------------------------

Another Example:
-----------------

Suppose:

    arr = [7, 3, 4, 7]
    target = 7

Valid subarrays:

    [7]       -> length 1
    [3,4]     -> length 2
    [7]       -> length 1

When processing [3,4]:

    previous best = 1

so:

    result = 1 + 2
           = 3

Later, when processing the final [7]:

    previous shortest valid subarray = 1

so:

    result = 1 + 1
           = 2

Therefore the answer is:

    2

------------------------------------------------------------

Why The Prefix Array Gives the Optimal Pair:
---------------------------------------------

For a current subarray [i...j], every valid previous subarray
that can be paired with it must end at or before i - 1.

Among all such subarrays, only the shortest one matters.

That shortest length is exactly:

    minBestLenTillIdx[i - 1]

Therefore, for every possible current valid subarray, we
consider the optimal previous subarray that can pair with it.

Taking the minimum over all current subarrays gives the
minimum total length.

------------------------------------------------------------

Handling No Valid Pair:
-----------------------

Initially:

    result = INT_MAX

If no pair of non-overlapping target-sum subarrays exists,
`result` remains INT_MAX.

Therefore:

    return (result != INT_MAX) ? result : -1;

returns:

    -1

when no valid pair exists.

------------------------------------------------------------

Algorithm:
----------

    1. Initialize two pointers:

           i = 0
           j = 0

    2. Add arr[j] to currSum.

    3. While currSum > target, move i forward and subtract
       the removed elements.

    4. If currSum == target:

           a. Calculate the current subarray length.

           b. Check whether a valid previous subarray exists
              before index i.

           c. If it exists, update result.

           d. Update bestMinLen with the current length.

    5. Store the shortest valid subarray found so far:

           minBestLenTillIdx[j] = bestMinLen

    6. Move j forward.

    7. Return result if a pair was found, otherwise return -1.

------------------------------------------------------------

Complexity:
-----------

The right pointer j moves from 0 to n - 1.

The left pointer i also only moves forward and never moves
backward.

Therefore, the sliding window portion takes:

    O(n)

Each valid subarray is processed in O(1) additional time.

The prefix array also uses O(n) space.

Therefore:

    Time Complexity:
        O(n)

    Space Complexity:
        O(n)

------------------------------------------------------------

Core Idea:
----------

The key is to combine TWO ideas:

    1. Sliding Window

       Find target-sum subarrays in O(n).

    2. Prefix Minimum

       Remember the shortest valid subarray seen before the
       current starting position.

For every current valid subarray:

              previous valid subarray
              [ ...... i-1 ]

                         +

              current valid subarray
              [ i ........ j ]

we use:

    minBestLenTillIdx[i - 1]

to obtain the shortest possible previous subarray.

Thus we can find the minimum total length of two
non-overlapping target-sum subarrays in linear time.
*/