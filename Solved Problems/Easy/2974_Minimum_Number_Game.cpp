class Solution {
    public:
        vector<int> numberGame(vector<int>& nums) {
            int n = nums.size();
            sort(nums.begin(), nums.end());
            vector<int> ans;
            for(int i = 0; i < n; i++) {
                ans.push_back(nums[i + 1]);
                ans.push_back(nums[i]);
                i++;
            }
            return ans;
        }
    };

/*
    ============================================================
    LeetCode 2974 - Minimum Number Game
    ============================================================

    Approach: Sorting + Pairing
    ------------------------------------------------------------

    The game repeatedly takes the two smallest numbers from
    `nums`.

    For each pair:

        Alice takes the smaller number.
        Bob takes the larger number.

    The final array is formed by placing Bob's number first
    and Alice's number second.

    Therefore, after sorting the array, we can process the
    numbers in pairs and simply reverse the order inside every
    pair.

    ============================================================
    1. Sort the Array
    ============================================================

    First:

        sort(nums.begin(), nums.end());

    After sorting:

        nums[0] <= nums[1] <= nums[2] <= ...

    Therefore, the two smallest remaining numbers are always
    the next two elements in the sorted array.

    Example:

        nums = [5, 4, 2, 3]

    After sorting:

        [2, 3, 4, 5]

    The pairs selected by the game are:

        (2, 3)
        (4, 5)

    ============================================================
    2. Reverse Each Pair
    ============================================================

    For every pair:

        nums[i], nums[i + 1]

    the smaller value is:

        nums[i]

    and the larger value is:

        nums[i + 1]

    Since Alice takes the smaller value and Bob takes the
    larger value, the required order in the result is:

        Bob, Alice

    Therefore we append:

        nums[i + 1]
        nums[i]

    For:

        [2, 3, 4, 5]

    the result becomes:

        [3, 2, 5, 4]

    ============================================================
    3. Why Can We Pair Adjacent Elements After Sorting?
    ============================================================

    The game always chooses the two smallest remaining
    numbers.

    After sorting, the first two elements are the two smallest.

    Once they are removed, the next two elements become the
    two smallest remaining numbers.

    Therefore, the game naturally processes the sorted array
    in consecutive pairs:

        (nums[0], nums[1])
        (nums[2], nums[3])
        (nums[4], nums[5])
        ...

    We do not need to simulate removing elements from the
    original array because sorting already gives us the exact
    order in which the pairs are selected.

    ============================================================
    4. Loop and i++
    ============================================================

    The loop starts with:

        i = 0

    and processes:

        nums[0], nums[1]

    At the end of the iteration, the code performs:

        i++;

    The `for` loop itself also performs another `i++`.

    Therefore, `i` increases by 2 after each iteration.

    This allows the next iteration to process:

        nums[2], nums[3]

    and so on.

    ============================================================
    5. Example
    ============================================================

    Suppose:

        nums = [5, 4, 2, 3]

    Step 1: Sort

        [2, 3, 4, 5]

    Step 2: First pair

        (2, 3)

        Alice -> 2
        Bob   -> 3

        Add to answer:

            [3, 2]

    Step 3: Second pair

        (4, 5)

        Alice -> 4
        Bob   -> 5

        Add to answer:

            [3, 2, 5, 4]

    Final answer:

        [3, 2, 5, 4]

    ============================================================
    6. Why Does This Work?
    ============================================================

    Sorting guarantees that the smallest two remaining
    numbers are always adjacent.

    The game selects exactly these two numbers at every step.

    Within each selected pair:

        smaller -> Alice
        larger  -> Bob

    The problem requires Bob's choice to appear first in the
    resulting array, so we append:

        larger, smaller

    Repeating this for every pair produces exactly the array
    required by the game.

    ============================================================
    Complexity Analysis
    ============================================================

    Time Complexity: O(n log n)

        Sorting the array takes O(n log n).

        The following loop processes every element once:

            O(n)

        Therefore, the total is:

            O(n log n)

    Space Complexity: O(n)

        The `ans` vector stores n elements.

        Apart from the output, the algorithm uses O(1)
        additional space apart from the space used internally
        by `sort`.

    ============================================================
    Core Idea
    ============================================================

    Sort the numbers first.

    Then process them two at a time:

        [small, large] -> [large, small]

    because the game always chooses the two smallest remaining
    numbers, and Bob's larger number is placed before Alice's
    smaller number in the result.
    ============================================================
*/