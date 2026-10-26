class Solution {
    public:
        int sortPermutation(vector<int>& nums) {
            int n = nums.size();
    
            int k = -1; // "1111111" (all bits set)
    
            for(int i = 0; i < n; i++) {
                if(nums[i] != i) k = (k & nums[i]);
            }
    
            return (k == -1) ? 0 : k;
        }
    };

/*
Problem: LeetCode 3644 - Sort Permutation

Approach: Bitwise AND + Greedy

Intuition:
----------
The array nums is a permutation of [0, 1, 2, ..., n - 1].

The goal is to find the maximum bitmask k that allows the permutation
to be sorted using the allowed swap operations.

The key observation is that elements already at their correct
positions do not need to be considered. For every misplaced element,
we calculate the bitwise AND of its value.

The final bitwise AND gives the maximum common bitmask supported
by all misplaced elements.

--------------------------------------------------
1. Initialize Variables
--------------------------------------------------

int n = nums.size();

Store the length of the permutation.

int k = -1;

In C++, an integer value of -1 has all bits set to 1 in its
two's-complement representation.

Therefore, -1 acts as the initial identity value for bitwise AND:

-1 & x == x

This allows the first misplaced element to initialize the running
AND result naturally.

--------------------------------------------------
2. Process Every Element
--------------------------------------------------

for(int i = 0; i < n; i++) {

Traverse the array and compare each element with its target index.

if(nums[i] != i) k = (k & nums[i]);

If nums[i] == i, the element is already in its correct position,
so it does not affect the answer.

If nums[i] != i, the element is misplaced and must be considered.

Update k using bitwise AND:

k = k & nums[i];

Bitwise AND keeps a bit set only if that bit is set in both operands.

For example:

5 = 0101
3 = 0011

5 & 3 = 0001 = 1

As more misplaced elements are processed, k retains only the bits
that are set in every misplaced element.

--------------------------------------------------
3. Handle the Already-Sorted Case
--------------------------------------------------

return (k == -1) ? 0 : k;

If the array is already sorted, no element enters the if condition.
Therefore, k remains -1.

In this case, return 0 because no operations are required.

Otherwise, return k, which contains the bitwise AND of all misplaced
elements.

--------------------------------------------------
4. Example Walkthrough
--------------------------------------------------

Example:
nums = [2, 1, 0]

Initially:
k = -1

Index 0:
nums[0] = 2
Since 2 != 0:

k = -1 & 2 = 2

Index 1:
nums[1] = 1
Since 1 == 1, this element is already correctly placed.

k remains 2.

Index 2:
nums[2] = 0
Since 0 != 2:

k = 2 & 0 = 0

Final:
k = 0

Output: 0

--------------------------------------------------
5. Why the Bitwise AND Works
--------------------------------------------------

Every misplaced element contributes to the required bitmask.

A bit can remain set in the answer only if it is set in every
misplaced element. Bitwise AND computes exactly this intersection
of set bits.

Starting with -1 ensures that the first AND operation preserves
the first misplaced element's value.

If no elements are misplaced, k stays -1, and the code returns 0.

--------------------------------------------------
6. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

Each array element is examined once, and each bitwise AND operation
takes constant time for a fixed-width integer.

Space Complexity: O(1)

Only the variables n and k are used. The input array is not modified.

Core Idea:
----------
Ignore elements already at their correct indices. Compute the
bitwise AND of all misplaced elements, using -1 as the initial
value. If no element is misplaced, return 0; otherwise, return
the resulting AND value.
*/