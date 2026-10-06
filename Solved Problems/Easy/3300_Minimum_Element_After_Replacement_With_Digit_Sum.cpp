class Solution {
    private:
        int findSum (int num) {
            int sum = 0;
            while(num) {
                sum += num % 10;
                num /= 10;
            }
            return sum;
        }
    
    public:
        int minElement(vector<int>& nums) {
            int minNumber = INT_MAX;
            for(auto& x : nums) minNumber = min(minNumber, findSum(x));
            return minNumber;
        }
    };

/*
    ============================================================
    LeetCode 3300
    ============================================================

    Approach:
    ------------------------------------------------------------

    For every number in `nums`, we need to calculate the sum
    of its digits.

    We use a helper function `findSum()` to calculate the digit
    sum of one number, and then keep track of the minimum digit
    sum among all elements.

    ============================================================
    1. Calculate the Digit Sum
    ============================================================

    The helper function:

        findSum(int num)

    extracts the digits one by one.

    For every iteration:

        num % 10

    gives the last digit of `num`.

    We add this digit to `sum`:

        sum += num % 10;

    Then:

        num /= 10;

    removes the last digit.

    This continues until all digits have been processed.

    Example:

        num = 1234

        1234 % 10 = 4
        123  % 10 = 3
        12   % 10 = 2
        1    % 10 = 1

        sum = 4 + 3 + 2 + 1
            = 10

    ============================================================
    2. Find the Minimum Digit Sum
    ============================================================

    We initialize:

        minNumber = INT_MAX;

    This allows the first calculated digit sum to become the
    current minimum.

    For every number `x` in `nums`:

        findSum(x)

    calculates its digit sum.

    Then:

        minNumber = min(minNumber, findSum(x));

    keeps the smallest digit sum found so far.

    ============================================================
    3. Example
    ============================================================

    Suppose:

        nums = [10, 12, 23]

    Digit sums:

        10 -> 1 + 0 = 1
        12 -> 1 + 2 = 3
        23 -> 2 + 3 = 5

    Therefore:

        minNumber = min(1, 3, 5)
                  = 1

    So the answer is:

        1

    ============================================================
    4. Why Does This Work?
    ============================================================

    `findSum(x)` always returns the sum of all digits of `x`.

    We calculate this value independently for every element
    in the array.

    By maintaining the minimum value seen so far, after all
    elements have been processed, `minNumber` contains the
    minimum digit sum among all numbers.

    ============================================================
    Complexity Analysis
    ============================================================

    Let:

        n = number of elements in nums
        d = maximum number of digits in any element

    Time Complexity: O(n * d)

        Each number is processed digit by digit.

    Space Complexity: O(1)

        Only a few integer variables are used apart from the
        input and output.

    ============================================================
    Core Idea
    ============================================================

    For every number:

        1. Extract its digits using % 10.
        2. Add the digits together.
        3. Remove each digit using / 10.
        4. Keep the minimum digit sum.

    Therefore:

        answer = minimum digit sum among all elements.
    ============================================================
*/