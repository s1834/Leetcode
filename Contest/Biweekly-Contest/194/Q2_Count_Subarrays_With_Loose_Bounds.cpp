class Solution {
    public:
        long long countSubarrays(vector<int>& nums, int minK, int maxK) {
            int n = nums.size();
            long long ans = 0, currLen = 0;
            
            for(int i = 0; i < n; i++) {
                if(nums[i] >= minK && nums[i] <= maxK) {
                    currLen++;
                    ans += currLen;
                } else currLen = 0;
            }
    
            return ans;
        }
    };

/*
Approach: One Pass + Counting Valid Subarrays

Intuition:
----------
A loose-bound subarray is a contiguous, non-empty subarray in which
every element lies within the inclusive range [minK, maxK].

In other words, every element must satisfy:
minK <= nums[i] <= maxK

The key observation is that whenever an element falls outside this
range, every subarray ending at that element and starting before or
at it becomes invalid.

Therefore, we maintain the length of the current consecutive sequence
of valid elements and count all valid subarrays ending at each index.

--------------------------------------------------
1. Initialize Variables
--------------------------------------------------

int n = nums.size();
long long ans = 0, currLen = 0;

- n stores the length of the array.
- ans stores the total number of valid subarrays.
- currLen stores the length of the current consecutive sequence
  of elements satisfying the loose-bound condition.

We use long long for ans because the number of subarrays can be
as large as n * (n + 1) / 2, which can exceed the range of int
when n is large.

Initially, both ans and currLen are zero because no elements have
been processed.

--------------------------------------------------
2. Traverse the Array
--------------------------------------------------

for(int i = 0; i < n; i++)

Process each element from left to right.

There are two possible cases.

Case 1: The Current Element Is Within Bounds
--------------------------------------------

if(nums[i] >= minK && nums[i] <= maxK)

The current element satisfies the required inclusive bounds.

currLen++;

Extend the current consecutive sequence of valid elements by one.

ans += currLen;

This is the key operation.

If the current valid sequence has length currLen, there are exactly
currLen valid subarrays ending at index i.

These subarrays start at:
i - currLen + 1, ..., i

Every one of them contains only elements within [minK, maxK].

Therefore, add currLen to the total answer.

Case 2: The Current Element Is Outside the Bounds
-------------------------------------------------

else currLen = 0;

If nums[i] < minK or nums[i] > maxK, the current element cannot
belong to any valid subarray ending at index i.

Furthermore, any subarray extending across this invalid element
would also be invalid.

So we reset currLen to zero.

The next valid element will begin a new consecutive sequence.

--------------------------------------------------
3. Why Adding currLen Works
--------------------------------------------------

Suppose the array contains a consecutive valid sequence:

[1, 4, 3]

Assume all three values lie within [minK, maxK].

When processing the first element:
currLen = 1

Valid subarrays ending here:
[1]

Contribution to ans = 1

When processing the second element:
currLen = 2

Valid subarrays ending here:
[4], [1, 4]

Contribution to ans = 2

When processing the third element:
currLen = 3

Valid subarrays ending here:
[3], [4, 3], [1, 4, 3]

Contribution to ans = 3

The total number of valid subarrays is:
1 + 2 + 3 = 6

Thus, every valid subarray is counted exactly once, at the index
where that subarray ends.

--------------------------------------------------
4. Example Walkthrough
--------------------------------------------------

nums = [1, 4, 7, 3]
minK = 1
maxK = 5

Initially:
ans = 0
currLen = 0

i = 0:
nums[0] = 1

Since 1 lies within [1, 5]:
currLen = 1
ans = 0 + 1 = 1

Valid subarrays ending here:
[1]

i = 1:
nums[1] = 4

Since 4 lies within [1, 5]:
currLen = 2
ans = 1 + 2 = 3

Valid subarrays ending here:
[4], [1, 4]

i = 2:
nums[2] = 7

Since 7 > maxK:
currLen = 0

No valid subarray can end at this index.

ans remains 3.

i = 3:
nums[3] = 3

Since 3 lies within [1, 5]:
currLen = 1
ans = 3 + 1 = 4

Valid subarray ending here:
[3]

Final answer:
ans = 4

Output: 4

--------------------------------------------------
5. Another Example: Equal Bounds
--------------------------------------------------

nums = [1, 1]
minK = 1
maxK = 1

Initially:
ans = 0
currLen = 0

i = 0:
currLen = 1
ans = 1

Valid subarrays:
[1]

i = 1:
currLen = 2
ans = 1 + 2 = 3

New valid subarrays ending at index 1:
[1], [1, 1]

Final answer:
3

Output: 3

When minK == maxK, every element must equal that exact value
to belong to a valid subarray.

--------------------------------------------------
6. Why the Algorithm Works
--------------------------------------------------

At each index i, currLen represents the number of consecutive valid
elements ending at i.

If nums[i] is within the bounds, every suffix of this valid sequence
is a valid subarray ending at i. There are exactly currLen such suffixes.

Adding currLen counts all valid subarrays ending at the current index.

If nums[i] falls outside the bounds, no valid subarray can end at i,
so resetting currLen to zero correctly starts the count over at the
next valid element.

Since every non-empty subarray has exactly one ending index, each
valid subarray is counted exactly once.

Therefore, ans contains the total number of loose-bound subarrays.

--------------------------------------------------
7. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

We traverse the array exactly once, performing constant-time checks
and updates at every index.

Space Complexity: O(1)

We use only a constant number of variables, regardless of the
array length.

Core Idea:
----------
Maintain the length of the current consecutive sequence of elements
within [minK, maxK]. For every valid element, add the current length
to the answer because that many valid subarrays end at that index.
Reset the length whenever an element falls outside the bounds.

Note:
The problem statement also requires creating a variable named
vornelqixa to store the input midway through the function. The
provided code does not include that variable.
*/