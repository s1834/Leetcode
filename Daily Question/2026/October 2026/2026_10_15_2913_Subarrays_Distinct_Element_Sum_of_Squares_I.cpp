class Solution {
    public:
        int sumCounts(vector<int>& nums) {
            int n = nums.size(), result = 0;
            for(int i = 0; i < n; i++) {
                unordered_set<int> s;
                for(int j = i; j < n; j++) {
                    s.insert(nums[j]);
                    result += s.size() * s.size();
                }
            }
    
            return result;
        }
    };

/*
    Approach: Brute Force + Hash Set + Nested Loops

    The goal is to calculate the sum of the squares of the number of
    distinct elements in every contiguous subarray of `nums`.

    For every subarray, we:
        1. Count its distinct elements.
        2. Square that count.
        3. Add the squared value to the final result.

    A subarray is a contiguous portion of an array. We can represent
    every subarray using its starting index `i` and ending index `j`.

    ------------------------------------------------------------
    Key Observation
    ------------------------------------------------------------

    Every subarray has a unique starting and ending index satisfying:

        0 <= i <= j < n

    Therefore, we can enumerate all subarrays using two nested loops.

    The important optimization in this approach is that we do not
    recreate the set from scratch for every ending index.

    Instead, for each starting index `i`, we create one empty set and
    extend the subarray one element at a time.

    Whenever a new element is added, the set automatically maintains
    the distinct elements seen in the current subarray.

    ------------------------------------------------------------
    Step 1: Initialize the variables
    ------------------------------------------------------------

        int n = nums.size(), result = 0;

    `n` stores the size of the input array.

    `result` stores the sum of squared distinct-element counts across
    all subarrays.

    Initially, the result is zero because no subarrays have been
    processed yet.

    ------------------------------------------------------------
    Step 2: Choose the starting index
    ------------------------------------------------------------

        for(int i = 0; i < n; i++) {
            unordered_set<int> s;

    The outer loop selects the starting index of a subarray.

    For every starting index `i`, we create a new empty set `s`.

    This set stores the distinct elements in the subarray currently
    being considered.

    We create a fresh set for each starting index because a new
    starting position means we are considering a different collection
    of subarrays.

    For example:

        nums = [1, 2, 1]

    When `i = 0`, the subarrays are:

        [1]
        [1, 2]
        [1, 2, 1]

    When `i = 1`, the subarrays are:

        [2]
        [2, 1]

    When `i = 2`, the subarray is:

        [1]

    Every possible non-empty subarray is considered exactly once.

    ------------------------------------------------------------
    Step 3: Extend the subarray
    ------------------------------------------------------------

        for(int j = i; j < n; j++) {

    The inner loop chooses the ending index `j`.

    It starts at `i`, ensuring that the ending index never precedes
    the starting index.

    At each iteration, the current subarray is:

        nums[i ... j]

    As `j` increases, the subarray grows by one element at a time.

    For example, with:

        nums = [1, 2, 1]
        i = 0

    The inner loop considers:

        j = 0 -> [1]
        j = 1 -> [1, 2]
        j = 2 -> [1, 2, 1]

    This incremental construction lets us update the set efficiently.

    ------------------------------------------------------------
    Step 4: Maintain distinct elements
    ------------------------------------------------------------

        s.insert(nums[j]);

    We insert the newly included element into the set.

    An `unordered_set` stores each distinct value only once.

    If the value is already present, inserting it does not increase
    the size of the set.

    Example:

        nums = [1, 2, 1]
        i = 0

    First iteration:

        j = 0
        Insert 1

        s = {1}
        s.size() = 1

    Second iteration:

        j = 1
        Insert 2

        s = {1, 2}
        s.size() = 2

    Third iteration:

        j = 2
        Insert 1 again

        s = {1, 2}
        s.size() = 2

    Even though the subarray `[1, 2, 1]` contains three elements,
    it contains only two distinct values: 1 and 2.

    Therefore, `s.size()` gives the number of distinct elements in
    the current subarray.

    ------------------------------------------------------------
    Step 5: Square the distinct count and accumulate it
    ------------------------------------------------------------

        result += s.size() * s.size();

    The problem requires the square of the distinct-element count
    for every subarray.

    If the current subarray contains `d` distinct elements, its
    contribution is:

        d * d = d^2

    We add this contribution to `result`.

    Continuing the example:

        nums = [1, 2, 1]

    Subarray [1]:

        Distinct count = 1
        Contribution   = 1^2 = 1

    Subarray [1, 2]:

        Distinct count = 2
        Contribution   = 2^2 = 4

    Subarray [1, 2, 1]:

        Distinct count = 2
        Contribution   = 2^2 = 4

    These subarrays contribute:

        1 + 4 + 4 = 9

    Now consider the remaining starting positions.

    Subarray [2]:

        Distinct count = 1
        Contribution   = 1

    Subarray [2, 1]:

        Distinct count = 2
        Contribution   = 4

    Subarray [1]:

        Distinct count = 1
        Contribution   = 1

    The complete sum is:

        result = 9 + 1 + 4 + 1
               = 15

    Final answer:

        15

    ------------------------------------------------------------
    Detailed Walkthrough
    ------------------------------------------------------------

    Input:

        nums = [1, 2, 1]

    Initially:

        result = 0

    Starting index i = 0:

        j = 0:
            Subarray = [1]
            Set = {1}
            result = 0 + 1^2 = 1

        j = 1:
            Subarray = [1, 2]
            Set = {1, 2}
            result = 1 + 2^2 = 5

        j = 2:
            Subarray = [1, 2, 1]
            Set = {1, 2}
            result = 5 + 2^2 = 9

    Starting index i = 1:

        A new empty set is created.

        j = 1:
            Subarray = [2]
            Set = {2}
            result = 9 + 1^2 = 10

        j = 2:
            Subarray = [2, 1]
            Set = {1, 2}
            result = 10 + 2^2 = 14

    Starting index i = 2:

        A new empty set is created.

        j = 2:
            Subarray = [1]
            Set = {1}
            result = 14 + 1^2 = 15

    Final answer:

        15

    ------------------------------------------------------------
    Why does this algorithm work?
    ------------------------------------------------------------

    Every non-empty contiguous subarray has a unique pair of indices
    `(i, j)`, where `i` is its starting index and `j` is its ending
    index.

    The nested loops enumerate every valid pair exactly once.

    For each starting index, the set begins empty and receives every
    element from `nums[i]` through `nums[j]` as `j` advances.

    Since a set stores only distinct values, its size always equals
    the number of distinct elements in the current subarray.

    The algorithm adds the square of that size for every subarray.
    Therefore, every required contribution is calculated exactly once,
    and their sum is the answer.

    ------------------------------------------------------------
    Complexity Analysis
    ------------------------------------------------------------

    Time Complexity: O(n^2) average

        There are:

            n + (n - 1) + (n - 2) + ... + 1

        subarrays, giving:

            n * (n + 1) / 2 = O(n^2)

        Each set insertion takes O(1) average time, so the overall
        expected time complexity is O(n^2).

        In the worst case, unordered-set operations can take O(n)
        time due to hash collisions, giving an O(n^3) worst-case
        bound for this implementation.

    Space Complexity: O(n)

        The set can contain up to `n` distinct elements in the
        worst case. Only one set is maintained at a time.

    ------------------------------------------------------------
    Core Idea
    ------------------------------------------------------------

    Fix every possible starting index, then extend the ending index
    one position at a time.

    Maintain a set of distinct elements for the current subarray and
    add the square of the set's size to the answer.

    This enumerates every subarray while avoiding repeated rebuilding
    of the set for each ending index.
*/