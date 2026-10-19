class Solution {
    public:
        vector<int> targetIndices(vector<int>& nums, int target) {
            sort(nums.begin(), nums.end());
            vector<int> result;
            int n = nums.size();
            for(int i = 0; i < n; i++) {
                if(nums[i] > target) break;   
                if(nums[i] == target) result.push_back(i); 
            }
            return result;
        }
    };

/*
Approach: Sorting + Linear Search

Intuition:
----------
We need to return all indices where target appears after sorting nums
in non-decreasing order.

Sorting places equal elements together. Therefore, all occurrences
of target will occupy consecutive positions in the sorted array.

The index of an element in the sorted array is exactly the target
index we need to return.

1. Sort the Array
-----------------
sort(nums.begin(), nums.end());

Sort nums in ascending order.

For example:
nums = [1, 2, 5, 2, 3]
target = 2

After sorting:
nums = [1, 2, 2, 3, 5]

The target value 2 appears at indices 1 and 2.

2. Initialize the Result
------------------------
vector<int> result;
int n = nums.size();

result stores every index at which nums[i] equals target.
n represents the total number of elements.

3. Traverse the Sorted Array
----------------------------
for(int i = 0; i < n; i++)

Visit each index from left to right.

Case 1: nums[i] > target
------------------------
if(nums[i] > target) break;

Since nums is sorted, every element after index i must also be
greater than target.

Therefore, no later index can contain target, and we can stop
the loop early.

Case 2: nums[i] == target
-------------------------
if(nums[i] == target) result.push_back(i);

If the current element equals target, add its index to result.

Because we traverse from left to right, the indices are automatically
stored in increasing order.

If nums[i] < target, neither condition executes, so we simply
continue to the next index.

4. Return the Result
--------------------
return result;

The vector contains all indices where target appears in the sorted
array. If target does not exist, result remains empty.

Example Walkthrough:
--------------------
nums = [1, 2, 5, 2, 3]
target = 2

After sorting:
[1, 2, 2, 3, 5]

i = 0: nums[0] = 1 < 2
       Skip.

i = 1: nums[1] = 2
       Add index 1.
       result = [1]

i = 2: nums[2] = 2
       Add index 2.
       result = [1, 2]

i = 3: nums[3] = 3 > 2
       Break because all remaining elements are greater than 2.

Output: [1, 2]

Why This Works:
---------------
Sorting ensures that all occurrences of target are grouped together
and every element greater than target appears after them.

The loop records every index containing target. Once an element
greater than target is encountered, no additional matching index
can exist, so breaking early is safe.

Complexity Analysis:
--------------------
Time Complexity: O(n log n)
- Sorting takes O(n log n).
- The linear scan takes O(n) in the worst case.

Space Complexity:
- O(1) auxiliary space for the scan, excluding sorting implementation
  details.
- O(k) space for result, where k is the number of occurrences of target.

Core Idea:
----------
Sort the array, collect the indices where nums[i] equals target,
and stop early once nums[i] becomes greater than target.
*/