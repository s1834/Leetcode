class Solution {
    public:
        int minOperations(vector<int>& nums, vector<int>& locked, int k) {
            int n = nums.size();
    
            vector<bool> goodBoundries(n + 1, false);
            goodBoundries[0] = true;
            goodBoundries[n] = true;
    
            int maxElementTillIndex = 0;
            for(int i = 1; i < n; i++) {
                maxElementTillIndex = max(maxElementTillIndex, nums[i - 1]);
                if(maxElementTillIndex == i) goodBoundries[i] = true;
            }
    
            int unlocks = 0;
            for(int i = 0; i < n; i++) {
                if(locked[i] == 1 && (!goodBoundries[i] || !goodBoundries[i + 1])) unlocks++;
            }
    
            if(unlocks > k) return -1;
    
            int swaps = 0;
            for(int i = 0; i < n; i++) {
                for(int j = i + 1; j < n; j++) {
                    if(nums[i] > nums[j]) swaps++;
                }
            }
    
            return swaps + unlocks;
        }
    };

/*
Problem: LeetCode 4099

Approach: Valid Partition Boundaries + Inversion Counting

Intuition:
----------
The solution identifies valid partition boundaries, counts
how many locked elements cannot remain in their current
positions, and calculates the total number of inversions.

It then combines the required unlock operations and swaps
to obtain the final answer.

--------------------------------------------------
1. Initialize Valid Partition Boundaries
--------------------------------------------------

int n = nums.size();

vector<bool> goodBoundries(n + 1, false);

goodBoundries[0] = true;
goodBoundries[n] = true;

goodBoundries[i] indicates whether index i is a valid
boundary for splitting the array.

The first and last boundaries are always valid because
they represent the beginning and end of the array.

--------------------------------------------------
2. Find Valid Boundaries
--------------------------------------------------

int maxElementTillIndex = 0;

for(int i = 1; i < n; i++) {

    maxElementTillIndex = max(maxElementTillIndex, nums[i - 1]);

    if(maxElementTillIndex == i)
        goodBoundries[i] = true;
}

This loop calculates the maximum element in the prefix
ending at index i - 1.

A boundary i is marked valid when:

    maxElementTillIndex == i

This means that every element in the prefix belongs to
the range [0, i].

For a permutation of numbers from 0 to n - 1, this condition
identifies positions where the prefix contains exactly
the first i values.

Such positions can act as valid partition boundaries.

--------------------------------------------------
3. Count Elements That Need to Be Unlocked
--------------------------------------------------

int unlocks = 0;

for(int i = 0; i < n; i++) {

    if(locked[i] == 1 &&
       (!goodBoundries[i] || !goodBoundries[i + 1]))
        unlocks++;
}

For every position:

- Check whether the element is locked.
- Check whether its left boundary is valid.
- Check whether its right boundary is valid.

If the element is locked and either boundary is invalid,
increment unlocks.

Thus, unlocks counts locked elements that cannot remain
in their current position according to the boundary
conditions used by this solution.

--------------------------------------------------
4. Check Whether Unlocking Is Possible
--------------------------------------------------

if(unlocks > k) return -1;

If the number of required unlocks exceeds the available
limit k, the function returns -1.

Otherwise, the solution proceeds to calculate swaps.

--------------------------------------------------
5. Count Inversions
--------------------------------------------------

int swaps = 0;

for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {

        if(nums[i] > nums[j])
            swaps++;
    }
}

An inversion is a pair of indices (i, j) such that:

    i < j
    nums[i] > nums[j]

Every such pair represents two elements that appear
in the wrong relative order.

The nested loops examine every possible pair and count
all inversions.

For example:

    nums = [3, 1, 2]

Inversions:
    (3, 1)
    (3, 2)

Therefore:

    swaps = 2

--------------------------------------------------
6. Calculate the Final Answer
--------------------------------------------------

return swaps + unlocks;

The solution adds:
- swaps: total number of inversions.
- unlocks: number of locked elements that fail the
  boundary condition.

The resulting sum is returned as the answer.

--------------------------------------------------
7. Complexity Analysis
--------------------------------------------------

Let n be the size of nums.

Time Complexity: O(n²)

- Finding valid boundaries takes O(n).
- Counting unlocks takes O(n).
- Counting inversions takes O(n²) because of the nested loops.

Space Complexity: O(n)

The goodBoundries vector stores n + 1 boolean values.

Core Idea:
----------
1. Identify valid prefix/suffix partition boundaries.
2. Count locked elements that do not satisfy the boundary
   condition.
3. Return -1 if the required unlock count exceeds k.
4. Count inversions using pairwise comparisons.
5. Return the sum of inversions and required unlocks.
*/