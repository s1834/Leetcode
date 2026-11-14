class Solution {
    public:
        int minimumSumSubarray(vector<int>& nums, int l, int r) {
            int n = nums.size();
    
            vector<int> prefixSum(n, 0);
            prefixSum[0] = nums[0];
            for (int i = 1; i < n; i++) prefixSum[i] = prefixSum[i - 1] + nums[i];
    
            int result = INT_MAX;
            for (int i = 0; i < n; i++) {
                for (int len = l; len <= r && i + len <= n; len++) {
                    int j = i + len - 1;
                    int sum = prefixSum[j] - (i > 0 ? prefixSum[i - 1] : 0);
                    if (sum > 0) result = min(result, sum);
                }
            }
    
            return result == INT_MAX ? -1 : result;
        }
    };

    
/*
    LeetCode 3364: Minimum Positive Sum Subarray

    Approach: Prefix Sum + Brute Force

    Intuition:
    We are given an array `nums` and two integers `l` and `r`.

    We need to find the minimum sum among all contiguous subarrays
    whose lengths are between l and r (inclusive), subject to the
    condition that the subarray sum must be strictly positive.

    Instead of calculating the sum of every subarray by traversing
    its elements repeatedly, we use a prefix sum array to calculate
    any subarray sum in O(1) time.

    Key Observation:
    Let prefixSum[i] represent the sum of all elements from index 0
    to index i.

    Then the sum of a subarray from index i to index j is:

        sum(i, j) = prefixSum[j] - prefixSum[i - 1]

    For a subarray starting at index 0, its sum is simply:

        sum(0, j) = prefixSum[j]

    This allows us to efficiently check every valid subarray.

    Step-by-Step Explanation:

    1. Calculate the array size:
        int n = nums.size();

       Store the number of elements in the input array.

    2. Build the prefix sum array:
        vector<int> prefixSum(n, 0);

       This array stores cumulative sums.

        prefixSum[0] = nums[0];

       The first prefix sum is simply the first element.

        for (int i = 1; i < n; i++)
            prefixSum[i] = prefixSum[i - 1] + nums[i];

       Each position stores the sum of all elements from index 0
       through the current index.

       Formula:

           prefixSum[i] = prefixSum[i - 1] + nums[i]

       Example:
           nums = [3, -2, 5, -1]

           prefixSum = [3, 1, 6, 5]

    3. Initialize the answer:
        int result = INT_MAX;

       We need to minimize the sum of valid positive-sum subarrays.

       Initially, no valid subarray has been found, so we use
       INT_MAX as a placeholder.

    4. Iterate over every possible starting index:
        for (int i = 0; i < n; i++)

       The outer loop fixes the starting index of the subarray.

    5. Try every allowed subarray length:
        for (int len = l; len <= r && i + len <= n; len++)

       The inner loop considers all subarray lengths from l to r.

       The condition:

           i + len <= n

       Ensures that the subarray does not extend beyond the array.

       Since the subarray starts at index i and has length len,
       its ending index must be:

           j = i + len - 1

    6. Calculate the ending index:
        int j = i + len - 1;

       This gives the last index of the current subarray.

    7. Calculate the subarray sum using prefix sums:
        int sum = prefixSum[j] -
                  (i > 0 ? prefixSum[i - 1] : 0);

       There are two cases:

       Case 1: Subarray starts at index 0.

           If i == 0:

               sum = prefixSum[j]

           No previous prefix sum needs to be subtracted.

       Case 2: Subarray starts after index 0.

           If i > 0:

               sum = prefixSum[j] - prefixSum[i - 1]

           We subtract the sum of all elements before the starting
           index to obtain only the elements inside the subarray.

    8. Check whether the sum is positive:
        if (sum > 0)

       The problem requires a strictly positive subarray sum.

       Therefore:
           - Zero is not considered valid.
           - Negative sums are also ignored.

    9. Update the minimum sum:
        result = min(result, sum);

       If the current subarray has a smaller positive sum than
       the previously found answer, update the result.

    10. Return the answer:
        return result == INT_MAX ? -1 : result;

       If result is still INT_MAX, no valid positive-sum subarray
       of an allowed length was found.

       In that case, return -1.

       Otherwise, return the minimum positive subarray sum.

    Example:
        nums = [3, -2, 5, -1]
        l = 2
        r = 3

        Prefix sum:
            prefixSum = [3, 1, 6, 5]

        Check subarrays with lengths 2 and 3.

        Starting at index 0:

            len = 2:
                Subarray = [3, -2]
                sum = prefixSum[1] = 1

                Positive -> result = 1

            len = 3:
                Subarray = [3, -2, 5]
                sum = prefixSum[2] = 6

                Positive -> result = min(1, 6) = 1

        Starting at index 1:

            len = 2:
                Subarray = [-2, 5]
                sum = prefixSum[2] - prefixSum[0]
                    = 6 - 3
                    = 3

                Positive -> result = min(1, 3) = 1

            len = 3:
                Subarray = [-2, 5, -1]
                sum = prefixSum[3] - prefixSum[0]
                    = 5 - 3
                    = 2

                Positive -> result = min(1, 2) = 1

        Starting at index 2:

            len = 2:
                Subarray = [5, -1]
                sum = prefixSum[3] - prefixSum[1]
                    = 5 - 1
                    = 4

                Positive -> result = min(1, 4) = 1

        Final minimum positive sum = 1

        Output: 1

    Complexity Analysis:

    Let:
        n = Number of elements in nums.
        r = Maximum allowed subarray length.

    - Time Complexity: O(n * (r - l + 1)).

      1. Building the prefix sum array takes O(n).
      2. The outer loop considers n starting positions.
      3. For each starting position, the inner loop checks at most
         (r - l + 1) possible lengths.
      4. Each subarray sum is calculated in O(1) using prefix sums.

      Therefore, the overall time complexity is:

          O(n + n * (r - l + 1))

      Which is O(n * (r - l + 1)).

      In the worst case, when the allowed length range is O(n),
      the complexity becomes O(n^2).

    - Space Complexity: O(n).

      The prefixSum vector stores n cumulative sums.
      Apart from this array, only a constant amount of extra space
      is used.

    Core Idea:
    Build a prefix sum array to calculate subarray sums in O(1).

    Enumerate every starting index and every allowed subarray length.
    Consider only subarrays with strictly positive sums and maintain
    the minimum among them.

    Return -1 if no valid subarray exists.
*/