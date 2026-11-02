class Solution {
    public:
        bool canJump(vector<int>& nums) {
            int n = nums.size(), maxReach = 0;
            for(int i = 0; i < n; i++) {
                if(i > maxReach) return false;
                maxReach = max(maxReach, i + nums[i]);
            }
    
            return maxReach >= n -1;
        }
    };

/*
Problem: LeetCode 55 - Jump Game

Approach: Greedy Algorithm

Intuition:
----------
We are given an array where nums[i] represents the maximum
number of steps we can jump forward from index i.

We need to determine whether we can reach the last index
starting from index 0.

Instead of exploring every possible jump, we maintain the
farthest index that can currently be reached.

The key idea is:
- If the current index is beyond maxReach, it means we
  cannot reach that position, so the answer is false.
- Otherwise, update maxReach using the maximum distance
  reachable from the current index.

--------------------------------------------------
1. Initialize Variables
--------------------------------------------------

int n = nums.size(), maxReach = 0;

- n stores the size of the array.
- maxReach stores the farthest index reachable so far.

Initially, we are at index 0, so maxReach = 0.

--------------------------------------------------
2. Traverse the Array
--------------------------------------------------

for(int i = 0; i < n; i++)

We iterate through every index and check whether it
is reachable.

--------------------------------------------------
3. Check Whether the Current Index Is Reachable
--------------------------------------------------

if(i > maxReach) return false;

If the current index is greater than maxReach, we cannot
reach it from any previously reachable position.

Therefore, reaching the last index is impossible, and
we immediately return false.

--------------------------------------------------
4. Update the Farthest Reachable Index
--------------------------------------------------

maxReach = max(maxReach, i + nums[i]);

From the current index i, we can jump at most nums[i]
positions forward.

Therefore, the farthest index reachable from i is:

    i + nums[i]

We update maxReach by taking the maximum of:
- The previously calculated farthest reachable index.
- The farthest index reachable from the current position.

This ensures that maxReach always represents the
maximum reachable position using all indices processed
so far.

--------------------------------------------------
5. Return the Final Result
--------------------------------------------------

return maxReach >= n - 1;

After processing the reachable indices, check whether
the farthest reachable position is at least the last
index (n - 1).

If yes, return true; otherwise, return false.

--------------------------------------------------
6. Example Walkthrough
--------------------------------------------------

Input:
nums = [2, 3, 1, 1, 4]

Initially:
    maxReach = 0

i = 0:
    0 <= maxReach
    maxReach = max(0, 0 + 2) = 2

i = 1:
    1 <= maxReach
    maxReach = max(2, 1 + 3) = 4

i = 2:
    2 <= maxReach
    maxReach = max(4, 2 + 1) = 4

i = 3:
    3 <= maxReach
    maxReach = max(4, 3 + 1) = 4

i = 4:
    4 <= maxReach
    maxReach = max(4, 4 + 4) = 8

Finally:

    maxReach = 8
    n - 1 = 4

Since maxReach >= n - 1, return true.

--------------------------------------------------
7. Example Where Reaching the End Is Impossible
--------------------------------------------------

Input:
nums = [3, 2, 1, 0, 4]

Initially:
    maxReach = 0

i = 0:
    maxReach = max(0, 0 + 3) = 3

i = 1:
    maxReach = max(3, 1 + 2) = 3

i = 2:
    maxReach = max(3, 2 + 1) = 3

i = 3:
    maxReach = max(3, 3 + 0) = 3

i = 4:
    4 > maxReach

We cannot reach index 4, so return false.

--------------------------------------------------
8. Complexity Analysis
--------------------------------------------------

Time Complexity: O(n)

We traverse the array exactly once, performing constant-time
operations at each index.

Space Complexity: O(1)

Only two variables, n and maxReach, are used.

Core Idea:
----------
Maintain the farthest reachable index while traversing
the array.

If the current index exceeds maxReach, return false.
Otherwise, extend maxReach using the current index.

At the end, check whether the last index is reachable.
*/