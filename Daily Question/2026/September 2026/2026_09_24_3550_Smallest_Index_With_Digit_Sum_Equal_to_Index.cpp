class Solution {
    private:
        int digitSum(int num) {
            int sum = 0;
            while(num) {
                sum += num % 10;
                num /= 10;
            }
            return sum;
        }
    
    public:
        int smallestIndex(vector<int>& nums) {
            int n = nums.size();
            for(int i = 0; i < n; i++) {
                if(digitSum(nums[i]) == i) return i;
            }
    
            return -1;
        }
    };

/*
    LeetCode 3550 - Smallest Index With Digit Sum Equal to Index
    ------------------------------------------------------------

    Approach:
    ------------------------------------------------------------

    We need to find the SMALLEST index i such that:

        sum of digits of nums[i] == i

    Since we want the smallest valid index, we simply scan the array
    from LEFT to RIGHT.

    For every index i:

        1. Calculate the digit sum of nums[i].
        2. Compare it with i.
        3. If they are equal, immediately return i.

    If we finish scanning the entire array without finding such an
    index, return -1.


    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    The condition we need to satisfy is:

        digitSum(nums[i]) == i

    There is no dependency between different elements of the array.

    Therefore, we can check every element independently.

    Since we scan from:

        i = 0, 1, 2, ...

    the FIRST index that satisfies the condition is automatically
    the smallest valid index.


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

        nums = [1, 3, 2, 1, 4, 2]

    Check each index:

        i = 0:
        nums[0] = 1

        digit sum = 1

        1 != 0


        i = 1:
        nums[1] = 3

        digit sum = 3

        3 != 1


        i = 2:
        nums[2] = 2

        digit sum = 2

        2 == 2

    Therefore, we immediately return:

        2


    ------------------------------------------------------------
    digitSum() Function:
    ------------------------------------------------------------

    The helper function:

        int digitSum(int num)

    calculates the sum of all decimal digits of num.

    It repeatedly extracts the LAST digit using:

        num % 10

    and then removes that last digit using:

        num /= 10


    ------------------------------------------------------------
    How num % 10 Works:
    ------------------------------------------------------------

    Suppose:

        num = 1234

    Then:

        1234 % 10 = 4

    so the last digit is:

        4


    After:

        num /= 10

    we get:

        123


    Again:

        123 % 10 = 3

    Then:

        123 / 10 = 12


    Then:

        12 % 10 = 2

    Then:

        12 / 10 = 1


    Finally:

        1 % 10 = 1

    Therefore:

        digit sum = 4 + 3 + 2 + 1
                  = 10


    ------------------------------------------------------------
    Step-by-Step digitSum():
    ------------------------------------------------------------

        int sum = 0;

    `sum` stores the total digit sum calculated so far.


    Then:

        while(num) {

    Continue extracting digits until all digits have been removed.


    Inside the loop:

        sum += num % 10;

    Add the last digit to sum.


    Then:

        num /= 10;

    Remove the last digit so that the next iteration processes
    the next digit.


    Finally:

        return sum;


    ------------------------------------------------------------
    Example of digitSum():
    ------------------------------------------------------------

        digitSum(508)

    Iteration 1:

        num = 508

        num % 10 = 8

        sum = 8

        num = 50


    Iteration 2:

        num = 50

        num % 10 = 0

        sum = 8 + 0 = 8

        num = 5


    Iteration 3:

        num = 5

        num % 10 = 5

        sum = 8 + 5 = 13

        num = 0


    Loop ends.

    Result:

        digitSum(508) = 13


    ------------------------------------------------------------
    Main Loop:
    ------------------------------------------------------------

        for(int i = 0; i < n; i++) {

            if(digitSum(nums[i]) == i)
                return i;

        }


    For every index i, we calculate:

        digitSum(nums[i])

    and compare it directly with:

        i


    If:

        digitSum(nums[i]) == i

    then i satisfies the required condition.

    Because we are traversing from left to right, this is guaranteed
    to be the SMALLEST such index.

    Therefore we can immediately:

        return i;


    ------------------------------------------------------------
    Why Can We Return Immediately?
    ------------------------------------------------------------

    Suppose multiple indices satisfy the condition:

        index 2  -> valid
        index 5  -> valid
        index 8  -> valid

    The problem asks for the SMALLEST index.

    Since our loop checks:

        0 -> 1 -> 2 -> 3 -> ...

    the first valid index encountered is always the smallest one.

    Therefore, there is no need to continue searching after finding
    a valid index.


    ------------------------------------------------------------
    Example With Multiple Valid Indices:
    ------------------------------------------------------------

        nums = [10, 20, 2, 3, 4, 5, 6]

    Suppose:

        digitSum(nums[2]) = digitSum(2) = 2

    So index 2 is valid.

    Even if a later index also satisfies the condition, such as:

        digitSum(nums[5]) = 5

    we still return:

        2

    because 2 is smaller than 5.


    ------------------------------------------------------------
    If No Valid Index Exists:
    ------------------------------------------------------------

    If the loop finishes without executing:

        return i;

    then there is no index satisfying:

        digitSum(nums[i]) == i

    Therefore:

        return -1;


    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

        nums = [10, 20, 30, 40]

    Check:

        i = 0:
        digitSum(10) = 1
        1 != 0

        i = 1:
        digitSum(20) = 2
        2 != 1

        i = 2:
        digitSum(30) = 3
        3 != 2

        i = 3:
        digitSum(40) = 4
        4 != 3


    No index satisfies the condition.

    Therefore:

        return -1;


    ------------------------------------------------------------
    Why We Do Not Need Extra Data Structures:
    ------------------------------------------------------------

    Each nums[i] can be processed independently.

    We do not need:

        - sorting
        - hash maps
        - dynamic programming
        - prefix sums
        - recursion
        - additional arrays

    We only need the current index and the digit sum of the current
    number.


    ------------------------------------------------------------
    Complexity:
    ------------------------------------------------------------

    Let:

        n = nums.size()

    and let d be the maximum number of digits in any nums[i].

    For every element, digitSum() processes each of its digits once.

    Therefore:

        Time Complexity = O(n * d)

    Since d is bounded by the integer size / problem constraints,
    this is effectively:

        O(n)


    Space Complexity:

        O(1)

    Only a few integer variables are used.


    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    The condition is simply:

        digitSum(nums[i]) == i

    So scan from left to right and return the first index where this
    condition is satisfied.


    ------------------------------------------------------------
    Main Takeaway:
    ------------------------------------------------------------

    This is a straightforward linear scan problem.

    The two important observations are:

        1. `num % 10` extracts the last digit.
        2. `num /= 10` removes the last digit.

    These allow us to calculate the digit sum in O(number of digits).

    Since we traverse the array from the smallest index to the largest,
    the first index satisfying:

        digitSum(nums[i]) == i

    is automatically the required smallest index.

    If no such index exists, return -1.
*/