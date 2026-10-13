class Solution {
    public:
        long long maxAlternatingSum(vector<int>& nums) {
            for(int& num : nums) num *= num;
            sort(nums.begin(), nums.end());
    
            int n = nums.size();
            long long result = 0;
            for(int i = 0; i < n / 2; i++) result -= nums[i];
            for(int i = n / 2; i < n; i++) result += nums[i];
    
            return result;
        }
    };

/*
    Approach: Squaring + Sorting + Greedy

    The goal is to maximize the alternating sum by arranging the squared
    values so that larger values contribute positively and smaller values
    contribute negatively.

    The alternating sum involves adding and subtracting squared elements.
    Instead of explicitly constructing an alternating subsequence, this
    solution sorts the squared values and separates them into two groups:
    the smaller half is subtracted, and the larger half is added.

    ------------------------------------------------------------
    Step 1: Square every element
    ------------------------------------------------------------

        for(int& num : nums) num *= num;

    The problem involves the squares of the array elements.

    We replace each element with its square.

    Example:

        nums = [1, 3, 2, 4]

    After squaring:

        nums = [1, 9, 4, 16]

    Squaring makes every value non-negative, allowing us to compare
    their magnitudes directly.

    Note that this operation modifies the original input vector.

    ------------------------------------------------------------
    Step 2: Sort the squared values
    ------------------------------------------------------------

        sort(nums.begin(), nums.end());

    Sorting arranges the squared values in ascending order.

    Continuing the example:

        Before sorting: [1, 9, 4, 16]
        After sorting:  [1, 4, 9, 16]

    Now, the smallest values are at the beginning and the largest
    values are at the end.

    This allows us to divide the array into two groups:

        Smaller half -> negative contribution
        Larger half  -> positive contribution

    ------------------------------------------------------------
    Step 3: Initialize the result
    ------------------------------------------------------------

        int n = nums.size();
        long long result = 0;

    `n` stores the number of elements.

    `result` maintains the sum of all positive and negative
    contributions.

    We use `long long` for the accumulated result because the sum
    of squared values may exceed the range of a 32-bit integer.

    ------------------------------------------------------------
    Step 4: Subtract the smaller half
    ------------------------------------------------------------

        for(int i = 0; i < n / 2; i++)
            result -= nums[i];

    The loop processes the first `n / 2` elements.

    Since the array is sorted, these elements contain the smallest
    squared values.

    We subtract each of them from the result.

    Example:

        nums = [1, 4, 9, 16]
        n = 4

    Here:

        n / 2 = 2

    The first loop processes:

        nums[0] = 1
        nums[1] = 4

    Therefore:

        result = 0 - 1 - 4
               = -5

    ------------------------------------------------------------
    Step 5: Add the larger half
    ------------------------------------------------------------

        for(int i = n / 2; i < n; i++)
            result += nums[i];

    The second loop processes all remaining elements.

    These are the larger squared values, which are added to the result.

    Continuing the example:

        nums = [1, 4, 9, 16]

    The second loop processes:

        nums[2] = 9
        nums[3] = 16

    Therefore:

        result = -5 + 9 + 16
               = 20

    Final answer:

        20

    ------------------------------------------------------------
    Why does the greedy strategy work?
    ------------------------------------------------------------

    After squaring, let the sorted values be:

        a[0] <= a[1] <= ... <= a[n - 1]

    To maximize the sum, we want larger values to receive positive
    contributions and smaller values to receive negative contributions.

    Consider two values a and b, where a <= b.

    Assigning the larger value positively and the smaller value
    negatively gives:

        b - a

    Reversing their contributions gives:

        a - b

    Since b >= a:

        b - a >= a - b

    Therefore, the first assignment is never worse.

    This exchange argument explains why sorting the values and
    separating smaller and larger values is a natural greedy strategy.

    The code implements this idea directly using two loops.

    ------------------------------------------------------------
    Example: Odd number of elements
    ------------------------------------------------------------

    Input:

        nums = [1, 2, 3]

    After squaring and sorting:

        nums = [1, 4, 9]

    We have:

        n = 3
        n / 2 = 1

    Integer division gives:

        3 / 2 = 1

    First loop:

        result = 0 - nums[0]
               = -1

    Second loop:

        result = -1 + nums[1]
               = 3

        result = 3 + nums[2]
               = 12

    Final answer:

        12

    For an odd-sized array, the first loop processes floor(n / 2)
    elements, and the second loop processes the remaining elements.

    ------------------------------------------------------------
    Complexity Analysis
    ------------------------------------------------------------

    Time Complexity: O(n log n)

        Squaring all elements takes O(n).
        Sorting takes O(n log n).
        The two loops together take O(n).

        Therefore, sorting dominates the total time complexity.

    Space Complexity: O(log n) auxiliary space typically for sorting,
    depending on the sorting implementation.

        The solution modifies `nums` in place and does not create
        another array proportional to n.

    ------------------------------------------------------------
    Core Idea
    ------------------------------------------------------------

    Square every element, sort the array, subtract the smaller half,
    and add the larger half.

    Sorting makes it easy to separate the values according to their
    magnitudes and calculate the maximum alternating sum.
*/