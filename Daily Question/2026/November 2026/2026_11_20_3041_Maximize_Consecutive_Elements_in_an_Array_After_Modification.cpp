class Solution {
    private:
        int n;
        vector<vector<int>> dp;
    
        int find(vector<int>& nums, int start, int target) {
            int j = lower_bound(nums.begin() + start, nums.end(), target) - nums.begin();
    
            if(j < n && nums[j] == target) return j;
            return -1;
        }
    
        int solve(vector<int>& nums, int i, int inc) {
            if(dp[i][inc] != -1) return dp[i][inc];
    
            int curr = nums[i] + inc; // inc = 0/1
            int ans = 1;
    
            // option 1: find (curr + 1)
            int j = find(nums, i + 1, curr + 1);
            if(j != -1) ans = max(ans, 1 + solve(nums, j, 0));
    
            // option 2: find (curr) and then inc by + 1
            j = find(nums, i + 1, curr);
            if(j != -1) ans = max(ans, 1 + solve(nums, j, 1));
    
            return dp[i][inc] = ans;
        }
    
    public:
        int maxSelectedElements(vector<int>& nums) {
            n = nums.size();
            sort(nums.begin(), nums.end());
    
            dp.assign(n + 1, vector<int>(2, -1));
    
            int result = 1;
            for(int i = 0; i < n; i++) result = max({result, solve(nums, i, 0), solve(nums, i, 1)});
            
            return result;
        }
    };

/*
    LeetCode 3041: Maximize Consecutive Elements in an Array

    Approach: Sorting + Dynamic Programming (Memoization) + Binary Search

    Intuition:
    We are allowed to increase each array element by at most 1.
    We need to select elements such that, after these modifications,
    we can form the longest sequence of consecutive integers.

    Since the order of the original elements does not matter, we first
    sort the array.

    After sorting, we use DP to determine the maximum length of a
    consecutive sequence that can be formed starting from each index.

    Each element has two possible states:
    - inc = 0: The current element is used without incrementing it.
    - inc = 1: The current element is incremented by 1.

    For every current element, we have two possible transitions:

    1. Find the next element equal to curr + 1.
       We select it without incrementing it.

    2. Find the next element equal to curr.
       We increment it by 1, making its effective value curr + 1.

    Both transitions extend the consecutive sequence by one element.

    Binary search helps us find the required next element efficiently
    because the array is sorted.

    DP State:

    dp[i][inc] = Maximum number of consecutive elements we can select
                 starting from index i, assuming the current element
                 is used with the increment decision represented by inc.

    Effective current value:
        curr = nums[i] + inc

    Here:
        inc = 0 -> use nums[i] as it is.
        inc = 1 -> use nums[i] + 1.

    Variables:
    - n: Number of elements in the sorted array.
    - dp: Memoization table storing results for each index and increment
          state.
    - i: Current index in the sorted array.
    - inc: Whether the current element is incremented.
    - curr: Effective value of the current element.
    - j: Index of the next element found using binary search.
    - ans: Maximum consecutive sequence length starting from the
           current state.

    Step-by-Step Explanation:

    1. find(nums, start, target):

       This helper function searches for `target` in the sorted array,
       starting from index `start`.

       int j = lower_bound(nums.begin() + start, nums.end(), target)
               - nums.begin();

       `lower_bound` returns an iterator pointing to the first element
       greater than or equal to `target`.

       We convert that iterator into an array index.

       If:
           j < n && nums[j] == target

       The target exists, so return its index.

       Otherwise, return -1.

       Searching from `i + 1` ensures that we only select elements
       appearing after the current index.

    2. solve(nums, i, inc):

       This function calculates the maximum sequence length starting
       from index `i`, using the specified increment state.

       First, check whether the state has already been calculated:

           if(dp[i][inc] != -1) return dp[i][inc];

       If yes, return the cached answer.

    3. Calculate the effective current value:

           int curr = nums[i] + inc;

       The current element can either remain unchanged or be
       incremented by one.

    4. Initialize the answer:

           int ans = 1;

       We can always select the current element itself, so the
       minimum sequence length is 1.

    5. Option 1: Select the next element without incrementing it.

           int j = find(nums, i + 1, curr + 1);

       We search for an element whose original value is exactly
       one greater than the current effective value.

       If found:
           ans = max(ans, 1 + solve(nums, j, 0));

       We add 1 for the current element and continue from index `j`
       with `inc = 0`, because the next element is used unchanged.

       Example:
           Current effective value = 5
           Next original value = 6

           Sequence: 5 -> 6

    6. Option 2: Select the next element and increment it.

           int j = find(nums, i + 1, curr);

       We search for another element whose original value equals
       the current effective value.

       If found, we increment that element by 1.

       Its effective value becomes:
           nums[j] + 1 = curr + 1

       Therefore, it extends the consecutive sequence.

       Transition:
           ans = max(ans, 1 + solve(nums, j, 1));

       We continue with `inc = 1` because the next element is
       being incremented.

       Example:
           Current effective value = 5
           Next original value = 5

           Increment the next element:
               5 -> 6

           Sequence: 5 -> 6

    7. Store and return the result:

           return dp[i][inc] = ans;

       This avoids recalculating the same state.

    8. maxSelectedElements(nums):

       First, store the array size in `n`.

       Sort the array:
           sort(nums.begin(), nums.end());

       Sorting allows us to use binary search and ensures that
       subsequent selected indices are processed in increasing order.

       Initialize the DP table:

           dp.assign(n + 1, vector<int>(2, -1));

       There are two possible states for every index:
           dp[i][0] -> current element is unchanged.
           dp[i][1] -> current element is incremented.

       Finally, try both possible starting states for every index:

           for(int i = 0; i < n; i++)
               result = max({
                   result,
                   solve(nums, i, 0),
                   solve(nums, i, 1)
               });

       We consider every index as a possible starting point because
       the optimal consecutive sequence may begin anywhere in the
       sorted array.

       We also consider both ways of using the starting element.

       Return the maximum result.

    Example Walkthrough:

    nums = [2, 1, 5, 1, 1]

    After sorting:
        nums = [1, 1, 1, 2, 5]

    Consider starting at index 0 with inc = 0:

        nums[0] = 1
        curr = 1

        Option 1:
            Find curr + 1 = 2.
            Index 3 contains 2.

            Select 1 -> 2.

        Option 2:
            Find curr = 1.
            Another 1 exists at index 1.

            Increment it to 2.

            Select 1 -> 2.

        From the effective value 2, we can find 5 or another 2,
        depending on the available elements and increment decisions.

    The DP explores these choices from every starting index and
    returns the longest possible consecutive sequence.

    Why It Works:

    Sorting ensures that every transition moves to a later index,
    so the same array element is never selected twice.

    At each state, the current element has a fixed effective value.
    To extend a consecutive sequence, the next selected element
    must have an effective value exactly one greater.

    There are only two ways to achieve that:
    - Select an original element equal to curr + 1.
    - Select an original element equal to curr and increment it.

    These are exactly the two transitions explored by the DP.

    Memoization ensures that each (index, increment state) is
    calculated only once.

    Complexity Analysis:

    Let n be the number of elements.

    - Sorting: O(n log n).

    - DP States: O(n)
      There are n indices and 2 possible increment states.

    - Each DP State: O(log n)
      Each state performs at most two binary searches.

    - Total Time Complexity: O(n log n)
      Sorting takes O(n log n), and all DP states together take
      O(n log n).

    - Space Complexity: O(n)
      The DP table requires O(n) space.
      The recursive call stack can also grow up to O(n).

    Core Idea:
    Sort the array and use DP on (index, increment choice).
    From each element, either select the next original value
    (curr + 1), or increment an equal value (curr) to extend
    the consecutive sequence. Use binary search to find both
    transitions efficiently.

    Implementation Note:
    - The `find()` function returns the first matching occurrence
      at or after `start`, which is sufficient because only one
      occurrence is needed for each transition.
    - The `dp` table has n + 1 rows, although only indices 0 to n - 1
      are accessed.
    - This implementation uses recursion, so for very large n,
      recursion depth may become a stack consideration.
*/