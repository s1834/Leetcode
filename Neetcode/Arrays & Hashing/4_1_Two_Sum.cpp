class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            int n = nums.size();
            for(int i = 0; i < n; i++) {
                for(int j = i + 1; j < n; j++) {
                    if(nums[i] + nums[j] == target) return {i, j};
                }
            }
    
            return {-1, -1};
        }
    };

/*
    LeetCode 1: Two Sum

    Approach: Brute Force (Nested Loops)

    Intuition:
    We are given an array `nums` and a target value.

    We need to find two distinct indices `i` and `j` such that:

        nums[i] + nums[j] == target

    Since we need to return the indices rather than the actual elements,
    we directly check every possible pair of elements.

    Step-by-Step Explanation:

    1. Calculate the size of the array:
        int n = nums.size();

    2. Fix the first element:
        for(int i = 0; i < n; i++)

       The outer loop selects the first element of the pair.

    3. Find the second element:
        for(int j = i + 1; j < n; j++)

       The inner loop checks every element after index `i`.

       Starting from `i + 1` ensures:
           - We never use the same element twice.
           - We avoid checking the same pair again in reverse order.

    4. Check whether the pair satisfies the target:
        if(nums[i] + nums[j] == target)

       If the sum equals the target, we have found the required pair.

       Return:
            {i, j}

       Since the problem guarantees exactly one solution, we can
       immediately return the indices without checking further pairs.

    5. If no valid pair is found:
        return {-1, -1};

       This is a fallback return statement in case no pair exists.

    Example:
        nums = [2, 7, 11, 15]
        target = 9

        i = 0, nums[i] = 2

            j = 1:
                nums[0] + nums[1] = 2 + 7 = 9

                Since the sum equals the target:
                    return {0, 1}

        Output: [0, 1]

    Complexity Analysis:

    - Time Complexity: O(n^2)
      The outer loop runs n times.
      For each index i, the inner loop checks all elements after i.

      Total comparisons:
          (n - 1) + (n - 2) + ... + 1
          = n * (n - 1) / 2

      Therefore, the time complexity is O(n^2).

    - Space Complexity: O(1)
      We use only a constant amount of extra space.
      No additional data structure is required.

    Core Idea:
    Check every possible pair of distinct elements using nested loops.
    Return the indices of the first pair whose sum equals the target.
*/