class Solution {
    public:
        int sumOfSquares(vector<int>& nums) {
            int n = nums.size();
            int ans = 0;
            for(int i = 0; i < n; i ++) if(n % (i + 1) == 0) ans += nums[i] * nums[i];
            return ans;
        }
    };

/*
    Approach: Array Traversal + Divisibility Check

    The goal is to calculate the sum of squares of all elements whose
    1-based positions divide the size of the array `n` exactly.

    In other words, an element at index `i` contributes to the answer
    if its position `(i + 1)` is a divisor of `n`.

    ------------------------------------------------------------
    Key Observation
    ------------------------------------------------------------

    Arrays use 0-based indexing, but the problem considers 1-based
    positions.

    Therefore:

        0-based index = i
        1-based position = i + 1

    An element is selected when:

        n % (i + 1) == 0

    This condition checks whether `i + 1` divides `n` without leaving
    a remainder.

    For every selected element, we add its square:

        nums[i] * nums[i]

    ------------------------------------------------------------
    Step 1: Initialize variables
    ------------------------------------------------------------

        int n = nums.size();
        int ans = 0;

    `n` stores the number of elements in the array.

    `ans` maintains the sum of squares of all qualifying elements.
    Initially, it is zero because no elements have been processed.

    ------------------------------------------------------------
    Step 2: Traverse the array
    ------------------------------------------------------------

        for(int i = 0; i < n; i++)

    We visit every index from `0` to `n - 1`.

    For each index, we check whether its 1-based position divides
    the array size.

        if(n % (i + 1) == 0)

    If the condition is true, we add:

        nums[i] * nums[i]

    to `ans`.

    If the condition is false, the element is skipped.

    ------------------------------------------------------------
    Example
    ------------------------------------------------------------

    Input:

        nums = [1, 2, 3, 4]
        n = 4

    We examine every element:

    Index 0:
        Position = 0 + 1 = 1
        4 % 1 = 0

        Position 1 divides 4.
        Add nums[0]^2 = 1^2 = 1

        ans = 1

    Index 1:
        Position = 1 + 1 = 2
        4 % 2 = 0

        Position 2 divides 4.
        Add nums[1]^2 = 2^2 = 4

        ans = 1 + 4 = 5

    Index 2:
        Position = 2 + 1 = 3
        4 % 3 != 0

        Position 3 does not divide 4.
        Skip this element.

        ans = 5

    Index 3:
        Position = 3 + 1 = 4
        4 % 4 = 0

        Position 4 divides 4.
        Add nums[3]^2 = 4^2 = 16

        ans = 5 + 16 = 21

    Final answer:

        21

    ------------------------------------------------------------
    Why does this work?
    ------------------------------------------------------------

    The loop checks every array position exactly once.

    For each position, the divisibility condition determines whether
    that position should contribute to the answer.

    Whenever the condition is satisfied, the square of the corresponding
    element is added to `ans`.

    All qualifying elements are therefore included, and all
    non-qualifying elements are excluded.

    ------------------------------------------------------------
    Complexity Analysis
    ------------------------------------------------------------

    Time Complexity: O(n)

        We traverse the array once and perform a constant amount of
        work at each index.

    Space Complexity: O(1)

        We use only the variables `n`, `ans`, and `i`, regardless of
        the size of the input array.

    ------------------------------------------------------------
    Core Idea
    ------------------------------------------------------------

    Traverse the array and use `n % (i + 1) == 0` to identify elements
    whose 1-based positions divide the array size. Add the square of
    each qualifying element to the answer.
*/