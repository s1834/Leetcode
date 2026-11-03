class Solution {
    public:
        int jump(vector<int>& nums) {
            int n = nums.size(), jumps = 0, l = 0, r = 0;
    
            while(r < n - 1) {
                int farthest = 0;
                for(int i = l; i <= r; i++) farthest = max(farthest, nums[i] + i);
                l = r + 1;
                r = farthest;
                jumps++;
            }
    
            return jumps;
        }
    };

/*
Problem: LeetCode 45 - Jump Game II

Approach: Greedy (BFS-Level Traversal)

Intuition:
----------
We need to find the minimum number of jumps required to
reach the last index.

Instead of exploring every possible jump, we process the
array in ranges.

Each range represents all the indices that can be reached
using the same number of jumps.

The key idea is:
- l and r represent the current range of reachable indices.
- From every index in this range, calculate the farthest
  position we can reach with one additional jump.
- The next range starts immediately after the current range
  and ends at that farthest position.
- Increment jumps after processing the current range.

This is similar to level-order traversal (BFS), where
each level represents one additional jump.

--------------------------------------------------
1. Initialize Variables
--------------------------------------------------

int n = nums.size(), jumps = 0, l = 0, r = 0;

- n: Number of elements in the array.
- jumps: Minimum number of jumps taken so far.
- l: Starting index of the current range.
- r: Ending index of the current range.

Initially:

    l = 0
    r = 0

We start at index 0, so the first reachable range contains
only index 0.

--------------------------------------------------
2. Continue Until the Last Index Is Reached
--------------------------------------------------

while(r < n - 1)

As long as the current range does not reach the last index,
we need another jump.

--------------------------------------------------
3. Find the Farthest Reachable Position
--------------------------------------------------

int farthest = 0;

for(int i = l; i <= r; i++)
    farthest = max(farthest, nums[i] + i);

For every index in the current range:

    nums[i] + i

represents the farthest index reachable by jumping from i.

We take the maximum of these values because we want to
extend our reach as much as possible with the next jump.

After processing the entire range, farthest represents
the maximum position reachable using one additional jump.

--------------------------------------------------
4. Move to the Next Range
--------------------------------------------------

l = r + 1;
r = farthest;

The next range starts immediately after the current range.

Its ending position is farthest.

Therefore, the new range is:

    [old_r + 1, farthest]

All indices in this range are reachable using one more
jump than the previous range.

--------------------------------------------------
5. Increment the Jump Count
--------------------------------------------------

jumps++;

We have processed the current range and expanded our reach
to the next range.

This corresponds to taking one additional jump.

--------------------------------------------------
6. Return the Answer
--------------------------------------------------

return jumps;

Once r reaches or exceeds n - 1, the last index is reachable.

The number of expansions performed gives the minimum
number of jumps required.

--------------------------------------------------
7. Example Walkthrough
--------------------------------------------------

Input:
nums = [2, 3, 1, 1, 4]

Initially:

    l = 0
    r = 0
    jumps = 0

Iteration 1:

Current range = [0, 0]

    i = 0:
        farthest = max(0, 0 + nums[0])
                 = max(0, 2)
                 = 2

Update:

    l = 1
    r = 2
    jumps = 1

We can reach indices [1, 2] using one jump.

Iteration 2:

Current range = [1, 2]

    i = 1:
        farthest = max(0, 1 + 3)
                 = 4

    i = 2:
        farthest = max(4, 2 + 1)
                 = 4

Update:

    l = 3
    r = 4
    jumps = 2

Now the last index is reachable.

Since r >= n - 1, the loop terminates.

Output:
2

--------------------------------------------------
8. Why Does This Greedy Approach Work?
--------------------------------------------------

Think of every reachable range as one BFS level.

- The first level contains index 0.
- The second level contains every index reachable in
  at most one jump.
- The third level contains every index reachable in
  at most two jumps.

For each level, we calculate the farthest position that
can be reached from any index in that level.

This ensures that the next level covers the maximum
possible range.

Since BFS explores states in increasing order of the
number of jumps, reaching the last index for the first
time gives the minimum number of jumps.

--------------------------------------------------
9. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

Although there is a nested loop, the ranges do not overlap.

For every iteration:
- The current range is processed.
- The next range starts at r + 1.

Therefore, every index is visited at most once.

Space Complexity: O(1)

Only a constant number of variables are used.

Core Idea:
----------
Treat reachable index ranges as BFS levels.

For each range:
1. Find the farthest position reachable from any index
   in the current range.
2. Move to the next range.
3. Increment the jump count.

Repeat until the last index becomes reachable.
*/