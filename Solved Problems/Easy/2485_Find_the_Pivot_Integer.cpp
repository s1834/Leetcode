class Solution {
    public:
        int pivotInteger(int n) {
            int sum = 0;
            for(int i = 1; i <= n ; i++ ) sum += i;
    
            int temp = 0;
            for(int i = 1; i <= n; i++) {
                temp += i;
                if(sum == temp) return i;
                
                sum -= i;
            }
    
            return -1;
        }
    };

/*
    Approach:
    ------------------------------------------------------------
    We need to find a pivot integer x such that:

        1 + 2 + ... + x
        =
        x + (x + 1) + ... + n

    In other words, the sum of all numbers from 1 to x must be
    equal to the sum of all numbers from x to n.

    The important observation is that the value x is included in
    BOTH sides.

    We can solve this directly by maintaining:

        - `sum`  -> remaining sum from the current position to n
        - `temp` -> prefix sum from 1 to the current position



    ------------------------------------------------------------
    Key Observation:
    ------------------------------------------------------------

    Initially:

        sum = 1 + 2 + ... + n

    This represents the total sum of the entire range.

    As we iterate through i from 1 to n:

        temp += i

    makes `temp` equal to:

        1 + 2 + ... + i

    At the same time:

        sum -= i

    removes the numbers before i from the remaining suffix sum.

    However, the code checks for equality BEFORE subtracting i:

        temp += i;

        if(sum == temp) return i;

        sum -= i;

    Therefore, at the moment of comparison:

        temp = 1 + 2 + ... + i

    and:

        sum = i + (i + 1) + ... + n

    So the equality:

        sum == temp

    is exactly the required pivot condition.



    ------------------------------------------------------------
    Why is `sum` initialized to the total sum?
    ------------------------------------------------------------

    Before starting the second loop:

        sum = 1 + 2 + ... + n

    For i = 1:

        temp = 1

        sum = 1 + 2 + ... + n

    After checking i = 1, we execute:

        sum -= 1

    Now:

        sum = 2 + 3 + ... + n

    At i = 2:

        temp = 1 + 2

        sum = 2 + 3 + ... + n

    Notice that the current value i is still present in `sum`.

    This is intentional because the pivot integer i belongs to
    both sides of the required equation.



    ------------------------------------------------------------
    Example:
    ------------------------------------------------------------

    n = 8

    Total sum:

        1 + 2 + 3 + 4 + 5 + 6 + 7 + 8
        = 36

    Initially:

        sum = 36
        temp = 0



    i = 1:

        temp = 1
        sum = 36

        1 != 36

        sum -= 1
             = 35



    i = 2:

        temp = 1 + 2
             = 3

        sum = 35

        3 != 35

        sum -= 2
             = 33



    i = 3:

        temp = 6
        sum = 33

        6 != 33

        sum -= 3
             = 30



    i = 4:

        temp = 10
        sum = 30

        10 != 30

        sum -= 4
             = 26



    i = 5:

        temp = 15
        sum = 26

        15 != 26

        sum -= 5
             = 21



    i = 6:

        temp = 21
        sum = 21

    Now:

        1 + 2 + 3 + 4 + 5 + 6
        =
        6 + 7 + 8

        21 = 21

    Therefore:

        answer = 6



    ------------------------------------------------------------
    Important Detail:
    ------------------------------------------------------------

    The current value i must be present in both `temp` and `sum`.

    That is why:

        temp += i;

    happens first, then the equality is checked, and only after
    that:

        sum -= i;

    is performed.

    If we subtracted i before checking, the right side would become:

        (i + 1) + ... + n

    and the pivot itself would incorrectly be excluded.



    ------------------------------------------------------------
    Example Where No Pivot Exists:
    ------------------------------------------------------------

    n = 4

    Total sum:

        1 + 2 + 3 + 4 = 10

    Check each possible pivot:

        i = 1:
            left  = 1
            right = 1 + 2 + 3 + 4 = 10

        i = 2:
            left  = 1 + 2 = 3
            right = 2 + 3 + 4 = 9

        i = 3:
            left  = 1 + 2 + 3 = 6
            right = 3 + 4 = 7

        i = 4:
            left  = 1 + 2 + 3 + 4 = 10
            right = 4

    No equality occurs.

    Therefore:

        return -1;



    ------------------------------------------------------------
    Algorithm:
    ------------------------------------------------------------

    1. Calculate the total sum from 1 to n and store it in `sum`.

    2. Initialize:

           temp = 0

       where `temp` will represent the prefix sum.

    3. For every i from 1 to n:
       - Add i to `temp`.
       - Check whether `temp == sum`.
       - If equal, i is the pivot integer.
       - Otherwise subtract i from `sum` so that it represents
         the suffix beginning at the next position.

    4. If no pivot is found, return -1.



    ------------------------------------------------------------
    Why This Works:
    ------------------------------------------------------------

    At every iteration i, the code maintains:

        temp = 1 + 2 + ... + i

    and, before subtracting i:

        sum = i + (i + 1) + ... + n

    Therefore:

        temp == sum

    is exactly equivalent to:

        1 + 2 + ... + i
        =
        i + (i + 1) + ... + n

    which is the definition of a pivot integer.

    Since every possible i from 1 to n is checked, if a pivot
    exists, the algorithm will find it.

    If none of the values satisfy the condition, returning -1 is
    correct.



    ------------------------------------------------------------
    Mathematical Interpretation:
    ------------------------------------------------------------

    The pivot condition is:

        1 + 2 + ... + i
        =
        i + (i + 1) + ... + n

    Using the total sum:

        total = n(n + 1) / 2

    the right side can also be viewed as:

        total - (1 + 2 + ... + i - 1)

    The code implements this relationship incrementally rather
    than using the mathematical formula directly.

    This avoids repeatedly calculating prefix and suffix sums.



    ------------------------------------------------------------
    Time Complexity:
    ------------------------------------------------------------

    First loop:

        O(n)

    Second loop:

        O(n)

    Therefore total:

        O(n)



    ------------------------------------------------------------
    Space Complexity:
    ------------------------------------------------------------

        O(1)

    Only a few integer variables are used.



    ------------------------------------------------------------
    Core Idea:
    ------------------------------------------------------------

    Maintain two sums while scanning from left to right:

        `temp`
            = sum from 1 to i

        `sum`
            = sum from i to n

    Check equality BEFORE removing i from `sum`, because the pivot
    itself must belong to both sides.

    Therefore:

        temp == sum

    means i is the pivot integer.

    If no such i exists, return -1.
*/