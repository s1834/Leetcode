class Solution {
    public:
        long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
            int n = nums1.size();
            vector<int> countDiff(1e5 + 1, 0); // abs(nums1[i] - nums2[i])
            for(int i = 0; i < n; i++) countDiff[abs(nums1[i] - nums2[i])]++;
    
            int k = k1 + k2; // total incr or decr
            for(int i = 1e5; i > 0 && k > 0; i--) {
                int minOps = min(k, countDiff[i]); // min we can remove
                countDiff[i] -= minOps; // -1 from curr
                countDiff[i - 1] += minOps; // add all those to i - 1 numbers
                k -= minOps;
            }
    
            long long result = 0;
            for(long long i = 1; i <= 1e5; i++) result += (countDiff[i] * i * i); // number of times i appears * square of i => countDiff[i] * (nums1[i] - nums2[i])^2
    
            return result;
        }
    };

/*
    ============================================================
    LeetCode 2333 - Minimum Sum of Squared Difference
    ============================================================

    Approach: Frequency Counting + Greedy
    ------------------------------------------------------------

    For every position i, only the absolute difference between
    nums1[i] and nums2[i] matters:

        diff[i] = |nums1[i] - nums2[i]|

    We have:

        k = k1 + k2

    total operations.

    Each operation can reduce one difference by 1.

    The final objective is:

        sum(diff[i]^2)

    Since squaring larger values has a much bigger contribution,
    we should always use our available operations to reduce the
    LARGEST differences first.

    Instead of storing every difference individually, we use a
    frequency array:

        countDiff[x]

    which stores how many positions currently have difference x.

    ============================================================
    1. Build the Difference Frequency Array
    ============================================================

    For every index:

        abs(nums1[i] - nums2[i])

    gives the current difference.

    We store its frequency:

        countDiff[abs(nums1[i] - nums2[i])]++;

    For example, if the differences are:

        [5, 5, 3, 2, 2]

    then:

        countDiff[5] = 2
        countDiff[3] = 1
        countDiff[2] = 2

    This allows us to process all equal differences together.

    ============================================================
    2. Combine k1 and k2
    ============================================================

    An operation from either k1 or k2 can reduce an absolute
    difference by 1.

    Therefore, only their total matters:

        k = k1 + k2;

    We can think of all operations as one common pool.

    ============================================================
    3. Why Reduce the Largest Difference First?
    ============================================================

    Suppose we have two differences:

        a > b

    Reducing `a` by 1 changes its squared contribution by:

        a^2 - (a - 1)^2
        = 2a - 1

    Reducing `b` by 1 changes its squared contribution by:

        b^2 - (b - 1)^2
        = 2b - 1

    Since:

        a > b

    we have:

        2a - 1 > 2b - 1

    Therefore, reducing the larger difference gives a larger
    reduction in the final sum.

    So the optimal greedy strategy is:

        Always reduce the largest current difference.

    ============================================================
    4. Process Differences from 1e5 Down to 1
    ============================================================

    The maximum possible difference is at most 1e5, so we
    traverse:

        for(int i = 1e5; i > 0 && k > 0; i--)

    Here `i` represents the current difference value.

    If:

        countDiff[i]

    elements currently have difference `i`, we can reduce some
    or all of them to:

        i - 1

    ============================================================
    5. How Many Differences Can We Reduce?
    ============================================================

    We calculate:

        int minOps = min(k, countDiff[i]);

    Suppose:

        countDiff[i] = 5
        k = 3

    Then only 3 of those five differences can be reduced:

        5 -> 4
        5 -> 4
        5 -> 4

    So:

        minOps = 3

    If instead:

        countDiff[i] = 5
        k = 10

    we can reduce all five:

        minOps = 5

    Therefore:

        minOps = min(k, countDiff[i])

    ============================================================
    6. Move the Differences from i to i - 1
    ============================================================

    Once `minOps` differences are reduced by 1:

        countDiff[i] -= minOps;

    removes them from the current bucket.

    Then:

        countDiff[i - 1] += minOps;

    places them into the bucket representing the new
    difference `i - 1`.

    Finally:

        k -= minOps;

    because those operations have been consumed.

    ============================================================
    7. Example
    ============================================================

    Suppose the differences are:

        [4, 4, 2]

    and:

        k = 3

    Frequency:

        countDiff[4] = 2
        countDiff[2] = 1

    Start from the largest difference, 4.

    ------------------------------------------------------------
    Process difference 4
    ------------------------------------------------------------

        countDiff[4] = 2
        k = 3

        minOps = min(3, 2)
                = 2

    Reduce both 4s:

        4 -> 3
        4 -> 3

    Frequencies become:

        countDiff[4] = 0
        countDiff[3] = 2
        countDiff[2] = 1

    Remaining operations:

        k = 3 - 2
          = 1

    ------------------------------------------------------------
    Process difference 3
    ------------------------------------------------------------

        countDiff[3] = 2
        k = 1

        minOps = 1

    Reduce one:

        3 -> 2

    Frequencies:

        countDiff[3] = 1
        countDiff[2] = 2

    No operations remain.

    Final differences:

        [3, 2, 2]

    ============================================================
    8. Why We Don't Need to Track Which Element Changes
    ============================================================

    The final answer only depends on the multiset of absolute
    differences.

    We do not care which particular index owns a difference.

    For example:

        [5, 3, 3]

    and:

        [3, 5, 3]

    produce the same squared-difference sum.

    Therefore, frequency counting is sufficient.

    ============================================================
    9. Calculate the Final Answer
    ============================================================

    After using the available operations, we have the final
    frequency of every difference.

    For every difference `i`:

        i^2

    is its contribution for one element.

    Since:

        countDiff[i]

    elements have this difference, their total contribution is:

        countDiff[i] * i * i

    Therefore:

        result += countDiff[i] * i * i;

    The result is stored in `long long` because the sum of
    squared differences can exceed the range of `int`.

    ============================================================
    10. Why Does the Greedy Strategy Give the Minimum?
    ============================================================

    The objective function is:

        sum(diff[i]^2)

    Consider using one operation on two possible differences:

        a > b

    Reducing `a` gives:

        a^2 - (a - 1)^2
        = 2a - 1

    reduction in the objective.

    Reducing `b` gives:

        b^2 - (b - 1)^2
        = 2b - 1

    Since `a > b`:

        2a - 1 > 2b - 1

    Therefore, the operation gives a greater improvement when
    applied to the larger difference.

    Repeatedly applying this logic means the optimal strategy
    is to reduce the largest differences first.

    The frequency array lets us perform this greedily without
    using a priority queue or processing every operation
    individually.

    ============================================================
    11. Why Is the Frequency Array Efficient?
    ============================================================

    A direct greedy implementation could repeatedly find the
    largest difference and decrease it.

    That could require many operations when k is large.

    Instead, we group equal differences.

    If:

        countDiff[100000] = 500

    and we have enough operations, we can move all 500 values
    from:

        100000 -> 99999

    in one step.

    Thus, the number of iterations depends on the possible
    difference values, not on the potentially huge value of k.

    ============================================================
    Complexity Analysis
    ============================================================

    Let:

        n = nums1.size()

    The maximum possible absolute difference is 1e5.

    Building the frequency array:

        O(n)

    Greedy reduction:

        O(1e5)

    Calculating the final result:

        O(1e5)

    Therefore:

        Time Complexity: O(n + 1e5)

    Since 1e5 is a fixed bound, this can effectively be viewed
    as:

        O(n)

    Space Complexity:

        O(1e5)

    for the frequency array.

    ============================================================
    Core Idea
    ============================================================

    1. Calculate every absolute difference.
    2. Store their frequencies.
    3. Combine k1 and k2 into one total number of operations.
    4. Starting from the largest difference, reduce as many
       values as possible by 1.
    5. Move those values from bucket `i` to bucket `i - 1`.
    6. Once all useful operations are applied, calculate:

           sum(countDiff[i] * i^2)

    The key greedy observation is:

        Reducing a larger difference gives a larger reduction
        in the squared-difference sum.

    Therefore, always reduce the largest differences first.
    ============================================================
*/