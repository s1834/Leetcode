class Solution {
    public:
        int minimumSum(int num) {
            vector<int> v;
            while(num) {
                v.push_back(num % 10);
                num /= 10;
            }
    
            sort(v.begin(), v.end());
            return (10 * v[0]) + (10 * v[1]) + v[2] + v[3];
        }
    };

/*
    ============================================================
    LeetCode 2160 - Minimum Sum of Four Digit Number After
                   Splitting Digits
    ============================================================

    Approach: Extract Digits + Sort
    ------------------------------------------------------------

    We are given a four-digit number.

    We need to rearrange its four digits into two two-digit
    numbers such that their sum is as small as possible.

    The key idea is to sort the digits and place the smaller
    digits in the tens positions.

    ============================================================
    1. Extract All Digits
    ============================================================

    We use:

        num % 10

    to get the last digit, and:

        num /= 10

    to remove the last digit.

    Therefore:

        while(num) {
            v.push_back(num % 10);
            num /= 10;
        }

    stores all four digits in `v`.

    Note that the digits are initially stored in reverse order,
    but this does not matter because we sort them afterward.

    Example:

        num = 2932

        Extracted digits:

            2, 3, 9, 2

        v = [2, 3, 9, 2]

    ============================================================
    2. Sort the Digits
    ============================================================

    We sort the four digits:

        sort(v.begin(), v.end());

    For:

        2932

    we get:

        v = [2, 2, 3, 9]

    ============================================================
    3. Why Should the Smallest Digits Go to the Tens Places?
    ============================================================

    A two-digit number has the form:

        10 * tens + ones

    Therefore, digits placed in the tens positions contribute
    10 times their value, while digits in the ones positions
    contribute only their value.

    So we want the smallest digits to occupy the tens places.

    After sorting:

        v[0] and v[1]

    are the two smallest digits.

    We use them as the tens digits.

    The remaining:

        v[2] and v[3]

    become the ones digits.

    Hence:

        answer = 10*v[0] + 10*v[1] + v[2] + v[3]

    ============================================================
    4. Example
    ============================================================

    Suppose:

        num = 2932

    Sorted digits:

        [2, 2, 3, 9]

    Construct:

        23 + 29

    Sum:

        23 + 29 = 52

    The formula gives:

        10*2 + 10*2 + 3 + 9
        = 20 + 20 + 3 + 9
        = 52

    ============================================================
    5. Why Is This Minimum?
    ============================================================

    Consider the four sorted digits:

        a <= b <= c <= d

    If `a` or `b` were placed in the ones position while
    `c` or `d` occupied a tens position, swapping them would
    decrease the total sum because the tens position has a
    larger multiplier.

    Therefore, the two smallest digits must be used as the
    tens digits.

    Once those are fixed, the remaining two digits can occupy
    the ones positions in either order, and their contribution
    is the same.

    Thus the minimum sum is:

        10*a + 10*b + c + d

    ============================================================
    Complexity Analysis
    ============================================================

    Time Complexity: O(1)

        There are always exactly four digits.

        Sorting four elements takes constant time.

    Space Complexity: O(1)

        The vector contains exactly four digits.

    ============================================================
    Core Idea
    ============================================================

    Extract the four digits, sort them, and place the two
    smallest digits in the tens positions.

        [a, b, c, d]

        minimum sum =
            10*a + 10*b + c + d

    because digits in the tens positions have the largest
    contribution to the final sum.
    ============================================================
*/