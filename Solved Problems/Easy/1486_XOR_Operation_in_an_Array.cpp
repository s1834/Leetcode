class Solution {
    public:
        int xorOperation(int n, int start) {
            int ans = 0;
            for(int i = 0; i < n; i++) ans ^= start + 2 * i;
            return ans;
        }
    };

/*
    ============================================================
    LeetCode 1486 - XOR Operation in an Array
    ============================================================

    Approach:
    ------------------------------------------------------------

    We are given two integers:

        n     -> number of elements
        start -> starting value

    The array is defined as:

        nums[i] = start + 2 * i

    for:

        0 <= i < n

    We need to return the XOR of all elements of this array.

    Instead of explicitly creating the array, we can generate
    each value directly inside the loop and XOR it into `ans`.

    ============================================================
    1. Generate Each Array Element
    ============================================================

    For every index i:

        nums[i] = start + 2 * i

    Therefore, the loop:

        for(int i = 0; i < n; i++)

    generates exactly the required sequence.

    Example:

        n = 5
        start = 0

        i = 0 -> 0 + 2 * 0 = 0
        i = 1 -> 0 + 2 * 1 = 2
        i = 2 -> 0 + 2 * 2 = 4
        i = 3 -> 0 + 2 * 3 = 6
        i = 4 -> 0 + 2 * 4 = 8

        Array:

            [0, 2, 4, 6, 8]

    ============================================================
    2. Calculate the XOR
    ============================================================

    We initialize:

        int ans = 0;

    Then for every generated value:

        ans ^= start + 2 * i;

    This is equivalent to:

        ans = ans ^ (start + 2 * i);

    Since XOR is associative and commutative, we can
    continuously accumulate the XOR into `ans`.

    For the example:

        [0, 2, 4, 6, 8]

        ans = 0 ^ 0
            = 0

        ans = 0 ^ 2
            = 2

        ans = 2 ^ 4
            = 6

        ans = 6 ^ 6
            = 0

        ans = 0 ^ 8
            = 8

    Final answer:

        8

    ============================================================
    3. Why Don't We Need to Store the Array?
    ============================================================

    The problem only asks for the final XOR value.

    We do not need the individual array after using each
    element in the XOR calculation.

    Therefore, instead of:

        vector<int> nums;

        // build nums
        // then XOR all elements

    we directly generate each element and update `ans`.

    This reduces the extra space required by the algorithm.

    ============================================================
    4. Example
    ============================================================

    Suppose:

        n = 4
        start = 3

    Generated values:

        i = 0 -> 3
        i = 1 -> 5
        i = 2 -> 7
        i = 3 -> 9

    So:

        nums = [3, 5, 7, 9]

    XOR them:

        3 ^ 5 ^ 7 ^ 9

    The loop performs exactly this calculation without
    explicitly creating the array.

    ============================================================
    5. Correctness Intuition
    ============================================================

    The loop visits every valid index:

        i = 0, 1, ..., n - 1

    For each index, it generates:

        start + 2 * i

    which is exactly the value defined for nums[i].

    Each generated value is XORed into `ans` exactly once.

    Therefore, after the loop:

        ans = nums[0] ^ nums[1] ^ ... ^ nums[n-1]

    which is exactly the required result.

    ============================================================
    Complexity Analysis
    ============================================================

    Time Complexity: O(n)

        We generate and process exactly n elements.

    Space Complexity: O(1)

        We only maintain the XOR result and loop variable.
        The array itself is never stored.

    ============================================================
    Core Idea
    ============================================================

    The array element at index i is:

        start + 2 * i

    So simply generate each element and XOR it into `ans`:

        ans ^= start + 2 * i;

    No separate array is required.
    ============================================================
*/