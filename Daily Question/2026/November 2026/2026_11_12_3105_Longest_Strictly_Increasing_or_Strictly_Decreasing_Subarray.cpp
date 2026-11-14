class Solution {
    public:
        int longestMonotonicSubarray(vector<int>& nums) {
            int n = nums.size(), i = 0, j = 1, longest = 1;
            while(j < n) {
                if(nums[j] > nums[j - 1]) longest = max(longest, j - i + 1);
                else i = j; 
                j++;
            }
    
            i = 0;
            j = 1;
            while(j < n) {
                if(nums[j] < nums[j - 1]) longest = max(longest, j - i + 1);
                else i = j;
                j++;
            }
            
            return longest;
        }
    };

/*
    LeetCode 3105: Longest Strictly Increasing or Strictly Decreasing Subarray

    Approach: Two-Pass Sliding Window

    Intuition:
    We need to find the length of the longest contiguous subarray that is
    either:
        1. Strictly increasing.
        2. Strictly decreasing.

    A subarray is strictly increasing if every element is greater than
    the previous element.

    A subarray is strictly decreasing if every element is smaller than
    the previous element.

    Instead of handling both conditions in a single traversal, we perform
    two separate passes:
        - First pass: Find the longest strictly increasing subarray.
        - Second pass: Find the longest strictly decreasing subarray.

    The maximum length across both passes is our answer.

    Variables:
        n       -> Size of the input array.
        i       -> Starting index of the current monotonic subarray.
        j       -> Index of the element currently being examined.
        longest -> Length of the longest valid subarray found so far.

    Step-by-Step Explanation:

    PASS 1: Find the Longest Increasing Subarray

    1. Initialize:
        i = 0, j = 1, longest = 1

       Every single element is considered a valid monotonic subarray,
       so the initial answer is 1.

    2. Compare adjacent elements:
        if(nums[j] > nums[j - 1])

       If the current element is strictly greater than the previous
       element, the increasing sequence continues.

       Calculate its length:
            j - i + 1

       Update the answer:
            longest = max(longest, j - i + 1);

    3. Break the increasing sequence:
        else i = j;

       If the current element is not greater than the previous one,
       the increasing sequence is broken.

       We move `i` to `j`, treating the current element as the beginning
       of a new possible increasing subarray.

    4. Move forward:
        j++;

       Continue until the entire array has been traversed.

    PASS 2: Find the Longest Decreasing Subarray

    We reset:
        i = 0;
        j = 1;

       This allows us to independently check decreasing subarrays
       across the entire array.

    1. Compare adjacent elements:
        if(nums[j] < nums[j - 1])

       If the current element is strictly smaller than the previous
       element, the decreasing sequence continues.

       Update the answer using:
            longest = max(longest, j - i + 1);

    2. Break the decreasing sequence:
        else i = j;

       If the current element is not smaller than the previous one,
       the decreasing sequence is broken.

       Start a new possible decreasing subarray from index `j`.

    3. Move forward and repeat until the array is traversed.

    Example:
        nums = [1, 4, 3, 3, 2]

        PASS 1: Increasing subarrays

        i = 0, j = 1:
            4 > 1
            Increasing subarray = [1, 4]
            longest = 2

        i = 0, j = 2:
            3 < 4
            Increasing sequence breaks.
            i = 2

        i = 2, j = 3:
            3 == 3
            Increasing sequence breaks.
            i = 3

        i = 3, j = 4:
            2 < 3
            Increasing sequence breaks.
            i = 4

        Longest increasing length = 2

        PASS 2: Decreasing subarrays

        i = 0, j = 1:
            4 > 1
            Decreasing sequence breaks.
            i = 1

        i = 1, j = 2:
            3 < 4
            Decreasing subarray = [4, 3]
            longest = 2

        i = 1, j = 3:
            3 == 3
            Decreasing sequence breaks.
            i = 3

        i = 3, j = 4:
            2 < 3
            Decreasing subarray = [3, 2]
            longest = 2

        Longest decreasing length = 2

        Final Output: 2

    Why This Works:
    Every strictly increasing subarray consists entirely of adjacent
    increasing pairs. The first traversal extends a window while this
    condition holds and resets it whenever the condition breaks.

    Similarly, the second traversal does the same for strictly
    decreasing subarrays.

    Since both possible types of valid subarrays are examined completely,
    taking the maximum length gives the required answer.

    Complexity Analysis:

    Let n be the size of the input array.

    - Time Complexity: O(n)
      The first traversal examines each element once.
      The second traversal also examines each element once.
      Therefore, total work is O(2 * n) = O(n).

    - Space Complexity: O(1)
      Only a constant number of variables are used.
      No additional data structure is required.

    Core Idea:
    Perform two linear scans:
        1. Find the longest strictly increasing contiguous subarray.
        2. Find the longest strictly decreasing contiguous subarray.

    Reset the starting index whenever the monotonic condition breaks,
    and maintain the maximum length throughout both traversals.
*/