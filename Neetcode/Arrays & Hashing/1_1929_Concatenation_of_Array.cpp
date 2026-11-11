class Solution {
    public:
        vector<int> getConcatenation(vector<int>& nums) {
            int n = nums.size();
            vector<int> result(2 * n);
            for(int i = 0; i < n; i++) {
                result[i] = nums[i];
                result[i + n] = nums[i];
            }
            return result;
        }
    };

/*
    LeetCode 1929: Concatenation of Array

    Approach: Direct Construction

    Intuition:
    We are given an array `nums` of size n and need to create a new array
    of size 2 * n by concatenating `nums` with itself.

    In other words:
        result = nums + nums

    The first half of the result contains the original array, while the
    second half contains an identical copy.

    Step-by-Step:
    1. Calculate the size of the input array and store it in `n`.
    2. Create a result array of size `2 * n`.
    3. Iterate through the original array:
       - `result[i] = nums[i]` copies the element to its original position.
       - `result[i + n] = nums[i]` copies the same element to the
         corresponding position in the second half.
    4. Return the constructed array.

    Example:
        nums = [1, 2, 1]

        n = 3
        result initially = [0, 0, 0, 0, 0, 0]

        i = 0:
            result[0] = 1
            result[3] = 1

        i = 1:
            result[1] = 2
            result[4] = 2

        i = 2:
            result[2] = 1
            result[5] = 1

        Final result = [1, 2, 1, 1, 2, 1]

    Complexity Analysis:
    - Time Complexity: O(n)
      We iterate through the input array once and perform two constant-time
      assignments during each iteration.

    - Space Complexity: O(n)
      We create a new result array containing 2 * n elements.
      Since the returned array is considered auxiliary output space,
      its size is O(n).

    Core Idea:
    Copy every element into two positions:
        result[i]     = nums[i]
        result[i + n] = nums[i]

    This constructs the concatenated array in a single traversal.
*/