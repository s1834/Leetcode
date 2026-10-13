/*
    Approach: Direct Traversal + Conditional Squaring

    The goal is to calculate the sum of squares of all elements whose
    indices satisfy the given condition.

    An element at index `i` is special if its 1-based position divides
    the length of the array.

    Since C++ uses 0-based indexing, the 1-based position of an element
    is `i + 1`.

    ------------------------------------------------------------
    Key Observation
    ------------------------------------------------------------

    For an array of size `n`, an element `nums[i]` contributes to the
    answer only when:

        n % (i + 1) == 0

    This checks whether the 1-based position of the element is a
    divisor of the array length.

    For every such element, we add:

        nums[i] * nums[i]

    to the answer.

    ------------------------------------------------------------
    Algorithm
    ------------------------------------------------------------

    1. Find the size of the array, `n`.
    2. Initialize `ans = 0`.
    3. Traverse every index `i` from `0` to `n - 1`.
    4. Check whether `n % (i + 1) == 0`.
    5. If true, add the square of `nums[i]` to `ans`.
    6. Return `ans`.

    ------------------------------------------------------------
    Example
    ------------------------------------------------------------

    Input:

        nums = [1, 2, 3, 4]
        n = 4

    Check each element:

        i = 0:
            1-based position = 1
            4 % 1 == 0
            Include 1^2 = 1

        i = 1:
            1-based position = 2
            4 % 2 == 0
            Include 2^2 = 4

        i = 2:
            1-based position = 3
            4 % 3 != 0
            Skip 3

        i = 3:
            1-based position = 4
            4 % 4 == 0
            Include 4^2 = 16

    Therefore:

        ans = 1 + 4 + 16 = 21

    Output:

        21

    ------------------------------------------------------------
    Why Does This Work?
    ------------------------------------------------------------

    The condition `n % (i + 1) == 0` selects exactly those elements
    whose 1-based positions divide the array length.

    Every selected element contributes its square exactly once, while
    every element that does not satisfy the condition is ignored.

    Therefore, the algorithm computes the required sum.

    ------------------------------------------------------------
    Complexity Analysis
    ------------------------------------------------------------

    Time Complexity: O(n)

        We traverse the array once and perform a constant amount of
        work for each element.

    Space Complexity: O(1)

        We use only a few variables, regardless of the array size.

    ------------------------------------------------------------
    Core Idea
    ------------------------------------------------------------

    Traverse the array, check whether each 1-based index divides the
    array length, and add the square of the element whenever the
    condition is satisfied.
*/